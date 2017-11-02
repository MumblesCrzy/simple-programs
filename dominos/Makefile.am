AUTOMAKE_OPTIONS = subdir-objects
AUTOMAKE_OPTIONS += foreign

bin_PROGRAMS = bin/dominos

INCLUDES = \
    -I ../ \
	-I ./src/

shared_SOURCES = \
	src/solution.cpp
	
bin_dominos_SOURCES = \
	src/main.cpp \
    $(shared_SOURCES)

bin_dominos_CXXFLAGS = $(DEPS_CFLAGS)

bin_dominos_LDFLAGS = \
    $(DEPS_LIBS)
