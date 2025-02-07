#include "node.h"
#include <stdlib.h>

// new_node - create a new node
node_t *new_node(int data, node_t *next) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->data = data;
  node->next = next;

  return node;
}

// new_employee - create a new employee
employee_t *new_employee(int id, char *name, department_t *department) {
  employee_t *employee = (employee_t *)malloc(sizeof(employee_t));
  employee->id = id;
  employee->name = name;
  employee->department = department;

  return employee;
}

// new_department - create a new department
department_t *new_department(char *name, employee_t *manager) {
  department_t *department = (department_t *)malloc(sizeof(department_t));
  department->name = name;
  department->manager = manager;

  return department;
}
