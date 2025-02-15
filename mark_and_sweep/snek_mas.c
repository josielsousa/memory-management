#include "snek_mas.h"
#include "snek_object.h"
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

void frame_free(frame_t *frame) {
  if (frame == NULL) {
    return;
  }

  free_stack(frame->references);
  free(frame);
}

void vm_free(vm_t *vm) {
  if (vm == NULL) {
    return;
  }

  for (size_t i = 0; i < vm->frames->count; i++) {
    frame_free((frame_t *)vm->frames->data[i]);
  }
  free_stack(vm->frames);

  for (size_t i = 0; i < vm->objects->count; i++) {
    snek_object_free((snek_object_t *)vm->objects->data[i]);
  }
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

void vm_track_object(vm_t *vm, void *object) {
  if (vm == NULL || object == NULL) {
    return;
  }

  stack_push(vm->objects, (void *)object);
}

void frame_reference_object(frame_t *frame, void *object) {
  if (frame == NULL || object == NULL) {
    return;
  }

  stack_push(frame->references, (void *)object);
}

// 1. iterate over each frame in the VM
// 2. iterate over each references object in each frame
// 3. mark the objects as `is_marked = true`
void mark(vm_t *vm) {
  if (vm == NULL) {
    return;
  }

  for (int i = 0; i < vm->frames->count; i++) {
    frame_t *frame = vm->frames->data[i];

    for (int j = 0; j < frame->references->count; j++) {
      snek_object_t *obj = frame->references->data[j];
      obj->is_marked = true;
    }
  }
}
