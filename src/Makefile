#This project made by woodsjul

CC = gcc
CFLAGS = -Wall -Wextra -Werror
GCOV_FLAGS = -Wno-coverage-invalid-line-number -fprofile-arcs -ftest-coverage
UNAME := $(shell uname -s)
CHECK_FLAGS = -lcheck -lm -lpthread
ifeq ($(UNAME), Linux)
    CHECK_FLAGS += -lsubunit
endif

SRC = $(wildcard units/*.c)
SRC_TESTS = $(wildcard tests/*.c)

UNIT_TEST_DIR = tests
TESTS_CHECK = $(wildcard $(UNIT_TEST_DIR)/*.c)
TEST_EXEC = tests_matrix

OBJ_DIR = obj
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_TESTS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_TESTS))
GCOV_DIR = gcov_report
REPORT_PATH = $(GCOV_DIR)/report/

all: clean s21_matrix.a

s21_matrix.a: $(OBJ)
# 	@echo "*\c";
	ar rcs $@ $^
# 	@echo "*";
	ranlib $@

$(TEST_EXEC): $(OBJ) $(OBJ_TESTS)
	$(CC) $(CFLAGS) -o $@ $^ $(CHECK_FLAGS) -lm

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
# 	@echo "*\c";
	$(CC) $(CFLAGS) -c $< -o $@

test: all $(TEST_EXEC)
# 	@echo "*";
# 	@echo "Start of all the tests...\n"
	./$(TEST_EXEC)

clean:
	@rm -rf $(GCOV_DIR) $(TEST_EXEC) 
	@rm -rf $(OBJ_DIR) s21_matrix.a

cpptest:
	cppcheck --enable=all --suppress=missingIncludeSystem *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c units/*.c

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.h *.c units/*.c
	clang-format -i *.h *.c units/*.c

run: all
	@rm -rf ./a.out
	@gcc -Werror work.c s21_matrix.a -lm
	@./a.out

mem: run
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./a.out

gcov_report: CFLAGS += $(GCOV_FLAGS)
gcov_report: clean
	@mkdir -p $(GCOV_DIR)
# 	@checkmk $(TESTS_CHECK) > $(UNIT_TEST_DIR)/$(TESTS_C)
	@$(CC) $(CFLAGS) $(GCOV_FLAGS) $(UNIT_TEST_DIR)/$(TESTS_C) $(SRC) -o $(TEST_EXEC) $(CHECK_FLAGS)
	@./$(TEST_EXEC)
	@lcov -t "$(UNIT_TEST_DIR)/$(TEST_EXEC)" -o $(GCOV_DIR)/coverage.info -c -d . --exclude "*.check"
	@lcov --remove $(GCOV_DIR)/coverage.info "*/unit_tests/*" -o $(GCOV_DIR)/coverage.info --ignore-errors unused
	@genhtml -o $(REPORT_PATH) $(GCOV_DIR)/coverage.info
	@echo "<table width="100%"><td class=\"title\" style=\"color: lightgreen; -webkit-text-stroke: 1px black;\">#Project was made by woodsjul</td></table>" >> $(REPORT_PATH)index.html
	@echo "=============================================="
	@echo "Отчёт покрытия успешно сгенерирован!"
	@echo "Откройте в браузере:"
	@echo "file://$(CURDIR)/$(REPORT_PATH)index.html"
	@echo "=============================================="
	@find "$(REPORT_PATH)src" -name "*.html" -type f -exec sh -c 'echo "<table width="100%"><td class=\"title\" style=\"color: lightgreen; -webkit-text-stroke: 1px black;\">#Project was made by woodsjul</td></table>" >> "$$1"' _ {} \;


.PHONY: all clean test gcov_report