#include "snek_object.h"
#include <stdlib.h>

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
