#pragma once

typedef enum SnekObjectKind {
  INTEGER = 1,
  STRING = 2,
  FLOATS = 3,
} snek_object_kind_t;

// Onion - a data structure that can store different types of data
// but only one at a time.
// It's like a struct, but all fields share the same memory space.
// The size of the union is the size of the largest field.
typedef union SnekObjectData {
  int v_int;
  float v_float;
  char *v_string;
} snek_object_data_t;

typedef struct SnekObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

void format_object(snek_object_t obj, char *buffer);

snek_object_t new_integer(int value);

snek_object_t new_string(const char *value);
