# Compilador
CC = cc

# Diretórios
SRC_DIR = boot-dev/c/src
TESTS_DIR = tests
MUNIT_DIR = munit

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
test: format test_suite
	@echo "==> Executando suite de testes..."
	./out/test_suite.o

# Limpar arquivos gerados
clean:
	@echo "==> Limpando o output..."
	rm -f out/*.o

# Gerar arquivo de configuração de estilo de código
code-style:
	@echo "==> Gerando o código..."
	@clang-format -style=llvm -dump-config > .clang-format

# Formatar o código
format: clean
	@echo "==> Formatando o código..."
	@clang-format -i $(SRC_FILES) $(TEST_FILES)
