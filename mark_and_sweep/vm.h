#include "snek_object.h"
#include "stack.h"

vm_t *vm_new(void);

void vm_free(vm_t *vm);

frame_t *vm_new_frame(vm_t *vm);

void vm_frame_push(vm_t *vm, frame_t *frame);

void frame_free(frame_t *frame);

// We are no longer going  to track how many times an object is referenced, but
// instead check at garbage collection time if each object is referenced at all.
// If it is, keep it, if not, free it.
void vm_track_object(vm_t *vm, snek_object_t *object);

void frame_reference_object(frame_t *frame, snek_object_t *object);

// In some mark and sweep implementations, you'll see different ways to mark
// `root objects` - the object directly referenced by the stack frames. However,
// in our simplicist VM it's a bit easier to find and mark all of the directly
// objects.
//
// 1. iterate over each frame in the VM
// 2. iterate over each references object in each frame
// 3. mark the objects as `is_marked = true`
//
void mark(vm_t *vm);

/*
 * In this example, we create a list that references itself. This is a simple
 * example of a circular reference. When we run the garbage collector, it should
 * be able to detect this circular reference and free the memory.
 *
 * ```python
 *     def get_list():
 *         a = []
 *         a.append(a)
 *         return [5]
 *
 *     print(get_list())
 * ```
 *
 * - Create a new stack with a capacity of 8 called `gray_objects`. If the
 *   allocation fails, return.
 *
 * - Iterate over each the onbject in the VM;
 *   - If the object is `is_marked` put it onto the `gray_objects` stack.
 *
 * - While the `gray_objects` stack is not empty;
 *   - Pop the object off the stack.
 *   - Call `trace_blacken_object` on the object.
 *
 * - Free the `gray_objects` stack.
 */
void trace(vm_t *vm);

// - If the object if an `INTEGER`, `FLOATS`, or `STRING`, we don't need to do
// anything.
//
// - If the object is a `VECTOR3` - call the `trace_mark_object` on the `x`,
// `y`, and `z` fields.
//
// - If the object is an `ARRAY`, call the `trace_mark_object` on each element
// in the array.
//
void trace_blacken_object(stack_t *gray_objects, snek_object_t *object);

// - If object is `NULL` or `is_marked` is `true`, return.
//
// - Otherwise set `is_marked` to `true` and push the object onto the
// `gray_objects`
//
void trace_mark_object(stack_t *gray_objects, snek_object_t *object);
