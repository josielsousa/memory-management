#include "munit_helpers.h"
#include "src/enums.h"
#include "src/node.h"

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

int munit_structs_enums_cases(int argc,
                              char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("strenums/test_new_node", test_new_node),
      munit_test("strenums/test_new_node_zero_value", test_new_node_zero_value),
      munit_test("strenums/test_new_employee", test_new_employee),
      munit_test("strenums/test_new_department", test_new_department),
      munit_test("strenums/test_new_department_manager",
                 test_new_department_manager),
      munit_test("strenums/test_enum_day_of_week", test_enum_day_of_week),
      munit_test("strenums/test_enum_color", test_enum_color),
      munit_test("strenums/test_enum_http_status", test_enum_http_status),
      munit_test("strenums/test_enum_http_status_to_str",
                 test_enum_http_status_to_str),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
