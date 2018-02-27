#include <stdio.h>
#include <string.h>

void copy1(char *str) {
  char buffer[16];
  strncpy(buffer, str, 16);
  printf("buffer: %s\n", buffer);
}

void copy2(char *str) {
  char buffer[16];
  strcpy(buffer, str);
  printf("buffer: %s\n", buffer);
}

int main () {
  copy1("It may be desirable to explain, that by the word operation, we mean");
  copy2("any proces which alters the mutual relation of two or more things,");
  printf("be this relation of what kind it may. - Ada Lovelace, \"Sketch\"\n");
  return 0;
}
