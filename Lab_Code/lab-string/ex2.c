#include <stdio.h>

int main()
{
  char* states2[] = {"California", "Virginia", "Oklahoma", "Washington"};
  (void)states2;
  char* states[] = {"Pennsylvania", "West Virginia", "Ohio", "Maryland"};
  int num_states = 4;

  for (int i = 0; i < num_states; i++) {
    printf("state #%d: %s\n", i, states[i]);
  }

  return 0;
}

