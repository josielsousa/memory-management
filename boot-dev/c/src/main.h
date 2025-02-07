#include "my_strings.h"

// #pragma once - evita que essas definições sejam incluídas mais de uma vez

#pragma once

struct Coordinate {
  int x;
  int y;
  int z;
};

typedef struct Human {
  char *name;
  int age;
  int is_alive;
} human_t;

// Memory layout
// poorly_aligned_t - nesse exemplo a struct é mal alinhada
// char a; -> 4 byte
// padding -> 4 byte
// double b; -> 8 bytes
// char c; -> 4 byte
// char d; -> 4 byte
// long e; -> 8 bytes
// char f; -> 4 byte
// padding -> 4 byte
// nesse ela vai ser alocada em um espaço maior, pois o compilador vai adicionar
// bytes de padding para alinhar os tipos de dados.
typedef struct {
  char a;
  double b;
  char c;
  char d;
  long e;
  char f;
} poorly_aligned_t;

// better_aligned_t - nesse exemplo a struct é bem alinhada
// double b; -> 8 bytes
// long e; -> 8 bytes
// char a; -> 1 byte
// char c; -> 1 byte
// char d; -> 1 byte
// char f; -> 1 byte
// padding -> 4 byte
// nesse caso a struct vai ser alocada em um espaço menor, pois o compilador
// não vai adicionar bytes de padding para alinhar os tipos de dados.
typedef struct {
  double b;
  long e;
  char a;
  char c;
  char d;
  char f;
} better_aligned_t;

char *get_language();

struct Coordinate new_coordinate(int x, int y, int z);

struct Coordinate scale_coordinate(struct Coordinate c, int scale);

human_t new_human(char *name, int age, int is_alive);

void update_coordinate_x(struct Coordinate c, int x);

struct Coordinate update_and_return_coordinate_x(struct Coordinate c, int x);

void update_coordinate_y_by_reference(struct Coordinate *c, int y);

struct Coordinate update_coordinate_z_by_dereference(struct Coordinate *c,
                                                     int z);

// Complete the `update_file` function to update the file data with the new file
// type and number of lines.
// The `1` index is the file type
// The `2` index is the number of lines
// The `199` index always should be `0`
void update_file(int filedata[200], int new_file_type, int new_num_lines);

void concat_strings_strcat(char *dst, char *src);

void concat_strings_roots(char *dst, char *src);
