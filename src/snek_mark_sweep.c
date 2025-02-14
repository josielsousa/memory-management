#include "snek_mark_sweep.h"
#include <stdlib.h>

vm_t *vm_new(void) {
  vm_t *vm = (vm_t *)malloc(sizeof(vm_t));
  if (vm == NULL) {
    return NULL;
  }

  vm->frames = new_stack(8);
  if (vm->frames == NULL) {
    free(vm);
    return NULL;
  }

  vm->objects = new_stack(8);
  if (vm->objects == NULL) {
    free_stack(vm->frames);
    free(vm);
    return NULL;
  }

  return vm;
}

void vm_free(vm_t *vm) {
  if (vm == NULL) {
    return;
  }

  free_stack(vm->frames);
  free_stack(vm->objects);
  free(vm);
}
