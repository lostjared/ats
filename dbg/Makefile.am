bin_PROGRAMS=ats_dbg
ats_dbg_SOURCES=main.cpp

AM_CPPFLAGS= -O2 -std=c++11  $(all_includes)-I$(top_srcdir)/system/include -I/usr/local/include
ats_dbg_LDADD= $(LDPREFIX) -L../system -lats -lreadline
