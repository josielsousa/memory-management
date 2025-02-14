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

static MunitResult test_stack_push(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  stack_t *stack = new_stack(10);
  int value = 42;
  stack_push(stack, &value);

  assert_int(stack->count, ==, 1);
  assert_int(stack->capacity, ==, 10);
  assert_int(*(int *)stack->data[0], ==, 42);

  free(stack->data);
  free(stack);

  return MUNIT_OK;
}

static MunitResult test_stack_push_double_cap(const MunitParameter params[],
                                              void *data) {
  (void)params;
  (void)data;

  int value = 42;

  stack_t *stack2 = new_stack(2);
  assert_ptr(stack2, !=, NULL);
  assert_int(stack2->count, ==, 0);
  assert_int(stack2->capacity, ==, 2);

  stack_push(stack2, &value);
  stack_push(stack2, &value);

  assert_int(stack2->count, ==, 2);
  assert_int(stack2->capacity, ==, 2);

  stack_push(stack2, &value);
  assert_int(stack2->count, ==, 3);
  assert_int(stack2->capacity, ==, 4);

  free(stack2->data);
  free(stack2);

  return MUNIT_OK;
}

static MunitResult test_stack_pop(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  stack_t *stack = new_stack(10);
  int value = 42;
  stack_push(stack, &value);

  int *popped = stack_pop(stack);
  assert_int(*popped, ==, 42);
  assert_int(stack->count, ==, 0);
  assert_int(stack->capacity, ==, 10);
  assert_ptr(stack->data, !=, NULL);

  free(stack->data);
  free(stack);

  return MUNIT_OK;
}

static MunitResult test_stack_free(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  stack_t *stack = new_stack(10);
  int value = 42;
  stack_push(stack, &value);

  free_stack(stack);

  return MUNIT_OK;
}

static MunitResult test_scary_double_push(const MunitParameter params[],
                                          void *data) {
  (void)params;
  (void)data;

  stack_t *stack = new_stack(2);
  assert_ptr(stack, !=, NULL);
  assert_int(stack->count, ==, 0);
  assert_int(stack->capacity, ==, 2);

  scary_double_push(stack);

  assert_int(stack->count, ==, 2);
  assert_int(stack->capacity, ==, 2);

  // int value = (int)stack->data[0]; // NOLINT
  // assert_int(value, ==, 1337);

  int *ptr2 = (int *)stack->data[1];
  assert_int(*ptr2, ==, 42);

  free_stack(stack);

  return MUNIT_OK;
}

static MunitResult test_remove_nulls(const MunitParameter params[],
                                     void *data) {
  (void)params;
  (void)data;

  stack_t *stack = new_stack(2);
  assert_ptr(stack, !=, NULL);
  assert_int(stack->count, ==, 0);
  assert_int(stack->capacity, ==, 2);

  stack_push(stack, NULL);
  stack_push(stack, NULL);
  stack_push(stack, NULL);

  stack_remove_nulls(stack);

  assert_int(stack->count, ==, 0);
  assert_int(stack->capacity, ==, 4);

  free_stack(stack);

  return MUNIT_OK;
}

int munit_stack_tests_cases(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("stack/test_new_stack", test_new_stack),
      munit_test("stack/test_stack_push", test_stack_push),
      munit_test("stack/test_stack_push_double_cap",
                 test_stack_push_double_cap),
      munit_test("stack/test_stack_pop", test_stack_pop),
      munit_test("stack/test_stack_free", test_stack_free),
      munit_test("stack/test_scary_double_push", test_scary_double_push),
      munit_test("stack/test_remove_nulls", test_remove_nulls),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
