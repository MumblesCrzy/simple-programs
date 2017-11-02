AUTOMAKE_OPTIONS = subdir-objects
AUTOMAKE_OPTIONS += foreign

bin_PROGRAMS = bin/unique_binary_tree

INCLUDES = \
    -I ../ \
	-I ./src/

shared_SOURCES = \
	src/binary_tree.cpp \
	src/solution.cpp
	
bin_unique_binary_tree_SOURCES = \
	src/main.cpp \
    $(shared_SOURCES)

bin_unique_binary_tree_CXXFLAGS = $(DEPS_CFLAGS)

bin_unique_binary_tree_LDFLAGS = \
    $(DEPS_LIBS)