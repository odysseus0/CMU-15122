#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
  // one way to declare and initialize a string
  char word[4] = {'a', 'c', 'e', '\0'};

  printf("word string: %s\n", word);
  printf("word ascii values: %d %d %d %d\n\n",
     word[0], word[1], word[2], word[3]);

  return 0;
}
