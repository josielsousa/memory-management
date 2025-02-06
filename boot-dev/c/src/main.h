// #pragma once - evita que essas definições sejam incluídas mais de uma vez

#pragma once

char *get_language();

struct Coordinate {
  int x;
  int y;
  int z;
};

struct Human {
  char *name;
  int age;
  int is_alive;
};

struct Coordinate new_coordinate(int x, int y, int z);

struct Coordinate scale_coordinate(struct Coordinate c, int scale);
