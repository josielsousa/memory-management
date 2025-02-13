#include "snek_object.h"
#include <stdlib.h>
#include <string.h>

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;

  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOATS;
  obj->data.v_float = value;

  return obj;
}

snek_object_t *new_snek_string(const char *value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = STRING;
  obj->data.v_string = malloc(strlen(value) + 1);

  if (obj->data.v_string == NULL) {
    return NULL;
  }

  strcpy(obj->data.v_string, value);

  return obj;
}

snek_object_t *new_snek_vector(snek_object_t *x, snek_object_t *y,
                               snek_object_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = VECTOR3;
  obj->data.v_vector3.x = x;
  obj->data.v_vector3.y = y;
  obj->data.v_vector3.z = z;

  return obj;
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = ARRAY;
  obj->data.v_array.size = size;

  snek_object_t **elements = calloc(sizeof(snek_object_t *), size);
  if (elements == NULL) {
    return NULL;
  }

  snek_array_t array = {size, elements};
  obj->data.v_array = array;

  for (size_t i = 0; i < size; i++) {
    obj->data.v_array.elements[i] = NULL;
  }

  return obj;
}

bool snek_array_set(snek_object_t *obj, size_t index, snek_object_t *value) {
  if (obj == NULL || value == NULL || obj->kind != ARRAY) {
    return false;
  }

  if (index >= obj->data.v_array.size) {
    return false;
  }

  obj->data.v_array.elements[index] = value;
  return true;
}

snek_object_t *snek_array_get(snek_object_t *obj, size_t index) {
  if (obj == NULL || obj->kind != ARRAY) {
    return NULL;
  }

  if (index >= obj->data.v_array.size) {
    return NULL;
  }

  return obj->data.v_array.elements[index];
}
