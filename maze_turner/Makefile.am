AUTOMAKE_OPTIONS = subdir-objects
AUTOMAKE_OPTIONS += foreign

bin_PROGRAMS = bin/maze_turner

INCLUDES = \
    -I ../ \
	-I ./src/

shared_SOURCES = \
	src/maze_turner.cpp
	
bin_maze_turner_SOURCES = \
	src/main.cpp \
    $(shared_SOURCES)

bin_maze_turner_CXXFLAGS = $(DEPS_CFLAGS)

bin_maze_turner_LDFLAGS = \
    $(DEPS_LIBS)
