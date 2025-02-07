#include "main.h"
#include "string.h"

// new_coordinate - create a new Coordinate
struct Coordinate new_coordinate(int x, int y, int z) {
  return (struct Coordinate){
      .x = x,
      .y = y,
      .z = z,
  };
}

// scale_coordinate - scale a Coordinate by a factor
struct Coordinate scale_coordinate(struct Coordinate c, int factor) {
  return (struct Coordinate){
      .x = c.x * factor,
      .y = c.y * factor,
      .z = c.z * factor,
  };
}

// new_human - create a new Human
human_t new_human(char *name, int age, int is_alive) {
  return (human_t){
      .name = name,
      .age = age,
      .is_alive = is_alive,
  };
}

// update_coordinate_x - update the x-coordinate of a Coordinate but do not
// return it
void update_coordinate_x(struct Coordinate c, int x) {
  (void)c; // disable unused warning from compiler

  c.x = x;
}

// update_and_return_coordinate_x - update the x-coordinate of a Coordinate and
// return it
struct Coordinate update_and_return_coordinate_x(struct Coordinate c, int x) {
  c.x = x;

  return c;
}

// update_coordinate_y_by_reference - update the y-coordinate of a Coordinate by
// reference
void update_coordinate_y_by_reference(struct Coordinate *c, int y) { c->y = y; }

// update_coordinate_z_by_dereference - update the z-coordinate of a Coordinate
// by dereference the pointer received and return the new Coordinate.
struct Coordinate update_coordinate_z_by_dereference(struct Coordinate *c,
                                                     int z) {
  struct Coordinate new_c = *c;
  new_c.z = z;

  return new_c;
}

// Complete the `update_file` function to update the file data with the new file
// type and number of lines. The file data is an array of 200 integers. The
// first integer is the file type, and the second integer is the number of lines
// in the file, and the 199 index shoud be 0. The function should not return
void update_file(int filedata[200], int new_file_type, int new_num_lines) {
  filedata[1] = new_file_type;
  filedata[2] = new_num_lines;
  filedata[199] = 0;
}

// concat_strings - concatenate two strings and return the result.
void concat_strings_strcat(char *dst, char *src) { strcat(dst, src); }

// concat_strings_roots - concatenate two strings and return the result.
void concat_strings_roots(char *dst, char *src) {
  // find the end of the destination string (null terminator)
  while (*dst != '\0') {
    dst++;
  }

  // copy the source string to the destination string
  while (1) {
    // make sure add the null terminator to the destination string
    *dst = *src;
    dst++;
    src++;

    if (*src == '\0') {
      break;
    }
  }
}
