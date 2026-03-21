#include <stdio.h>
#include <string.h>
#define SPEC_BUFSIZ 1024
int main(int argc, char** argv) {
   char buf[SPEC_BUFSIZ];
   char buf2[SPEC_BUFSIZ];
   if (argc < 2) {
      fprintf(stderr, "Usage: spec filename\n");
      return 1;
   }
   FILE *f = fopen(argv[1], "r");
   if (f == NULL) {
      perror("FATAL ERROR");
      return 2;
   }
   buf2[0] = '\0';
   while (fgets(buf, SPEC_BUFSIZ, f) != NULL) {
      if (strcmp(buf, buf2) != 0) {
         printf("%s", buf);
      }
      memcpy(buf2, buf, SPEC_BUFSIZ);
   }
   fclose(f);
   return 0;
}