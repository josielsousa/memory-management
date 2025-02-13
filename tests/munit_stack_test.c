#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit/munit.h"
#include "munit_helpers.h"
#include "src/stack.h"

static MunitResult test_new_stack(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  stack_t *stack = new_stack(10);
  assert_int(stack->count, ==, 0);
  assert_int(stack->capacity, ==, 10);
  assert_ptr(stack->data, !=, NULL);

  free(stack->data);
  free(stack);

  return MUNIT_OK;
}

int munit_stack_tests_cases(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("stack/test_new_stack", test_new_stack),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
