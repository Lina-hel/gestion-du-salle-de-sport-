dnl Process this file with autoconf to produce a configure script.

AC_INIT([gestion_salle_de_sport], [0.1])

AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_PROG_CC
AC_HEADER_STDC

# GTK 2.0
pkg_modules="gtk+-2.0 >= 2.0.0"
PKG_CHECK_MODULES([PACKAGE], [$pkg_modules])
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)

# Gettext
GETTEXT_PACKAGE=gestion_salle_de_sport
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"], [Gettext package.])

ALL_LINGUAS=""
AM_GLIB_GNU_GETTEXT

AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
])

