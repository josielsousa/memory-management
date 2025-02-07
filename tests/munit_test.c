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

static MunitResult test_new_node(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  node_t *node = new_node(1, NULL);
  assert_int(node->data, ==, 1);
  assert_ptr(node->next, ==, NULL);

  node_t *node2 = new_node(2, node);

  assert_int(node2->data, ==, 2);
  assert_ptr(node2->next, ==, node);
  assert_ptr(node->next, ==, NULL);

  return MUNIT_OK;
}

static MunitResult test_new_node_zero_value(const MunitParameter params[],
                                            void *data) {
  (void)params;
  (void)data;

  node_t *zero = {0};

  node_t *node = new_node(1, zero);
  assert_int(node->data, ==, 1);
  assert_ptr(node->next, ==, NULL);

  return MUNIT_OK;
}

static MunitResult test_new_employee(const MunitParameter params[],
                                     void *data) {
  (void)params;
  (void)data;

  employee_t *employee = new_employee(1, "John Doe", NULL);
  assert_int(employee->id, ==, 1);
  assert_string_equal(employee->name, "John Doe");
  assert_ptr(employee->department, ==, NULL);

  return MUNIT_OK;
}

static MunitResult test_new_department_manager(const MunitParameter params[],
                                               void *data) {
  (void)params;
  (void)data;

  employee_t *manager = new_employee(1, "Mary Jane", NULL);
  assert_int(manager->id, ==, 1);
  assert_string_equal(manager->name, "Mary Jane");
  assert_ptr(manager->department, ==, NULL);

  department_t *department = new_department("Engineering", manager);
  assert_string_equal(department->name, "Engineering");
  assert_ptr(department->manager, !=, NULL);

  // check if the manager is correctly assigned
  assert_string_equal(department->manager->name, "Mary Jane");
  assert_int(department->manager->id, ==, 1);

  employee_t *engineer = new_employee(2, "John Doe", department);
  assert_int(engineer->id, ==, 2);
  assert_string_equal(engineer->name, "John Doe");

  // check if the department is correctly assigned
  assert_ptr(engineer->department, !=, NULL);
  assert_string_equal(engineer->department->name, "Engineering");

  // check if the manager is correctly assigned
  assert_ptr(engineer->department->manager, !=, NULL);
  assert_string_equal(engineer->department->manager->name, "Mary Jane");
  assert_int(engineer->department->manager->id, ==, 1);

  return MUNIT_OK;
}

static MunitResult test_new_department(const MunitParameter params[],
                                       void *data) {
  (void)params;
  (void)data;

  department_t *department = new_department("Engineering", NULL);
  assert_string_equal(department->name, "Engineering");
  assert_ptr(department->manager, ==, NULL);

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
      munit_test("main/test_update_coordinate_z_by_dereference",
                 test_update_coordinate_z_by_dereference),
      munit_test("main/test_update_file", test_update_file),
      munit_test("main/test_concatenate_strings", test_concatenate_strings),
      munit_test("main/test_concatenate_strings_one_empty",
                 test_concatenate_strings_one_empty),
      munit_test("main/test_concatenate_strings_roots",
                 test_concatenate_strings_roots),
      munit_test("main/test_smart_append", test_smart_append),
      munit_test("main/test_smart_append_nullable", test_smart_append_nullable),
      munit_test("main/test_smart_append_overflow", test_smart_append_overflow),
      munit_test("main/test_new_node", test_new_node),
      munit_test("main/test_new_node_zero_value", test_new_node_zero_value),
      munit_test("main/test_new_employee", test_new_employee),
      munit_test("main/test_new_department", test_new_department),
      munit_test("main/test_new_department_manager",
                 test_new_department_manager),

      munit_null_test,
  };

  MunitSuite test_suite = munit_suite(test_suite_tests);

  return munit_suite_main(&test_suite, NULL, argc, argv);
}
