#include <stddef.h>

#pragma once
// Hey! this exists and we will define late.
typedef struct SnekObject snek_object_t;

typedef enum SnekObjectKind {
  INTEGER = 1,
  STRING = 2,
  VECTOR3 = 3,
  FLOATS = 4,
  ARRAY = 5,
} snek_object_kind_t;

typedef struct SnekVector {
  snek_object_t *x;
  snek_object_t *y;
  snek_object_t *z;
} snek_vector_t;

typedef struct SnekArray {
  size_t size;
  snek_object_t **elements;
} snek_array_t;

// Onion - a data structure that can store different types of data
// but only one at a time.
// It's like a struct, but all fields share the same memory space.
// The size of the union is the size of the largest field.
typedef union SnekObjectData {
  int v_int;
  float v_float;
  char *v_string;
  snek_vector_t v_vector3;
  snek_array_t v_array;
} snek_object_data_t;

typedef struct SnekObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

void format_object(snek_object_t obj, char *buffer);

snek_object_t new_integer(int value);

snek_object_t new_string(const char *value);
