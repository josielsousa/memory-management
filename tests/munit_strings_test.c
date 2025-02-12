#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit/munit.h"
#include "munit_helpers.h"
#include "src/my_strings.h"

static MunitResult test_smart_append(const MunitParameter params[],
                                     void *data) {
  (void)params;
  (void)data;

  TextBuffer buffer = {.length = 0, .buffer = ""};
  int status = smart_append(&buffer, "Hello");
  assert_int(status, ==, 0);
  assert_string_equal(buffer.buffer, "Hello");
  assert_int(buffer.length, ==, 5);

  return MUNIT_OK;
}

static MunitResult test_smart_append_nullable(const MunitParameter params[],
                                              void *data) {
  (void)params;
  (void)data;

  TextBuffer buffer = {0};
  const char *src = {0};

  int status = smart_append(&buffer, src);
  assert_int(status, ==, 1);
  assert_string_equal(buffer.buffer, "");
  assert_int(buffer.length, ==, 0);

  return MUNIT_OK;
}

static MunitResult test_smart_append_overflow(const MunitParameter params[],
                                              void *data) {
  (void)params;
  (void)data;

  TextBuffer buffer = {0};
  const char *src =
      "This is a very long string that will not fit in the buffer because it ";

  int status = smart_append(&buffer, src);
  assert_int(status, ==, 1);
  assert_string_equal(
      buffer.buffer,
      "This is a very long string that will not fit in the buffer beca");
  assert_int(buffer.length, ==, 63);

  return MUNIT_OK;
}

int munit_strings_tests_cases(int argc,
                              char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("strings/test_smart_append", test_smart_append),
      munit_test("strings/test_smart_append_nullable",
                 test_smart_append_nullable),
      munit_test("strings/test_smart_append_overflow",
                 test_smart_append_overflow),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
