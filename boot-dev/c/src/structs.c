#include "main.h"

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
void update_coordinate_x(struct Coordinate c, int x) { c.x = x; }

// update_and_return_coordinate_x - update the x-coordinate of a Coordinate and
// return it
struct Coordinate update_and_return_coordinate_x(struct Coordinate c, int x) {
  c.x = x;

  return c;
}
