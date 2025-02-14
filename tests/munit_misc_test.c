#include "munit_helpers.h"
#include "src/main.h"

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

// test_update_coordinate_z_by_dereference - assert that
// updated coordinate z by dereference the pointer received.
static MunitResult
test_update_coordinate_z_by_dereference(const MunitParameter params[],
                                        void *data) {
  (void)params;
  (void)data;

  struct Coordinate c = new_coordinate(1, 2, 3);
  struct Coordinate updated = update_coordinate_z_by_dereference(&c, 4);

  assert_int(updated.z, ==, 4);

  return MUNIT_OK;
}

// test_update_file - assert that update_file updates the file data
// with the new file type and number of lines.
static MunitResult test_update_file(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  int file_data[200] = {0};
  update_file(file_data, 1, 150);
  assert_int(file_data[1], ==, 1);
  assert_int(file_data[2], ==, 150);
  assert_int(file_data[199], ==, 0);

  return MUNIT_OK;
}

static MunitResult test_concatenate_strings(const MunitParameter params[],
                                            void *data) {
  (void)params;
  (void)data;

  char str1[20] = "Hello ";
  char *str2 = "World";
  concat_strings_strcat(str1, str2);

  assert_string_equal(str1, "Hello World");

  return MUNIT_OK;
}

static MunitResult
test_concatenate_strings_one_empty(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  // NOTE: the source string should be greater than the resulting string
  // otherwise the strcat function will not work and return a segmentation
  char str1[100] = "Hello";
  char *str2 = "";
  concat_strings_strcat(str1, str2);
  assert_string_equal(str1, "Hello");

  // NOTE: in this next example, the strcat function returns a segmentation
  // fault because the source string is smaller than the resulting string
  // char *str1 = ""; or char str1[5] = "";
  // char *str2 = "Hello";
  // assert_string_equal(str1, "Hello");

  return MUNIT_OK;
}

static MunitResult test_concatenate_strings_roots(const MunitParameter params[],
                                                  void *data) {
  (void)params;
  (void)data;

  char str1[20] = "Hello ";
  char *str2 = "World";
  concat_strings_roots(str1, str2);

  assert_string_equal(str1, "Hello World");

  return MUNIT_OK;
}

int munit_misc_tests_cases(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("misc/test_compare_integer", test_compare_integer),
      munit_test("misc/test_get_language", test_get_language),
      munit_test("misc/test_new_coordinate", test_new_coordinate),
      munit_test("misc/test_scale_coordinate", test_scale_coordinate),
      munit_test("misc/test_new_human", test_new_human),
      munit_test("misc/test_poorly_aligned", test_poorly_aligned),
      munit_test("misc/test_better_aligned", test_better_aligned),
      munit_test("misc/test_update_coordinate_x", test_update_coordinate_x),
      munit_test("misc/test_update_and_return_coordinate_x",
                 test_update_and_return_coordinate_x),
      munit_test("misc/test_update_coordinate_y_by_reference",
                 test_update_coordinate_y_by_reference),
      munit_test("misc/test_update_coordinate_z_by_dereference",
                 test_update_coordinate_z_by_dereference),
      munit_test("misc/test_update_file", test_update_file),
      munit_test("misc/test_concatenate_strings", test_concatenate_strings),
      munit_test("misc/test_concatenate_strings_one_empty",
                 test_concatenate_strings_one_empty),
      munit_test("misc/test_concatenate_strings_roots",
                 test_concatenate_strings_roots),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
