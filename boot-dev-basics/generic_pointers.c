#include <stdio.h>

// cc generic_pointers.c -o generic_pointers.o && ./generic_pointers.o
int main() {
  int value = 42;
  void *generic_int_ptr = &value;

  printf("==> The value from generic casted is: %d\n", *(int *)generic_int_ptr);
}
