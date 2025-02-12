#include "pointers.h"
#include <stdbool.h>

void snek_zero_out(void *ptr, sneks_object_kind_t kind) {
  switch (kind) {
  case INT:
    ((snek_int_t *)ptr)->value = 0;
    break;
  case FLOAT:
    ((snek_float_t *)ptr)->value = 0.0;
    break;
  case BOOL:
    ((snek_bool_t *)ptr)->value = false;
    break;
  }
}
