#include <stdio.h>

typedef struct coordinate {
  int x;
  int y;
} coordinate_t;

coordinate_t new_coordinate(int x, int y) {
  coordinate_t c;
  c.x = x;
  c.y = y;

  // when returning a pointer to a local variable
  // the same pointer was used to allocate the memory every time.
  // So, only the last value will be returned.
  // to fix it, we can evict the pointer and return the struct.
  //
  // return &c;

  return c;
}

// cc pointer_to_stack.c -o stack.o && ./stack.o
int main() {
  coordinate_t c1 = new_coordinate(10, 20);
  coordinate_t c2 = new_coordinate(30, 40);
  coordinate_t c3 = new_coordinate(50, 60);

  printf("coordinate: %d, %d\n", c1.x, c1.y);
  printf("coordinate: %d, %d\n", c2.x, c2.y);
  printf("coordinate: %d, %d\n", c3.x, c3.y);

  return 0;
}
