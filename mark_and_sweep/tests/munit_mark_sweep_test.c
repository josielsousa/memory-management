#include "mark_and_sweep/snek_mas.h"
#include "mark_and_sweep/snek_object.h"
#include "munit_helpers.h"

static MunitResult test_new_vm(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  assert_not_null(vm);

  assert_not_null(vm->frames);
  assert_int(vm->frames->count, ==, 0);
  assert_int(vm->frames->capacity, ==, 8);

  assert_not_null(vm->objects);
  assert_int(vm->objects->count, ==, 0);
  assert_int(vm->objects->capacity, ==, 8);

  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

static MunitResult test_new_frame(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  assert_not_null(vm);

  frame_t *frame = vm_new_frame(vm);
  assert_not_null(frame);
  assert_int(vm->frames->count, ==, 1);

  assert_not_null(frame->references);
  assert_int(frame->references->count, ==, 0);
  assert_int(frame->references->capacity, ==, 8);

  frame_free(frame);
  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

static MunitResult test_new_object(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  assert_not_null(vm);

  snek_object_t *obj = new_snek_integer(vm, 42);
  assert_not_null(obj);
  assert_int(obj->kind, ==, INTEGER);
  assert_int(obj->data.v_int, ==, 42);

  assert_int(vm->objects->count, ==, 1);

  free(obj);
  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

int munit_mark_sweep_tests_cases(int argc,
                                 char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("mark_sweep/test_new_vm", test_new_vm),
      munit_test("mark_sweep/test_new_frame", test_new_frame),
      munit_test("mark_sweep/test_new_object", test_new_object),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
