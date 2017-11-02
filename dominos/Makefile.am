AUTOMAKE_OPTIONS = subdir-objects
AUTOMAKE_OPTIONS += foreign

bin_PROGRAMS = bin/program1

INCLUDES = \
    -I ../ \
	-I ./src/

shared_SOURCES = \
	src/solution.cpp
	
bin_program1_SOURCES = \
	src/main.cpp \
    $(shared_SOURCES)

bin_program1_CXXFLAGS = $(DEPS_CFLAGS)

bin_program1_LDFLAGS = \
    $(DEPS_LIBS)

TESTS = unit_tests/test_all
check_PROGRAMS = unit_tests/test_all

unit_tests_test_all_SOURCES = \
    unit_tests/main.cpp \
    unit_tests/Program1Test.cpp \
    $(shared_SOURCES)

unit_tests_test_all_CXXFLAGS = $(DEPS_CFLAGS)

unit_tests_test_all_LDFLAGS = \
    $(DEPS_LIBS) \
    $(shell gtest-config --ldflags) \
    $(shell gtest-config --libs)
