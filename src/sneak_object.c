#include "sneak_object.h"
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
