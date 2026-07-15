#include <stdio.h>
int main(int argc, char** argv) {
   if (argc < 2) {
      fprintf(stderr, "Usage: print \"<string>\"...\n");
      return 1;
   }
   for(int i = 1; i < argc; i++) {
      printf("%s", argv[i]);

      if(i != argc - 1) putchar(' ');
      else putchar('\n');
   }
   return 0;
}

