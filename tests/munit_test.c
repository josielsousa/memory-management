#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit/munit.h"
#include "src/enums.h"
#include "src/heap.h"
#include "src/main.h"
#include "src/my_strings.h"
#include "src/node.h"
#include "src/pointers.h"
#include "src/swaps.h"
#include "src/unions.h"

// ############################################################################
// Helpers
// ############################################################################
//
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

  free(node2);
  free(node);

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

  free(node);

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

  free(engineer);
  free(department);
  free(manager);

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

static MunitResult test_enum_day_of_week(const MunitParameter params[],
                                         void *data) {
  (void)params;
  (void)data;

  event_t event = {.name = "Meeting", .day = MONDAY};
  assert_string_equal(event.name, "Meeting");
  assert_int(event.day, ==, MONDAY);
  assert_int(SUNDAY, ==, 1);
  assert_int(MONDAY, ==, 2);
  assert_int(SATURDAY, ==, 7);

  return MUNIT_OK;
}

static MunitResult test_enum_color(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  color_t color = GREEN;
  assert_int(color, ==, 127);
  assert_int(RED, ==, 83);
  assert_int(GREEN, !=, BLUE);

  return MUNIT_OK;
}

static MunitResult test_enum_http_status(const MunitParameter params[],
                                         void *data) {
  (void)params;
  (void)data;

  http_status_t status = STATUS_OK;
  assert_int(status, ==, 200);
  assert_int(STATUS_OK, ==, 200);
  assert_int(STATUS_BAD_REQUEST, ==, 400);
  assert_int(STATUS_INTERNAL_SERVER_ERROR, ==, 500);

  return MUNIT_OK;
}

static MunitResult test_enum_http_status_to_str(const MunitParameter params[],
                                                void *data) {
  (void)params;
  (void)data;

  char *status = http_to_str(STATUS_OK);
  assert_string_equal(status, "200 OK");

  status = http_to_str(STATUS_BAD_REQUEST);
  assert_string_equal(status, "400 Bad Request");

  status = http_to_str(STATUS_FORBIDDEN);
  assert_string_equal(status, "403 Forbidden");

  status = http_to_str(STATUS_NOT_FOUND);
  assert_string_equal(status, "404 Not Found");

  status = http_to_str(STATUS_INTERNAL_SERVER_ERROR);
  assert_string_equal(status, "500 Internal Server Error");

  status = http_to_str(600);
  assert_string_equal(status, "Unknown");

  return MUNIT_OK;
}

static MunitResult test_unions_snek_object(const MunitParameter params[],
                                           void *data) {
  (void)params;
  (void)data;

  snek_object_t obj = new_integer(42);
  assert_int(obj.kind, ==, INTEGER);
  assert_int(obj.data.v_int, ==, 42);

  snek_object_t obj2 = new_string("Hello");
  assert_int(obj2.kind, ==, STRING);
  assert_string_equal(obj2.data.v_string, "Hello");

  char buffer[15];
  format_object(obj, buffer);
  assert_string_equal(buffer, "integer:42\n");

  format_object(obj2, buffer);
  assert_string_equal(buffer, "string:Hello\n");

  snek_object_t obj_unknown = {0};
  format_object(obj_unknown, buffer);
  assert_string_equal(buffer, "unknown\n");

  return MUNIT_OK;
}

static MunitResult test_is_pointer_on_stack(const MunitParameter params[],
                                            void *data) {
  (void)params;
  (void)data;

  int value = 42;
  int *ptr = &value;

  assert_true(is_on_stack(ptr));

  employee_t *engineer = new_employee(2, "John Doe", NULL);
  assert_false(is_on_stack(engineer));
  free(engineer);

  return MUNIT_OK;
}

static MunitResult test_allocate_scallar_list(const MunitParameter params[],
                                              void *data) {
  (void)params;
  (void)data;

  int *list = allocate_scallar_list(5, 2);
  int expected[5] = {0, 2, 4, 6, 8};

  for (int i = 0; i < 5; i++) {
    assert_int(list[i], ==, expected[i]);
  }

  free(list);

  return MUNIT_OK;
}

static MunitResult
test_allocate_scallar_list_zero(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  int *list = allocate_scallar_list(5, 0);
  int expected[5] = {0, 0, 0, 0, 0};

  for (int i = 0; i < 5; i++) {
    assert_int(list[i], ==, expected[i]);
  }

  free(list);

  return MUNIT_OK;
}

static MunitResult test_snek_zero_out(const MunitParameter params[],
                                      void *data) {
  (void)params;
  (void)data;

  snek_int_t integer = {.name = "value", .value = 42};
  snek_zero_out(&integer, INT);
  assert_int(integer.value, ==, 0);

  snek_float_t floating = {.name = "value", .value = 3.14};
  snek_zero_out(&floating, FLOAT);
  assert_float(floating.value, ==, 0.0);

  snek_bool_t boolean = {.name = "value", .value = true};
  snek_zero_out(&boolean, BOOL);
  assert_false(boolean.value);

  return MUNIT_OK;
}

static MunitResult test_swap_ints(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  int a = 10;
  int b = 20;

  swap_ints(&a, &b);

  assert_int(a, ==, 20);
  assert_int(b, ==, 10);

  return MUNIT_OK;
}

static MunitResult test_swap_strings(const MunitParameter params[],
                                     void *data) {
  (void)params;
  (void)data;

  char *a = "Hello";
  char *b = "World";

  swap_strings(&a, &b);

  assert_string_equal(a, "World");
  assert_string_equal(b, "Hello");

  return MUNIT_OK;
}

static MunitResult test_swap(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  int a = 10;
  int b = 20;

  swap(&a, &b, sizeof(int));

  assert_int(a, ==, 20);
  assert_int(b, ==, 10);

  // swap strings
  char *str1 = "Hello";
  char *str2 = "World";

  swap(&str1, &str2, sizeof(char *));
  assert_string_equal(str1, "World");
  assert_string_equal(str2, "Hello");

  // swap custom type
  snek_int_t integer1 = {.name = "value", .value = 42};
  snek_int_t integer2 = {.name = "value", .value = 24};

  swap(&integer1, &integer2, sizeof(snek_int_t));
  assert_int(integer1.value, ==, 24);
  assert_int(integer2.value, ==, 42);

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
      munit_test("main/test_enum_day_of_week", test_enum_day_of_week),
      munit_test("main/test_enum_color", test_enum_color),
      munit_test("main/test_enum_http_status", test_enum_http_status),
      munit_test("main/test_enum_http_status_to_str",
                 test_enum_http_status_to_str),
      munit_test("main/test_unions_snek_object", test_unions_snek_object),
      munit_test("main/test_is_pointer_on_stack", test_is_pointer_on_stack),
      munit_test("main/test_allocate_scallar_list", test_allocate_scallar_list),
      munit_test("main/test_allocate_scallar_list_zero",
                 test_allocate_scallar_list_zero),
      munit_test("main/test_snek_zero_out", test_snek_zero_out),
      munit_test("main/test_swap_ints", test_swap_ints),
      munit_test("main/test_swap_strings", test_swap_strings),
      munit_test("main/test_swap", test_swap),

      munit_null_test,
  };

  MunitSuite test_suite = munit_suite(test_suite_tests);

  return munit_suite_main(&test_suite, NULL, argc, argv);
}
