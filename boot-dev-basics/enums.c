#include <stdio.h>

typedef enum BigNumber {
  BIG_NUMBER_1 = 1000,                 // int
  BIGGER_NUMBER = 4294967295,          // unsigned int
  BIGEST_NUMBER = 9223372036854775807, // long

  // in the next example compiler return segmentation fault - overflows
  // BIGEST_NUMBER = 9223372036854775808,
} big_number_t;

typedef enum Color {
  RED,
  GREEN,
  BLUE,
} color_t;

// cc enums.c -o enums.o && ./enums.o
int main() {
  printf("Size of color_t: %zu bytes\n", sizeof(color_t));
  printf("Size of big_number_t: %zu bytes\n", sizeof(big_number_t));
  return 0;
}
