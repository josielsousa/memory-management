#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit/munit.h"
#include "munit_helpers.h"
#include "src/enums.h"
#include "src/heap.h"
#include "src/node.h"
#include "src/pointers.h"
#include "src/swaps.h"
#include "src/unions.h"

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

      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL},
  };

  int misc_result = munit_misc_tests_cases(argc, argv);
  if (misc_result != 0) {
    return misc_result;
  }

  int strings_result = munit_strings_tests_cases(argc, argv);
  if (strings_result != 0) {
    return strings_result;
  }

  MunitSuite test_suite = munit_suite(test_suite_tests);

  return munit_suite_main(&test_suite, NULL, argc, argv);
}
