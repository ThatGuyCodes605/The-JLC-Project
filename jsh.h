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
