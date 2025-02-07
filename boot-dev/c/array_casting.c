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

// cc boot-dev/c/array_casting.c -o out/array_casting.o && ./out/array_casting.o
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
}
