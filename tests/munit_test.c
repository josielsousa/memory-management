#define MUNIT_ENABLE_ASSERT_ALIASES
#include "../munit/munit.h"

#include "../boot-dev/c/src/main.h"

// ############################################################################
// Helpers
// ############################################################################
const MunitTest munit_null_test = {.name = NULL,
                                   .test = NULL,
                                   .setup = NULL,
                                   .tear_down = NULL,
                                   .options = MUNIT_TEST_OPTION_NONE,
                                   .parameters = NULL};

MunitTest munit_test(char *name, MunitTestFunc test_func) {
  return (MunitTest){.name = name,
                     .test = test_func,
                     .setup = NULL,
                     .tear_down = NULL,
                     .options = MUNIT_TEST_OPTION_NONE,
                     .parameters = NULL};
}

MunitSuite munit_suite(MunitTest *tests) {
  return (MunitSuite){
      .prefix = (char *)"",
      .tests = tests,
      .suites = NULL,
      .iterations = 1,
      .options = MUNIT_SUITE_OPTION_NONE,
  };
}

// ############################################################################
// Suite Cases - Tests
// ############################################################################

// test_compare_integer - compare an integer to itself
static MunitResult test_compare_integer(const MunitParameter params[],
                                        void *data) {
  (void)params;
  (void)data;

  assert_int(1, ==, 1);

  return MUNIT_OK;
}

// test_get_language - assert that  get_language returns "C"
static MunitResult test_get_language(const MunitParameter params[],
                                     void *data) {
  (void)params;
  (void)data;

  char *language = get_language();
  assert_string_equal(language, "C");

  return MUNIT_OK;
}

// test_new_coordinate - assert that new_coordinate returns a Coordinate
static MunitResult test_new_coordinate(const MunitParameter params[],
                                       void *data) {
  (void)params;
  (void)data;

  struct Coordinate coordinate = new_coordinate(1, 2, 3);
  assert_int(coordinate.x, ==, 1);
  assert_int(coordinate.y, ==, 2);
  assert_int(coordinate.z, ==, 3);

  return MUNIT_OK;
}

// test_scale_coordinate - assert that scale_coordinate returns a Coordinate
static MunitResult test_scale_coordinate(const MunitParameter params[],
                                         void *data) {
  (void)params;
  (void)data;

  struct Coordinate coordinate = new_coordinate(1, 2, 3);
  struct Coordinate scaled = scale_coordinate(coordinate, 2);

  assert_int(scaled.x, ==, 2);
  assert_int(scaled.y, ==, 4);
  assert_int(scaled.z, ==, 6);

  return MUNIT_OK;
}

// test_new_human - assert that new_human returns a Human
static MunitResult test_new_human(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  human_t human = new_human("John Doe", 30, 1);
  assert_string_equal(human.name, "John Doe");
  assert_int(human.age, ==, 30);
  assert_int(human.is_alive, ==, 1);

  return MUNIT_OK;
}

// test_poorly_aligned - assert that poorly_aligned_t is poorly aligned
static MunitResult test_poorly_aligned(const MunitParameter params[],
                                       void *data) {
  (void)params;
  (void)data;

  assert_size(sizeof(poorly_aligned_t), ==, 40);

  return MUNIT_OK;
}

// test_better_aligned - assert that better_aligned_t is better aligned
static MunitResult test_better_aligned(const MunitParameter params[],
                                       void *data) {
  (void)params;
  (void)data;

  assert_size(sizeof(better_aligned_t), ==, 24);

  return MUNIT_OK;
}

static MunitResult test_update_coordinate_x(const MunitParameter params[],
                                            void *data) {
  (void)params;
  (void)data;

  struct Coordinate c = new_coordinate(1, 2, 3);
  update_coordinate_x(c, 4);

  assert_int(c.x, ==, 1);

  return MUNIT_OK;
}

// test_update_and_return_coordinate_x - assert that
// update_and_return_coordinate_x
static MunitResult
test_update_and_return_coordinate_x(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  struct Coordinate c = new_coordinate(1, 2, 3);
  struct Coordinate updated = update_and_return_coordinate_x(c, 4);

  assert_int(updated.x, ==, 4);

  return MUNIT_OK;
}

// test_update_coordinate_y_by_reference - assert that
// updated coordinate y by reference
static MunitResult
test_update_coordinate_y_by_reference(const MunitParameter params[],
                                      void *data) {
  (void)params;
  (void)data;

  struct Coordinate c = new_coordinate(1, 2, 3);
  update_coordinate_y_by_reference(&c, 4);

  assert_int(c.y, ==, 4);

  return MUNIT_OK;
}

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests[] = {
      munit_test("main/test_compate_integer", test_compare_integer),
      munit_test("main/test_get_language", test_get_language),
      munit_test("main/test_new_coordinate", test_new_coordinate),
      munit_test("main/test_scale_coordinate", test_scale_coordinate),
      munit_test("main/test_new_human", test_new_human),
      munit_test("main/test_poorly_aligned", test_poorly_aligned),
      munit_test("main/test_better_aligned", test_better_aligned),
      munit_test("main/test_update_coordinate_x", test_update_coordinate_x),
      munit_test("main/test_update_and_return_coordinate_x",
                 test_update_and_return_coordinate_x),
      munit_test("main/test_update_coordinate_y_by_reference",
                 test_update_coordinate_y_by_reference),
      munit_null_test,
  };

  MunitSuite test_suite = munit_suite(test_suite_tests);

  return munit_suite_main(&test_suite, NULL, argc, argv);
}
