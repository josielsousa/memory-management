#include "mark_and_sweep/snek_vm.h"
#include "mark_and_sweep/vm.h"
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
  assert_false(obj->is_marked);

  assert_int(vm->objects->count, ==, 1);
  assert_ptr_equal(vm->objects->data[0], obj);

  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

static MunitResult test_snek_object_free(const MunitParameter params[],
                                         void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  assert_not_null(vm);

  snek_object_t *obj = new_snek_integer(vm, 42);
  assert_not_null(obj);
  assert_int(obj->kind, ==, INTEGER);
  assert_int(obj->data.v_int, ==, 42);
  assert_false(obj->is_marked);

  assert_int(vm->objects->count, ==, 1);
  assert_ptr_equal(vm->objects->data[0], obj);

  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

static MunitResult
test_frame_object_one_reference(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  frame_t *frame = vm_new_frame(vm);

  snek_object_t *lanes_wpm = new_snek_integer(vm, 9);
  assert_false(lanes_wpm->is_marked);
  frame_reference_object(frame, lanes_wpm);

  assert_int(frame->references->count, ==, 1);
  assert_ptr_equal(frame->references->data[0], lanes_wpm);

  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

static MunitResult test_frames_are_freed(const MunitParameter params[],
                                         void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  vm_new_frame(vm);
  vm_new_frame(vm);
  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

static MunitResult
test_frame_object_multiple_references(const MunitParameter params[],
                                      void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  frame_t *frame = vm_new_frame(vm);

  snek_object_t *lanes_wpm = new_snek_integer(vm, 9);
  assert_false(lanes_wpm->is_marked);

  snek_object_t *master_wpm = new_snek_integer(vm, 190);
  assert_false(master_wpm->is_marked);

  frame_reference_object(frame, lanes_wpm);
  frame_reference_object(frame, master_wpm);

  assert_int(frame->references->count, ==, 2);
  assert_ptr_equal(frame->references->data[0], lanes_wpm);
  assert_ptr_equal(frame->references->data[1], master_wpm);

  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

static MunitResult test_mark(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  vm_t *vm = vm_new();
  frame_t *frame = vm_new_frame(vm);

  snek_object_t *lanes_wpm = new_snek_integer(vm, 9);
  assert_false(lanes_wpm->is_marked);

  snek_object_t *master_wpm = new_snek_integer(vm, 190);
  assert_false(master_wpm->is_marked);

  snek_object_t *name = new_snek_string(vm, "name");
  assert_false(name->is_marked);

  frame_reference_object(frame, lanes_wpm);
  frame_reference_object(frame, master_wpm);
  frame_reference_object(frame, name);

  mark(vm);

  assert_true(lanes_wpm->is_marked);
  assert_true(master_wpm->is_marked);
  assert_true(name->is_marked);

  vm_free(vm);
  assert(1);

  return MUNIT_OK;
}

int munit_mark_phase_tests_cases(int argc,
                                 char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("mark_sweep/test_new_vm", test_new_vm),
      munit_test("mark_sweep/test_new_frame", test_new_frame),
      munit_test("mark_sweep/test_new_object", test_new_object),
      munit_test("mark_sweep/test_snek_object_free", test_snek_object_free),
      munit_test("mark_sweep/test_frames_are_freed", test_frames_are_freed),
      munit_test("mark_sweep/test_frame_object_one_reference",
                 test_frame_object_one_reference),
      munit_test("mark_sweep/test_frame_object_multiple_references",
                 test_frame_object_multiple_references),
      munit_test("mark_sweep/test_mark", test_mark),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
