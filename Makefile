# Compilador
CC = cc

# Diretórios
SRC_DIR = boot-dev/c/src
TESTS_DIR = tests
MUNIT_DIR = munit/

# Flags do compilador
CFLAGS = -Wall -Wextra -I$(MUNIT_DIR) -I$(SRC_DIR)

# Arquivos fonte
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TESTS_DIR)/*.c)
MUNIT_FILES = $(MUNIT_DIR)/munit.c

# Regra para compilar a suite de testes
test_suite: $(SRC_FILES) $(TEST_FILES) $(MUNIT_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) $(TEST_FILES) $(MUNIT_FILES) -o out/test_suite.o

# Regra para rodar os testes
test: test_suite
	./out/test_suite.o

# Limpar arquivos gerados
clean:
	rm -f out/test_suite.o
