#pragma once

#include "stack.h"

// Mark and Sweep Garbage Collection
// The mark and sweep algorithm is a simple garbage collection algorithm that
// works by marking all objects that are reachable from the root set and then
// sweeping all objects that are not marked. This is a simple algorithm that
// works well for small programs, but can be slow for large programs.
//
// ## Pros of MaS
// - Can detect and collect cycles
// - Reduces potential performance degradation in higly multi-threaded programs.
//   - refcounting requires atomic updates for thread safety.
// - Can be implemented in a single pass.
//
// ## Cons of MaS
// - Can cause "stop the world" pauses, when a lot of objects are allocated.
// - More complex to implement than refcounting.
// - Higher memory overhead than refcounting.

// The Virtual Machine
typedef struct VirtualMachine {
  stack_t *frames;
  stack_t *objects;
} vm_t;

// To prevent us from shooting ourselves in the foot, we will create some
// functions that are more type safe and make it much more difficult to do the
// wrong thing when interacting with our vm_t.
typedef struct StackFrame {
  stack_t *references;
} frame_t;

vm_t *vm_new(void);

void vm_free(vm_t *vm);

frame_t *vm_new_frame(vm_t *vm);

void vm_frame_push(vm_t *vm, frame_t *frame);

void frame_free(frame_t *frame);
