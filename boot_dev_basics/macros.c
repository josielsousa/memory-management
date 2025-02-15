#include <stdio.h>

// Definição de uma estrutura Coordinate para o exemplo
struct Coordinate {
  int x;
  int y;
  int z;
};

// Macros para asserções (simplificadas para o exemplo)
#define assert_int(actual, operator, expected, message)                        \
  if (!(actual operator expected)) {                                           \
    printf("Assertion failed: %s (expected %d, got %d)\n", message, expected,  \
           actual);                                                            \
  }

// Definição da macro munit_case
#define munit_case(action, test_name, test_block)                              \
  void test_name() {                                                           \
    printf("Running test: %s\n", #test_name);                                  \
    test_block;                                                                \
  }

// Exemplo de uso
munit_case(RUN, test_new_coordinate1, {
  struct Coordinate c;
  c.x = 1;
  c.y = 5;
  c.z = 3;
  assert_int(c.x, ==, 1, "should set x");
  assert_int(c.y, ==, 2, "should set y");
  assert_int(c.z, ==, 3, "should set z");
});

// cc macros.c -o macros.o && ./macros.o
int main() {
  // Executa o teste
  test_new_coordinate1();
  return 0;
}
