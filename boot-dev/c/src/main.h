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
