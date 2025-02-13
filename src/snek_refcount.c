#include "snek_object.h"
#include <stdlib.h>

void refcount_decr(snek_object_t *obj) {
  if (obj == NULL) {
    return;
  }

  obj->refcount--;
  if (obj->refcount == 0) {
    refcount_free(obj);
  }
}

void refcount_free(snek_object_t *obj) {
  if (obj == NULL) {
    return;
  }

  switch (obj->kind) {
  case INTEGER:
    free(obj);
    break;
  case FLOATS:
    free(obj);
    break;
  case STRING:
    free(obj->data.v_string);
    free(obj);
    break;
  case VECTOR3:
    // refcount_decr(obj->data.v_vector3.x);
    // refcount_decr(obj->data.v_vector3.y);
    // refcount_decr(obj->data.v_vector3.z);
  case ARRAY:
    for (size_t i = 0; i < obj->data.v_array.size; i++) {
      refcount_decr(obj->data.v_array.elements[i]);
    }
    free(obj);
    break;
  }
}

void refcount_incr(snek_object_t *obj) {
  if (obj == NULL) {
    return;
  }

  obj->refcount++;
}

snek_object_t *_new_snek_object(void) {
  snek_object_t *obj = calloc(1, sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->refcount = 1;
  return obj;
}
