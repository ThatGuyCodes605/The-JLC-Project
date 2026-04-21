/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "jsh.h"

/* Defines */
#define MAX_CMDS 64
#define MAX_ARGS 64
#define VER "1.0.0"
#define USR getenv("USER")
#define clear() printf("\033[H\033[J")

/* Function Prototypes */
void init_shell(void);
int take_input(char* s);
void control_c_handler(int sig);
int split(char* str, const char* delim, char** out);
int split_quoted(char* str, const char* delim, char** out);
void parse_args(char* cmd, char** args);
int own_cmd_handler(char** parsed);
int exec_pipeline(char** cmds, int n, int background);
void execute_input(char* input);

int main(void){
    char input[1024];
    signal(SIGINT, control_c_handler);
    init_shell();
    while(1){
        if(take_input(input)){
            continue;
        }
        execute_input(input);
    }
    return 0;
}
/* Functions */
void init_shell() {
    clear();
    printf("Initializing JSH...\n");
    usleep(200000);
    printf("Loading configuration...\n");
    usleep(200000);
    printf("Setting up environment...\n");
    usleep(200000);
    printf("JSH initialized successfully!\n");
    usleep(200000);
    printf("Welcome %s to JSH (Jamie's Shell)!\n", USR);
    usleep(200000);
    printf("JSH version %s\n", VER);
    usleep(200000);
    clear();
    usleep(200000);
    FILE* f = popen("jfetch", "r");
    char line[256];
    while (fgets(line, sizeof(line), f))
        printf("%s", line);
    pclose(f);
    usleep(200000);

}
int take_input(char* s){
    char prompt[1536];
    char cwd[1024];
    char hostname[256];
    getcwd(cwd, sizeof(cwd)); /* Get the current working directory */
    gethostname(hostname, sizeof(hostname)); /* Get the hostname */
    snprintf(prompt, sizeof(prompt), "%s@%s:%s$ ", USR, hostname, cwd); /* Construct the prompt string */
    char* input;
    do {
        input = readline(prompt);
        if (input == NULL){
            printf("\n");
        }
    } while (input == NULL);
    if (input == NULL){
        printf("\n");
        return 1;
    }
    if(strlen(input) > 0){
        add_history(input);
        strcpy(s, input);
        free(input);
        return 0;
    }
    free(input);
    return 1;
}
void control_c_handler(int sig){
    signal(SIGINT, control_c_handler);
    printf("\nCaught signal %d. Use 'exit' to quit JSH.\n", sig);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int split(char* str, const char* delim, char** out) {
    int i = 0;

    char* saveptr;
    char* token = strtok_r(str, delim, &saveptr);

    while (token && i < MAX_CMDS - 1) {
        out[i++] = token;
        token = strtok_r(NULL, delim, &saveptr);
    }

    out[i] = NULL;
    return i;
}

int split_quoted(char* str, const char* delim, char** out){
    int i = 0; /*/ Index for output array */
    char* start = str; /*/ Start of the current token */
    int in_quotes = 0; /*/ Flag to track if we're inside quotes */
    int delim_len = strlen(delim);
    for(char* p = str; *p != '\0'; p++){ /*/ Iterate through the string */
        if(*p == '"') in_quotes = !in_quotes; /*/ Toggle quote flag */
        if(!in_quotes && strncmp(p, delim, delim_len) == 0){ /*/ Check for delimiter */
            *p = '\0'; /* Null-terminate the token */
            out[i++] = start; /*/ Store the token */
            p += delim_len - 1; /* Move past the delimiter */
            start = p + 1; /*/ Set start for the next token */
        }
    }
    out[i++] = start;
    out[i] = NULL;
    return i;
} 
void parse_args(char* cmd, char** args) {
    int i = 0; /* Index for args array */
    char* p = cmd; /* Pointer to traverse the command string */

    while (*p && i < MAX_ARGS - 1) { /* Loop until end of string or max args reached */ 
        
        while (*p == ' ' || *p == '\t') p++; /* Skip leading whitespace */
        if (*p == '\0') break; /* End of string */

        char* start; /* Start of the current argument */
        if (*p == '"') { /* Handle quoted argument */
            start = ++p; /* Skip the opening quote */
            while (*p && *p != '"') p++; /* Move to the closing quote */
        } else {
            start = p; /* Start of a non-quoted argument */
            while (*p && *p != ' ' && *p != '\t') p++; /* Move to the next whitespace */
        }

        if (*p != '\0') { /* Null-terminate the argument */
            *p = '\0'; /* Null-terminate the argument */
            p++; /* Move past the null terminator */
        }

        args[i++] = start; /* Store the argument in the args array */
    }
    args[i] = NULL; /* Null-terminate the args array */
}


/*
int exec_args(char** args){
    pid_t pid = fork();
    if(pid == -1){
        perror("Fork failed");
        return 2;
    }
    else if(pid == 0){
        if(execvp(args[0], args) < 0){
            perror("Execution failed");
        }
        exit(0);
    }
    else{
        wait(NULL);
        return 0;
    }
}
*/
int own_cmd_handler(char** parsed){
    if (strcmp(parsed[0], "help") == 0){
        printf("JSH - Jamie's Shell\n");
        printf("Version: %s\n", VER);
        printf("Author: Jamie\n");
        printf("Built-in commands:\n");
        printf("  ver - Show the current version of JSH\n");
        printf("  cd [dir] - Change the current directory to 'dir'\n");
        printf("  history - Show command history\n");
        printf("  clear - Clear the terminal screen\n");
        printf("  help - Display this help message\n");
        printf("  exit - Exit the shell\n");
        printf("Use '<command> | <command>' for piped commands\n");
        return 6;
    }
    else if (strcmp(parsed[0], "ver") == 0){
        printf("JSH version %s\n", VER);
        return 7;
    }
    else if (strcmp(parsed[0], "clear") == 0){
        clear();
        return 8;
    }
    else if (strcmp(parsed[0], "history") == 0){
        HIST_ENTRY** hist = history_list();
        for (int i = 0; hist[i]; i++){
            printf("%d: %s\n", i + history_base, hist[i]->line);
        }
        return 9;
    }
    else if (strcmp(parsed[0], "cd") == 0){
        if (chdir(parsed[1]) < 0){
            perror("cd failed");
        }
        return 10;
    }
    else if (strcmp(parsed[0], "exit") == 0){
        printf("Exiting JSH...\n");
        exit(0);
    }
    return 0;
}
int exec_pipeline(char** cmds, int n, int background) {
    int pipes[n-1][2];
    if (n == 1) {
        pid_t pid = fork(); /* Fork a child process */
        if (pid == 0) {
            char* args[MAX_ARGS];
            parse_args(cmds[0], args); /* Parse the command into arguments */
            execvp(args[0], args); /* Execute the command */
            perror("exec failed"); /* If execvp returns, it means execution failed */
            exit(1); /* Exit the child process with an error code */
        }
        if (!background)
            wait(NULL); /* Wait for the child process to finish if not running in background */
        return 0;
    }
    for (int i = 0; i < n-1; i++)
        pipe(pipes[i]); /* Create pipes for inter-process communication */

    for (int i = 0; i < n; i++) {
        if (fork() == 0) {
            if (i > 0)
                dup2(pipes[i-1][0], STDIN_FILENO);
            if (i < n-1)
                dup2(pipes[i][1], STDOUT_FILENO);

            for (int j = 0; j < n-1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            char* args[MAX_ARGS];
            parse_args(cmds[i], args);
            execvp(args[0], args);
            perror("exec failed");
            exit(1);
        }
    }

    for (int i = 0; i < n-1; i++) {
        close(pipes[i][0]); /* Close the read end of the pipe in the parent process */
        close(pipes[i][1]); /* Close the write end of the pipe in the parent process */
    }

    if (!background){
        for (int i = 0; i < n; i++)
            wait(NULL); /* Wait for all child processes to finish if not running in background */
    }
    return 0;
}
void execute_input(char* input) {
    char* and_cmds[MAX_CMDS];
    int and_count = split_quoted(input, "&&", and_cmds); /* Split input by '&&' while respecting quotes */
    for (int i = 0; i < and_count; i++) {
        char* cmd = and_cmds[i];

        
        int background = 0;
        int in_quotes = 0;
        for (char* p = cmd; *p; p++) { /* Iterate through the command string */
            if (*p == '"') in_quotes = !in_quotes;
            if (*p == '&' && !in_quotes) {
                background = 1;
                *p = '\0';
                break;
            }
        }

        
        char cmd_copy[1024];
        strncpy(cmd_copy, cmd, sizeof(cmd_copy) - 1); /* Copy command to a temporary buffer for parsing */
        cmd_copy[sizeof(cmd_copy) - 1] = '\0';

        char* args[MAX_ARGS]; /* Array to hold parsed arguments */
        parse_args(cmd_copy, args); /* Parse the command into arguments */
        if (args[0] && own_cmd_handler(args)) { /* Check if it's a built-in command and handle it */
            continue; /* If it was a built-in command, skip to the next command */
        }

        
        char* pipe_cmds[MAX_CMDS]; /* Array to hold piped commands */
        int pipe_count = split_quoted(cmd, "|", pipe_cmds); /* Split command by '|' while respecting quotes */

        exec_pipeline(pipe_cmds, pipe_count, background); /* Execute the pipeline of commands */
    }
}

