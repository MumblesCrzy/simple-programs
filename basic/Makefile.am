AUTOMAKE_OPTIONS = subdir-objects
AUTOMAKE_OPTIONS += foreign

bin_PROGRAMS = bin/program

INCLUDES = \
    -I ../ \
	-I ./src/

shared_SOURCES = \
	src/program.cpp
	
bin_program_SOURCES = \
	src/main.cpp \
    $(shared_SOURCES)

bin_program_CXXFLAGS = $(DEPS_CFLAGS)

bin_program_LDFLAGS = \
    $(DEPS_LIBS)
