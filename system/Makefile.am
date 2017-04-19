lib_LTLIBRARIES=libats.la
libats_includedir=$(includedir)/ats
libats_include_HEADERS=include/code.hpp include/function.hpp include/lexer.hpp include/symbol.hpp

libats_la_SOURCES=func_convert.cpp func_list.cpp func_remove.cpp func_symbols.cpp func_symbol.cpp func_unsym.cpp function.cpp lexer.cpp code.cpp func_clear.cpp func_display.cpp func_open.cpp func_save.cpp func_execute.cpp textline.cpp code_func.cpp code_cls.cpp symbol.cpp variable.cpp icode.cpp
libats_la_CXXFLAGS=-O2 -std=c++11 -I$(top_srcdir)/system/include
libats_la_LDFLAGS=
include_dir=ats/
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA=../ats.pc

