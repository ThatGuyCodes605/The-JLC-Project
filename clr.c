#include <stdio.h>

int main(int argc, char** argv) {
    /* 
        Check if the user passed any arguments. 
        'clr' doesn't take arguments, so if there are any, 
        print usage to stderr and exit with an error code.
    */
    if (argc != 1) {
        fprintf(stderr, "Usage: clr\n");
        return 1;
    }

    /*
      ANSI escape sequences used:
      \033[H   : Moves the cursor to the home position (top left).
      \033[2J  : Clears the entire screen.
      \033[3J  : Clears the scrollback buffer (supported in most modern terminals).
    */
    printf("\033[H\033[2J\033[3J"); // I serached that lol

    // Flush stdout to ensure the terminal processes the escape sequences immediately
    fflush(stdout);

    return 0; 

    // Now to try this print in the terminal 'gcc -std=c99 -o clr clr.c', then './clr' and your terminal should be clear
}