#include "stack.h"
#include <stdio.h>

// cc stack.c -o stack.o && ./stack.o
int main() {
  // on this approach the stack grows
  // and release after the function call
  printMessageOne();
  printMessageTwo();
  printMessageThree();

  // on this approach the stack grows
  printMessageOneBadApproach();
  return 0;
}

void printMessageOne() {
  const char *message = "Dark mode?\n";
  printStackPointerDiff();
  printf("%s\n", message);
}
void printMessageTwo() {
  const char *message = "More like...\n";
  printStackPointerDiff();
  printf("%s\n", message);
}

void printMessageThree() {
  const char *message = "dark roast.\n";
  printStackPointerDiff();
  printf("%s\n", message);
}

void printStackPointerDiff() {
  static void *last_sp = NULL;
  void *current_sp;
  current_sp = __builtin_frame_address(0);

  long diff = (char *)last_sp - (char *)current_sp;

  if (last_sp == NULL) {
    last_sp = current_sp;
    diff = 0;
  }

  printf("---------------------------------\n");
  printf("Stack pointer offset: %ld bytes\n", diff);
  printf("---------------------------------\n");
}

void printMessageOneBadApproach() {
  const char *message = "Dark mode?\n";
  printStackPointerDiff();

  printf("%s\n", message);
  printMessageTwoBadApproach();
}

void printMessageTwoBadApproach() {
  const char *message = "More like...\n";
  printStackPointerDiff();
  printf("%s\n", message);
  printMessageThreeBadApproach();
}

void printMessageThreeBadApproach() {
  const char *message = "dark roast.\n";
  printStackPointerDiff();
  printf("%s\n", message);
}
