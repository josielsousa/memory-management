#include "mark_and_sweep/snek_vm.h"
#include "mark_and_sweep/vm.h"
#include "munit_helpers.h"

static MunitResult test_sweep_simple_case(const MunitParameter params[],
                                          void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  frame_t *frame = vm_new_frame(vm);

  snek_object_t *phrase = new_snek_string(vm, "Hello, World!");
  frame_reference_object(frame, phrase);
  vm_garbage_collector(vm);

  // nothing should be collected, we haven't freed the frame reference.
  assert_int(vm->objects->count, ==, 1);

  // now we free the frame reference
  frame_free(vm_frame_pop(vm));
  vm_garbage_collector(vm);
  assert(1);

  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

static MunitResult test_sweep_complete_case(const MunitParameter params[],
                                            void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  frame_t *frame1 = vm_new_frame(vm);
  frame_t *frame2 = vm_new_frame(vm);
  frame_t *frame3 = vm_new_frame(vm);

  snek_object_t *s1 = new_snek_string(vm, "This string is going to frame 1!");
  frame_reference_object(frame1, s1);

  snek_object_t *s2 = new_snek_string(vm, "This string is going to frame 2!");
  frame_reference_object(frame2, s2);

  snek_object_t *s3 = new_snek_string(vm, "This string is going to frame 3!");
  frame_reference_object(frame3, s3);

  snek_object_t *i1 = new_snek_integer(vm, 1);
  snek_object_t *i2 = new_snek_integer(vm, 2);
  snek_object_t *i3 = new_snek_integer(vm, 3);
  snek_object_t *v = new_snek_vector(vm, i1, i2, i3);
  frame_reference_object(frame2, v);
  frame_reference_object(frame3, v);

  assert_int(vm->objects->count, ==, 7);

  // only free the top frame (frame3)
  frame_free(vm_frame_pop(vm));
  vm_garbage_collector(vm);
  assert_int(vm->objects->count, ==, 6);

  // free the rest of the frames
  // only free the top frame (frame2)
  frame_free(vm_frame_pop(vm));

  // only free the top frame (frame1)
  frame_free(vm_frame_pop(vm));
  vm_garbage_collector(vm);
  assert(1);

  assert_int(vm->objects->count, ==, 0);

  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

int munit_sweep_phase_tests_cases(int argc,
                                  char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest table_tests[] = {
      munit_test("sweep/simple_case", test_sweep_simple_case),
      munit_test("sweep/complete_case", test_sweep_complete_case),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite suite = munit_suite(table_tests);

  return munit_suite_main_custom(&suite, NULL, argc, argv, NULL);
}
