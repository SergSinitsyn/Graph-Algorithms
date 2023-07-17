CFLAGS=-std=c++17 -Wall -Werror -Wextra $(shell pkg-config --cflags gtest) 
CLEAN=rm -rf
uname_S := $(shell uname -s)
ifeq ($(uname_S), Linux)
	CHECK_LIBS=$(shell pkg-config --libs gtest) -lm
	CC=g++
	LEAKS=valgrind --undef-value-errors=yes --leak-check=full -s $(BUILD_DIR)/$(TEST_PROG)
	SHOW_LEAKS=grep "ERROR SUMMARY" leaks.log
else
	CHECK_LIBS=-lgtest -lm
	CC=g++
	LEAKS=CK_FORK=no leaks --atExit -- $(BUILD_DIR)/$(TEST_PROG)
	SHOW_LEAKS=cat leaks.log
endif
SOURCES=*.cc
SRC_DIR=./
HEADERS=*.h
OBJECTS=*.o

MAIN_TEST_DIR=./test
TEST_SOURCES = $(MAIN_TEST_DIR)/s21_*.cc 
TEST_PROG=test.out

DEBUG_DIR=./debug
DEBUG_PROG=debug.out
BUILD_DIR=./

LIB1=s21_graph
LIB1_NAME=s21_graph.a
LIB1_SOURCES=s21_graph.cc
LIB1_HEADERS=(s21_graph.h)
LIB1_OBJS=$(LIB1_SOURCES:.cc=.o)

.SUFFIXES:
.SUFFIXES: .cc .o

all: clean test 

rebuild: clean all

.cc.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB1_NAME): $(LIB1_OBJS)
	ar rcs lib$@ $(LIB1_OBJS)
	cp lib$@ $@

clean:
	$(CLEAN) $(OBJECTS) *.a *.gcno *.gcda *.gcov *.info
	$(CLEAN) $(BUILD_DIR)$(OBJECTS) $(BUILD_DIR)*.a $(BUILD_DIR)$(TEST_PROG)
	$(CLEAN) $(BUILD_DIR)report
	$(CLEAN) $(DEBUG_PROG)
	$(CLEAN) ./leaks.log
	$(CLEAN) .clang-format
	$(CLEAN) test.out test.out*
	$(CLEAN) $(LIB1_OBJS) $(LIB1_NAME) lib$(LIB1_NAME)

test: $(TEST_PROG)
	-$(BUILD_DIR)/$(TEST_PROG)

$(TEST_PROG): $(TEST_SOURCES) $(SRC_DIR)/$(HEADERS) $(LIB1_NAME)
	$(CC) $(CFLAGS) -g $(TEST_SOURCES) $(CHECK_LIBS) -o $(BUILD_DIR)$(TEST_PROG) -L. -l$(LIB1)

report/index.html:
	make clean
	$(CC) $(CFLAGS) -g -fprofile-arcs -ftest-coverage -fPIC $(TEST_SOURCES) $(CHECK_LIBS) -lgcov -o $(BUILD_DIR)/$(TEST_PROG)
	$(CLEAN) $(OBJ)
	-$(BUILD_DIR)/$(TEST_PROG)
	gcov -o src/ *.gcda
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	-mkdir $(BUILD_DIR)/report
	genhtml -o $(BUILD_DIR)/report gcov_report.info
	$(CLEAN) $(BUILD_DIR)/$(TEST_PROG)

gcov_report: report/index.html
	open report/index.html

# проверки
check: cpplint cppcheck

cpplint:
	cp ../materials/linters/.clang-format ./
	-clang-format -n *.h */*.cc */*/*.h
	-clang-format -n $(TEST_SOURCES)
	rm .clang-format

cppcheck:
	cppcheck --std=c++17 --enable=all --suppress=syntaxError --suppress=missingInclude --suppress=noExplicitConstructor  --suppress=unreadVariable ./

leaks:  $(TEST_PROG) 
	# $(CC) $(CFLAGS) -D_NO_EXCEPTIONS -g $(TEST_SOURCES) $(CHECK_LIBS) -o $(BUILD_DIR)/$(TEST_PROG) 
	$(LEAKS)
	# $(LEAKS) > leaks.log 2>&1
	# $(SHOW_LEAKS)

valgrind: leaks

.PHONY:  clean
