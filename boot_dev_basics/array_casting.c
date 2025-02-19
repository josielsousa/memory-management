#include <stdio.h>

typedef struct {
  int fps;
  int height;
  int width;
} graphics_t;

// dump_graphics - percorre o array de graphics fazendo um casting
// para um ponteiro de inteiros e imprime os valores
// dos campos de cada struct.
void dump_graphics(graphics_t graphics[10]) {
  int *ptr = (int *)graphics; // cast to int pointer

  // (10 * 3) = 10 is the numebr of elements in the array
  // and 3 is the number of fields in the struct

  for (int i = 0; i < (10 * 3); i++) {
    printf("settings[%d] = %d\n", i, ptr[i]);
  }
}

// In C language, the pointers are always the same size, because they just
// represent a memory address.
// The size of a pointer is 4 bytes in a 32-bit system and
// 8 bytes in a 64-bit system.
void pointers_size() {
  int *ptr;
  char *ptr3;
  double *ptr2;

  printf("==> Size of int pointer: %zu\n", sizeof(ptr));
  printf("==> Size of char pointer: %zu\n", sizeof(ptr3));
  printf("==> Size of double pointer: %zu\n", sizeof(ptr2));
}

// In C language, the size of an array is the size of the data type multiplied
// by the number of elements in the array.
// Now the size is equals to size of the array and the size of the data type.
void pointers_size_array() {
  int intArray[10];       // 10 elements of 4 bytes each == 40 bytes
  char charArray[10];     // 10 elements of 1 byte each  == 10 bytes
  double doubleArray[10]; // 10 elements of 8 bytes each == 80 bytes

  printf("==> Size of int array pointer: %zu\n", sizeof(intArray));
  printf("==> Size of char array pointer: %zu\n", sizeof(charArray));
  printf("==> Size of double array pointer: %zu\n", sizeof(doubleArray));
}

// cc array_casting.c -o array_casting.o && ./array_casting.o
int main() {
  graphics_t graphics[10] = {{.fps = 60, .height = 1380, .width = 2160},
                             {.fps = 75, .height = 1440, .width = 2560},
                             {.fps = 120, .height = 1080, .width = 720},
                             {.fps = 144, .height = 1080, .width = 1920},
                             {.fps = 160, .height = 1080, .width = 1920},
                             {.fps = 240, .height = 1080, .width = 1920},
                             {.fps = 300, .height = 1080, .width = 1920},
                             {.fps = 360, .height = 1080, .width = 1920},
                             {.fps = 500, .height = 1080, .width = 1920},
                             {.fps = 900, .height = 1080, .width = 1920}};

  dump_graphics(graphics);
  pointers_size();
  pointers_size_array();
}
