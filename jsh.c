#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#define VER "0.0.1" 
#define USR getenv("USER")
#define clear() printf("\033[H\033[J")
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
void printDIR(){
    char cwd[1024];
    char hostname[256];

    if(getcwd(cwd, sizeof(cwd)) != NULL){
        gethostname(hostname, sizeof(hostname));
        printf("%s@%s %s", USR, hostname, cwd);
    }
    else{
        perror("getcwd() error");
    }
}
int take_input(char* s){
    char* input = readline(" $ ");
    if(strlen(input) > 0){
        add_history(input);
        strcpy(s, input);
        return 0;
    }
    else{
        return 1;
    }
}
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
int execArgsPiped(char** parsed, char** parsedpipe){
    int pipefd[2];
    pid_t p1, p2;
    if(pipe(pipefd) < 0){
        perror("Pipe failed");
        return 4;
    }
    p1 = fork();
    if (p1 < 0){
        perror("Fork failed");
        return 2;
    }
    if (p1 == 0){
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        if (execvp(parsed[0], parsed) < 0){
            perror("Execution failed");
            exit(0);
        }   
    } 
    else{
        p2 = fork();
        if (p2 < 0){
            perror("Fork failed");
            return 2;
        }
        if (p2 == 0){
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            if (execvp(parsedpipe[0], parsedpipe) < 0){
                perror("Execution failed");
                exit(0);
            }
        }
        else{
            wait(NULL);
            wait(NULL);
        }
    }
    return 0;
}
int own_cmd_handler(char** parsed){
    if (strcmp(parsed[0], "cd") == 0){
        if (chdir(parsed[1]) < 0){
            perror("cd failed");
        }
        return 1;
    }
    else if (strcmp(parsed[0], "exit") == 0){
        printf("Exiting JSH...\n");
        exit(0);
    }
    return 0;
}

int parse_pipe(char* s, char** strpiped){
    for (int i = 0; i < 2; i++){
        strpiped[i] = strsep(&s, "|");
        if (strpiped[i] == NULL){
            break;
        }
    }
    if (strpiped[1] == NULL){
        return 0;
   }    
    else {
        return 1;
    }
}   
void parse_space(char* s, char** parsed){
    for (int i = 0; i < 100; i++){
        parsed[i] = strsep(&s, " ");
        if (parsed[i] == NULL){
            break;
        }
        if (strlen(parsed[i]) == 0){
            i--;
        }
    }
}
int prosess_string(char* s, char** parsed, char** parsedpipe){
    char* strpiped[2];
    int piped = 0;
    piped = parse_pipe(s, strpiped);
    if(piped){
        parse_space(strpiped[0], parsed);
        parse_space(strpiped[1], parsedpipe);
    }
    else {
        parse_space(s, parsed);
        if (own_cmd_handler(parsed))
            return 0;
        return 1;
    }
     if (own_cmd_handler(parsedpipe)){
        return 0;
    }
     else{
      return 1 + piped;
    }
}

int main(void){
    char input[1024];
    char* parsed_args_pipe[100];
    char* parsed_args[100];
    int execFlag = 0;
    init_shell();
        while(1){
        printDIR();
        if(take_input(input)){
            continue;
        }
        execFlag = prosess_string(input, parsed_args, parsed_args_pipe);
        if(execFlag == 1){
            exec_args(parsed_args);
        }
        if(execFlag == 2){
            execArgsPiped(parsed_args, parsed_args_pipe);
        }
    }
    return 0;
}
