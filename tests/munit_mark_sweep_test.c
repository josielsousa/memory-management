#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit/munit.h"
#include "munit_helpers.h"
#include "src/snek_mark_sweep.h"

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

int munit_mark_sweep_tests_cases(int argc,
                                 char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("mark_sweep/test_new_vm", test_new_vm),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
