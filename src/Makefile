CFLAGS=-g -std=c++17 -O3 -Wall -Werror -Wextra $(shell pkg-config --cflags gtest) 
CFLAGS_GCOV=-g -std=c++17 -Wall -Werror -Wextra $(shell pkg-config --cflags gtest) --coverage 
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
SOURCES=consoleapp.cc consoleview/consoleview.cc controller/controller.cc
SRC_DIR=./
INCLUDES = consoleview/ controller/ containers/ ./ ant_colony_algorithm/ monte_carlo_algorithm/ matrix/ 
HEADERS=*.h
OBJECTS=*.o
MAIN_APP=consoleapp

MAIN_TEST_DIR=./test
TEST_SOURCES = $(MAIN_TEST_DIR)/s21_*.cc 
TEST_PROG=test.out

DEBUG_DIR=./debug
DEBUG_PROG=debug.out
BUILD_DIR=../

LIB1=s21_graph
LIB1_NAME=s21_graph.a
LIB1_SOURCES=s21_graph.cc
LIB1_OBJS=$(LIB1_SOURCES:.cc=.o)

LIB2=s21_graph_algorithms
LIB2_NAME=s21_graph_algorithms.a
LIB2_SOURCES=s21_graph_algorithms.cc ant_colony_algorithm/ant_colony_algorithm.cc ant_colony_algorithm/ant.cc monte_carlo_algorithm/monte_carlo_algorithm.cc
LIB2_OBJS=$(LIB2_SOURCES:.cc=.o)

.SUFFIXES:
.SUFFIXES: .cc .o

all: $(MAIN_APP) 

rebuild: clean all

report/index.html: clean
	$(CC) $(CFLAGS_GCOV) $(INCLUDES:%=-I %) -c $(SRC_DIR)/$(LIB1_SOURCES)
	ar rc $(LIB1_NAME) $(LIB1_OBJS)
	$(CLEAN) lib$(LIB1_NAME)
	ln $(LIB1_NAME) lib$(LIB1_NAME)
	$(CC) $(CFLAGS_GCOV)  $(INCLUDES:%=-I %) -c $(SRC_DIR)/$(LIB2_SOURCES)
	ar rc $(LIB2_NAME) $(notdir $(LIB2_OBJS))
	$(CLEAN) lib$(LIB2_NAME)
	ln $(LIB2_NAME) lib$(LIB2_NAME)
	$(CC) $(CFLAGS_GCOV)  $(INCLUDES:%=-I %) $(TEST_SOURCES) -L. -l$(LIB1) -l$(LIB2) $(CHECK_LIBS) -lgcov -o $(BUILD_DIR)/$(TEST_PROG) 
	$(CLEAN) $(OBJECTS)
	-$(BUILD_DIR)/$(TEST_PROG)
	gcov  -o src/ *.gcda
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	-mkdir $(BUILD_DIR)/report
	genhtml -o $(BUILD_DIR)/report gcov_report.info
	$(CLEAN) $(BUILD_DIR)/$(TEST_PROG)


.cc.o:
	$(CC) $(CFLAGS) $(INCLUDES:%=-I %) -c $< -o $@

$(MAIN_APP): $(SOURCES) $(INCLUDES:%=%*.h) $(LIB1_NAME) $(LIB2_NAME) 
	$(CC) $(CFLAGS) $(INCLUDES:%=-I %) $(LIB1_SOURCES) $(LIB2_SOURCES) -o $(BUILD_DIR)/$@ $^

$(LIB1_NAME): $(LIB1_OBJS) $(INCLUDES:%=%*.h)
	ar rcs lib$@ $^
	[ -e $@ ] && rm $@ || true
	cp lib$@ $@

$(LIB2_NAME): $(LIB2_OBJS) $(INCLUDES:%=%*.h)
	ar rcs lib$@ $^
	[ -e $@ ] && rm $@ || true
	cp lib$@ $@

clean:
	$(CLEAN) $(OBJECTS) */$(OBJECTS) *.a *.gcno *.gcda *.gcov *.info
	$(CLEAN) $(BUILD_DIR)$(OBJECTS) $(BUILD_DIR)*.a $(BUILD_DIR)$(TEST_PROG)
	$(CLEAN) $(BUILD_DIR)report
	$(CLEAN) $(DEBUG_PROG)
	$(CLEAN) ./leaks.log
	$(CLEAN) .clang-format
	$(CLEAN) $(TEST_PROG)
	$(CLEAN) ../consoleapp*
	$(CLEAN) temp.dot

tests: test

test: clean $(TEST_PROG)
	-$(BUILD_DIR)$(TEST_PROG)

$(TEST_PROG): $(TEST_SOURCES) $(SRC_DIR)/$(HEADERS) $(LIB1_NAME) $(LIB2_NAME)
	$(CC) $(CFLAGS) $(INCLUDES:%=-I %) $(TEST_SOURCES) $(CHECK_LIBS) -o $(BUILD_DIR)$(TEST_PROG) -L. -l$(LIB1) -l$(LIB2)


gcov_report: report/index.html
	open report/index.html

check: cpplint cppcheck leaks

cpplint:
	@-clang-format -n -style=google -verbose *.cc *.h */*.cc */*.h
	@-clang-format -n -style=google -verbose $(TEST_SOURCES)

cppcheck:
	@cppcheck --std=c++17 --enable=all  --suppress=missingInclude $(INCLUDES:%=-I %) ./

leaks:  $(TEST_PROG) 
	@$(LEAKS)

valgrind: leaks

.PHONY:  clean
