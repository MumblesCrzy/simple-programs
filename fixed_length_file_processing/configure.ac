# autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_INIT(configure.ac)
AC_PREREQ(2.59)

MAJOR_VERSION=0
MINOR_VERSION=0
MICRO_VERSION=1

PACKAGE=program1
VERSION=$MAJOR_VERSION.$MINOR_VERSION.$MICRO_VERSION
RELEASE=$MAJOR_VERSION.$MINOR_VERSION

AC_SUBST(MAJOR_VERSION)
AC_SUBST(MINOR_VERSION)
AC_SUBST(LT_VERSION)

AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE($PACKAGE, $VERSION)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_LANG_CPLUSPLUS

AM_PROG_LIBTOOL

# PKG-CONFIG NEW
PKG_PROG_PKG_CONFIG()
#PKG_CHECK_MODULES(DEPS)

# C++ Defines
OUR_FLAGS="-m64"
CPPFLAGS="$CPPFLAGS $OUR_FLAGS"

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h sys/time.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset fopen64])

AC_CONFIG_FILES([ Makefile ])
AC_OUTPUT
