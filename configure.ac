AC_PREREQ([2.64])
AC_INIT(ats, 1.0, lostjared@lostsidedead.com)
AC_CONFIG_HEADERS(config.h)
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE
AM_PROG_AS
AC_LANG_CPLUSPLUS
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_PID_T
AC_FUNC_FORK


AC_SEARCH_LIBS([readline], [readline], [], [
  AC_MSG_ERROR([unable to find the readline() function install libreadline])
])
enable_dbg=no
AC_ARG_ENABLE(debug,
[   --enable-debug              DebugMode ],enable_dbg=yes)

if test x$enable_dbg = xyes; then
	AC_DEFINE_UNQUOTED(DEBUG_MODE, 1, [debug])
	echo "debug mode:  enabled"
fi

AC_OUTPUT(Makefile system/Makefile ats.pc dbg/Makefile)
