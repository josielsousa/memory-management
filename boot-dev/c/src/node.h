#pragma once

typedef struct Node node_t;

struct Node {
  int data;
  node_t *next;
};

node_t *new_node(int data, node_t *next);

// Mutual struct references
typedef struct Employee employee_t;
typedef struct Department department_t;

struct Employee {
  int id;
  char *name;
  department_t *department;
};

struct Department {
  char *name;
  employee_t *manager;
};

employee_t *new_employee(int id, char *name, department_t *department);

department_t *new_department(char *name, employee_t *manager);
