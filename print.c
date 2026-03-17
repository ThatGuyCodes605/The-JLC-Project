#include <stdio.h>
int main(int argc, char** argv) {
   if (argc != 2) {
      printf("Usage: print \"<string>\"\n");
      return 1;
   }
   printf("%s\n", argv[1]);
}