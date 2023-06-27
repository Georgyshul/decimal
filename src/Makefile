CC          = gcc
SRC_DIR     = .
TEST_DIR    = tests
TEST_FLAGS := --coverage -c -g

SRC  := $(shell find $(SRC_DIR) -name "s21*.c" | sed -e 's/\.\///')
TEST := $(shell find $(TEST_DIR) -name "*.c" | sed -e 's/\.\///')

BUILD_DIR      = obj
BUILD_TEST_DIR = obj_test

OBJS      := $(SRC:%.c=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST:%.c=$(BUILD_TEST_DIR)/%.o)

CFLAGS=-Wall -Wextra -std=c11 -g -lm
LFLAGS    ?= $(shell pkg-config --cflags --libs check)
INC_CHECK ?= $(shell pkg-config --cflags --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage

DEC_TEST  := decimal_test.c

GCOV_DIR	:=gcov_report

all: s21_decimal.a test

test: s21_decimal.a $(TEST_OBJS) $(BUILD_TEST_DIR)/main.o
	$(CC) $(CFLAGS) $(TEST_OBJS) s21_decimal.a $(BUILD_TEST_DIR)/main.o $(LFLAGS) -o test.out
	./test.out

s21_decimal.a: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rc s21_decimal.a $(OBJS)
	ranlib s21_decimal.a

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_TEST_DIR)/main.o: $(DEC_TEST) 
	@mkdir -p $(BUILD_TEST_DIR)
	$(CC) $(CFLAGS) $(INC_CHECK) -c -o $(BUILD_TEST_DIR)/main.o $(DEC_TEST)

$(BUILD_TEST_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_CHECK) -c $^ -o $@

# $(GCOV_OBJ_DIR)/%.o: %.c
# 	@mkdir -p $(dir $@)
# 	$(CC) $(TEST_FLAGS) -c $< -o $@

# gcov_report: clean
# 	$(CC) $(CFLAGS) $(GCOVFLAGS) $(SRC) $(LFLAGS) -o gcov.out
# 	./gcov.out
# 	lcov --capture --directory . --output-file coverage.info
# 	genhtml coverage.info --output-directory gcov_report
# 	open $(GCOV_DIR)/index.html
# 	rm -Rf *.gcda *.cov *.gcno *.info

# .PHONY: clean rebuild lint test
clean: 
	rm -f *.gcda *.gcov *.o *.gcno
	rm -f s21_decimal.a
	rm -rf $(BUILD_DIR)
	rm -rf $(BUILD_TEST_DIR)
	rm -rf $(GCOV_OBJ_DIR)
	rm -f test.out

rebuild: clean all

lint:
	# Sorry! Open source doesn't include lint check.
	# -cp ../materials/linters/CPPLINT.cfg .
	# -find . -type f -name "*.c" | xargs python3 ../materials/linters/cpplint.py --extensions=c
	# -find . -type f -name "*.h" | xargs python3 ../materials/linters/cpplint.py --extensions=c
	# -find . -type f -name "*.c" | xargs cppcheck --enable=all --suppress=missingIncludeSystem
	# rm -f CPPLINT.cfg

