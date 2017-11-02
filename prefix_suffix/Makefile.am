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
