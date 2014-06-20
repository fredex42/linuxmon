#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([linuxmon],[0.9],[andy.gallagher@theguardian.com])
AM_INIT_AUTOMAKE(linuxmon,0.9)
AC_CONFIG_SRCDIR([.])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([libpqxx],[libpqxx])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h malloc.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
#AC_CHECK_HEADER_STDBOOL
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gethostname memset pow])

AC_OUTPUT([Makefile])
