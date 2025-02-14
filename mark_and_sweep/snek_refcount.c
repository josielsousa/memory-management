#include "snek_object.h"
#include <stdlib.h>

snek_object_t *_new_snek_object(void) {
  snek_object_t *obj = calloc(1, sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  return obj;
}
