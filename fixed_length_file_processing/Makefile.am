AUTOMAKE_OPTIONS = subdir-objects
AUTOMAKE_OPTIONS += foreign

bin_PROGRAMS = bin/fixed_length_file_processing

INCLUDES = \
    -I ../ \
	-I ./src/

shared_SOURCES = \
	src/file_processing.cpp
	
bin_fixed_length_file_processing_SOURCES = \
	src/main.cpp \
    $(shared_SOURCES)

bin_fixed_length_file_processing_CXXFLAGS = $(DEPS_CFLAGS)

bin_fixed_length_file_processing_LDFLAGS = \
    $(DEPS_LIBS)
