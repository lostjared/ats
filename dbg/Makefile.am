bin_PROGRAMS=dbg
dbg_SOURCES=main.cpp

AM_CPPFLAGS= -O2 -std=c++11  $(CFLAGPREFIX) $(all_includes)-I$(top_srcdir)/system/include
dbg_LDADD= $(LDPREFIX) -L../system -lats 
