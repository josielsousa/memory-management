#include <stdio.h>

// cc lesson_03.c -o lesson_03.o && ./lesson_03.o
int main() {
  int max_recursive_calls = 2;
  char io_mode = 'w';
  float throtle_speed = 0.2;

  // array of characters(aka char star) == string
  char *name = "lesson_03.c";

  printf("Max recursive calls: %d\n", max_recursive_calls);
  printf("IO mode: %c\n", io_mode);
  printf("Throtle speed: %f\n", throtle_speed);
  printf("Name: %s\n", name);

  const float pi = 3.14159;
  printf("Pi: %f\n", pi);
}
