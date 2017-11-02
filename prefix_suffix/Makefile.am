AUTOMAKE_OPTIONS = subdir-objects
AUTOMAKE_OPTIONS += foreign

bin_PROGRAMS = bin/prefix_suffix

INCLUDES = \
    -I ../ \
	-I ./src/

shared_SOURCES = \
	src/prefix_suffix.cpp
	
bin_prefix_suffix_SOURCES = \
	src/main.cpp \
    $(shared_SOURCES)

bin_prefix_suffix_CXXFLAGS = $(DEPS_CFLAGS)

bin_prefix_suffix_LDFLAGS = \
    $(DEPS_LIBS)

TESTS = unit_tests/test_all
check_PROGRAMS = unit_tests/test_all

unit_tests_test_all_SOURCES = \
    unit_tests/main.cpp \
    unit_tests/prefix_suffixTest.cpp \
    $(shared_SOURCES)

unit_tests_test_all_CXXFLAGS = $(DEPS_CFLAGS)

unit_tests_test_all_LDFLAGS = \
    $(DEPS_LIBS) \
    $(shell gtest-config --ldflags) \
    $(shell gtest-config --libs)
