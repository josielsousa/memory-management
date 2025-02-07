#include "node.h"
#include <stdlib.h>

node_t *new_node(int data, node_t *next) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->data = data;
  node->next = next;

  return node;
}
