#include "mark_and_sweep/snek_vm.h"
#include "mark_and_sweep/vm.h"
#include "munit_helpers.h"

static MunitResult test_trace_vector(const MunitParameter params[],
                                     void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  frame_t *frame = vm_new_frame(vm);

  snek_object_t *x = new_snek_integer(vm, 5);
  snek_object_t *y = new_snek_integer(vm, 5);
  snek_object_t *z = new_snek_integer(vm, 5);
  snek_object_t *vector = new_snek_vector(vm, x, y, z);

  // nothing is marked
  assert_false(x->is_marked);
  assert_false(y->is_marked);
  assert_false(z->is_marked);
  assert_false(vector->is_marked);

  // After referencing and marking, the
  // vector should be marked, but not the contents
  frame_reference_object(frame, vector);
  mark(vm);
  assert_true(vector->is_marked);
  assert_false(x->is_marked);
  assert_false(y->is_marked);
  assert_false(z->is_marked);

  // After tracing, the contents should be marked
  trace(vm);
  assert_true(vector->is_marked);
  assert_true(x->is_marked);
  assert_true(y->is_marked);
  assert_true(z->is_marked);

  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

static MunitResult test_trace_array(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  frame_t *frame = vm_new_frame(vm);

  snek_object_t *devs = new_snek_array(vm, 2);
  snek_object_t *josiel = new_snek_string(vm, "Josiel");
  snek_object_t *teej = new_snek_string(vm, "Teej");

  snek_array_set(devs, 0, josiel);
  snek_array_set(devs, 1, teej);

  // nothing is marked
  assert_false(devs->is_marked);
  assert_false(josiel->is_marked);
  assert_false(teej->is_marked);

  // After referencing and marking, the
  // array should be marked, but not the contents
  frame_reference_object(frame, devs);
  mark(vm);
  assert_true(devs->is_marked);
  assert_false(josiel->is_marked);
  assert_false(teej->is_marked);

  // After tracing, the contents should be marked
  trace(vm);
  assert_true(devs->is_marked);
  assert_true(josiel->is_marked);
  assert_true(teej->is_marked);

  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

int munit_traces_tests_cases(int argc,
                             char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("mark_sweep_trace/test_trace_vector", test_trace_vector),
      munit_test("mark_sweep_trace/test_trace_array", test_trace_array),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
