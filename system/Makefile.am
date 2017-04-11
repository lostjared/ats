lib_LTLIBRARIES=libats.la
libats_includedir=$(includedir)/ats
#libats_include_HEADERS=lexer.hpp function.hpp code.hpp

libats_la_SOURCES=func_convert.cpp func_list.cpp func_remove.cpp function.cpp lexer.cpp code.cpp func_clear.cpp func_display.cpp func_open.cpp func_save.cpp 
libats_la_CXXFLAGS= -O2 -std=c++11 -I$(top_srcdir)/include
libats_la_LDFLAGS=
include_dir=ats/
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA=../ats.pc

