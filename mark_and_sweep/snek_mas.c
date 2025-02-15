#include "snek_mas.h"
#include "vm.h"
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

void vm_track_object(vm_t *vm, snek_object_t *object) {
  if (vm == NULL || object == NULL) {
    return;
  }

  stack_push(vm->objects, object);
}

void frame_reference_object(frame_t *frame, snek_object_t *object) {
  if (frame == NULL || object == NULL) {
    return;
  }

  stack_push(frame->references, object);
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

// - If object is `NULL` or `is_marked` is `true`, return.
//
// - Otherwise set `is_marked` to `true` and push the object onto the
// `gray_objects`
//
void trace_mark_object(stack_t *gray_objects, snek_object_t *object) {
  if (object == NULL || gray_objects == NULL || object->is_marked) {
    return;
  }

  object->is_marked = true;
  stack_push(gray_objects, object);
}

// - If the object if an `INTEGER`, `FLOATS`, or `STRING`, we don't need to do
// anything.
//
// - If the object is a `VECTOR3` - call the `trace_mark_object` on the `x`,
// `y`, and `z` fields.
//
// - If the object is an `ARRAY`, call the `trace_mark_object` on each element
// in the array.
//
void trace_blacken_object(stack_t *gray_objects, snek_object_t *object) {
  if (object == NULL || gray_objects == NULL) {
    return;
  }

  switch (object->kind) {
  case INTEGER:
    return;
  case FLOATS:
    return;
  case STRING:
    return;
  case VECTOR3:
    trace_mark_object(gray_objects, object->data.v_vector3.x);
    trace_mark_object(gray_objects, object->data.v_vector3.y);
    trace_mark_object(gray_objects, object->data.v_vector3.z);
    return;
  case ARRAY:
    for (int i = 0; i < object->data.v_array.size; i++) {
      trace_mark_object(gray_objects, snek_array_get(object, i));
    }
    return;
  }
}

// - Create a new stack with a capacity of 8 called `gray_objects`. If the
//   allocation fails, return.
//
// - Iterate over each the onbject in the VM;
//   - If the object is `is_marked` put it onto the `gray_objects` stack.
//
// - While the `gray_objects` stack is not empty;
//   - Pop the object off the stack.
//   - Call `trace_blacken_object` on the object.
//
// - Free the `gray_objects` stack.
//
void trace(vm_t *vm) {
  if (vm == NULL) {
    return;
  }

  stack_t *gray_objects = new_stack(8);
  if (gray_objects == NULL) {
    return;
  }

  for (int i = 0; i < vm->objects->count; i++) {
    snek_object_t *object = vm->objects->data[i];
    if (object->is_marked) {
      stack_push(gray_objects, object);
    }
  }

  while (gray_objects->count > 0) {
    snek_object_t *object = stack_pop(gray_objects);
    trace_blacken_object(gray_objects, object);
  }

  free_stack(gray_objects);
}
