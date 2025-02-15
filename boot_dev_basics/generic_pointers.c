#include <stdio.h>

// cc generic_pointers.c -o generic_pointers.o && ./generic_pointers.o
int main() {
  int value = 42;

  // void in C represent "nothing" or "no type" like a any type on Go language
  void *generic_int_ptr = &value;

  // so, we need to cast the void pointer to a specific type to access the value
  printf("==> The value from generic casted is: %d\n", *(int *)generic_int_ptr);
}
