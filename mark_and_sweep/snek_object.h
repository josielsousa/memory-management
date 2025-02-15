#include "snek_mas.h"
#include <stdbool.h>
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
  bool is_marked;
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

void format_object(snek_object_t obj, char *buffer);

bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value);

snek_object_t *snek_array_get(snek_object_t *obj, size_t index);

int snek_length(snek_object_t *obj);

snek_object_t *snek_add(vm_t *vm, snek_object_t *a, snek_object_t *b);

snek_object_t *_new_snek_object(vm_t *vm);

snek_object_t new_integer(vm_t *vm, int value);

snek_object_t new_string(vm_t *vm, const char *value);

snek_object_t *new_snek_integer(vm_t *vm, int value);

snek_object_t *new_snek_float(vm_t *vm, float value);

snek_object_t *new_snek_string(vm_t *vm, const char *value);

snek_object_t *new_snek_vector(vm_t *vm, snek_object_t *x, snek_object_t *y,
                               snek_object_t *z);

snek_object_t *new_snek_array(vm_t *vm, size_t size);

void snek_object_free(snek_object_t *obj);
