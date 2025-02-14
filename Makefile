# Compiler
CC = cc

# Folders
SRC_DIR=src
TESTS_DIR=tests
MUNIT_DIR=munit
PROJ_DIR=$(shell pwd)
SRC_MAS_DIR=mark_and_sweep
SHARED_DIR=shared
TESTS_MAS_DIR=mark_and_sweep/tests

# Flags CC compiler
CFLAGS=-Wall -Wextra -I$(MUNIT_DIR) -I$(SRC_DIR)

# Sources
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
SHARED_FILES=$(wildcard $(SHARED_DIR)/*.c)
TEST_FILES=$(wildcard $(TESTS_DIR)/*.c)
MUNIT_FILES=$(MUNIT_DIR)/munit.c $(MUNIT_DIR)/munit.h

SRC_MAS_FILES=$(wildcard $(SRC_MAS_DIR)/*.c)
TEST_MAS_FILES=$(wildcard $(TESTS_MAS_DIR)/*.c)

# Run principal suite test
print:
	@echo "==> printing envs..."
	@echo $(SRC_MAS_FILES)
	@echo $(TEST_MAS_FILES)

# Compile principal suite test
src_test_suite:
	$(CC) $(SHARED_FILES) $(SRC_FILES) $(TEST_FILES) $(MUNIT_FILES) -I$(PROJ_DIR) -o out/src_test_suite.o

# Compile mark and  sweep suite test
mas_test_suite:
	$(CC) $(SHARED_FILES) $(SRC_MAS_FILES) $(TEST_MAS_FILES) $(MUNIT_FILES) -I$(PROJ_DIR) -o out/mas_test_suite.o

# Run principal suite test
test-src: format src_test_suite
	@echo "==> Running src tests..."
	./out/src_test_suite.o

# Run mark and sweep suite test
test-mas: format mas_test_suite
	@echo "==> Running mark and sweep tests..."
	./out/mas_test_suite.o

# Run principal suite test
test: format src_test_suite mas_test_suite
	@echo "==> Running all tests..."
	./out/src_test_suite.o
	./out/mas_test_suite.o

# Clean output files
clean:
	@echo "==> Cleaning output files..."
	rm -f out/*.o
	rm -f boot-dev-basics/*.o

# Generate code style
code-style:
	@echo "==> Generating code-style format..."
	@clang-format -style=llvm -dump-config > .clang-format

# Format code
format: clean
	@echo "==> Formating the code..."
	@clang-format -i $(SRC_FILES) $(SRC_MAS_FILES) $(TEST_FILES)
