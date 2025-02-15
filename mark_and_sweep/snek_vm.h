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
//
// Mark and Sweep garbage collection was first described by John McCarthy in
// 1960, primarily for managing memory in Lisp programs. It's a two-phase
// algorithm:
//
// 1. Mark phase: The garbage collector traverses the object graph, starting
//   from the root set, marking all objects that are reachable.
// 2. Sweep phase: The garbage collector sweeps through the heap, freeing all
//  objects that are not marked.
//
//  NOTE: We don't need to track how many times an object is referenced, but
//  instead check at garbage collection time if each object is referenced in
//  each `stack_frame` and traverse our container objects looking for any other
//  referenced objects.

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
