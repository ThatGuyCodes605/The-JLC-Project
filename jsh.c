/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

/* Defines */
#define MAX_CMDS 64
#define MAX_ARGS 64
#define VER "0.0.1" 
#define USR getenv("USER")
#define clear() printf("\033[H\033[J")

/* Function Prototypes */
void init_shell();
int take_input(char* s);
void control_c_handler(int sig);
int split_quoted(char* str, const char* delim, char** out);
void parse_args(char* cmd, char** args);
int exec_pipeline(char** cmds, int n, int background);
void execute_input(char* input);
int own_cmd_handler(char** parsed);

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
    getcwd(cwd, sizeof(cwd));
    gethostname(hostname, sizeof(hostname));
    snprintf(prompt, sizeof(prompt), "%s@%s:%s$ ", USR, hostname, cwd);
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

int exec_pipeline(char** cmds, int n, int background) {
    int pipes[n-1][2];
    if (n == 1) {
        pid_t pid = fork();
        if (pid == 0) {
            char* args[MAX_ARGS];
            parse_args(cmds[0], args);
            execvp(args[0], args);
            perror("exec failed");
            exit(1);
        }
        if (!background)
            wait(NULL);
        return 0;
    }
    for (int i = 0; i < n-1; i++)
        pipe(pipes[i]);

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
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    if (!background)
        for (int i = 0; i < n; i++)
            wait(NULL);

    return 0;
}
int split_quoted(char* str, const char* delim, char** out) {
    int i = 0;
    int in_quotes = 0;
    char* start = str;
    int delim_len = strlen(delim);

    for (char* p = str; *p != '\0'; p++) {
        
        if (*p == '"') {
            in_quotes = !in_quotes;
        }

        
        if (!in_quotes && strncmp(p, delim, delim_len) == 0) {
            *p = '\0'; 
            out[i++] = start;
            p += delim_len - 1; 
            start = p + 1;      
        }

        if (i >= MAX_CMDS - 1) break;
    }

    out[i++] = start;
    out[i] = NULL;
    return i;
}

void parse_args(char* cmd, char** args) {
    int i = 0;
    char* p = cmd;

    while (*p && i < MAX_ARGS - 1) {
        
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '\0') break;

        char* start;
        if (*p == '"') {
            start = ++p; 
            while (*p && *p != '"') p++; 
        } else {
            start = p;
            while (*p && *p != ' ' && *p != '\t') p++; 
        }

        if (*p != '\0') {
            *p = '\0'; 
            p++;
        }

        args[i++] = start;
    }
    args[i] = NULL;
}

void execute_input(char* input) {
    char* and_cmds[MAX_CMDS];
    
    int and_count = split_quoted(input, "&&", and_cmds);

    for (int i = 0; i < and_count; i++) {
        char* cmd = and_cmds[i];

        
        int background = 0;
        int in_quotes = 0;
        for (char* p = cmd; *p; p++) {
            if (*p == '"') in_quotes = !in_quotes;
            if (*p == '&' && !in_quotes) {
                background = 1;
                *p = '\0';
                break;
            }
        }

        
        char cmd_copy[1024];
        strncpy(cmd_copy, cmd, sizeof(cmd_copy) - 1);
        cmd_copy[sizeof(cmd_copy) - 1] = '\0';

        char* args[MAX_ARGS];
        parse_args(cmd_copy, args);
        if (args[0] && own_cmd_handler(args)) {
            continue;
        }

        
        char* pipe_cmds[MAX_CMDS];
        int pipe_count = split_quoted(cmd, "|", pipe_cmds);

        exec_pipeline(pipe_cmds, pipe_count, background);
    }
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
int own_cmd_handler(char** parsed);
void parse_args(char* cmd, char** args);
int split_quoted(char* str, const char* delim, char** out);
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
