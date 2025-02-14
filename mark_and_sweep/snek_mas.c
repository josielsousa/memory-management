#include "snek_mas.h"
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

frame_t *vm_new_frame(vm_t *vm) {
  frame_t *frame = (frame_t *)malloc(sizeof(frame_t));
  if (frame == NULL) {
    return NULL;
  }

  frame->references = new_stack(8);
  if (frame->references == NULL) {
    free(frame);
    return NULL;
  }

  vm_frame_push(vm, frame);
  return frame;
}

void vm_frame_push(vm_t *vm, frame_t *frame) {
  if (vm == NULL || frame == NULL) {
    return;
  }

  stack_push(vm->frames, (void *)frame);
}

void frame_free(frame_t *frame) {
  if (frame == NULL) {
    return;
  }

  free_stack(frame->references);
  free(frame);
}

void vm_track_object(vm_t *vm, void *object) {
  if (vm == NULL || object == NULL) {
    return;
  }

  stack_push(vm->objects, (void *)object);
}
