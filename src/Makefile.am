## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir). \
	$(EIGEN3_CFLAGS). \
	$(BLITZ_CFLAGS). \
	$(BLITZ_CFLAGS)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gcode

gcode_SOURCES = \
	main.cc \
	mcode.cxx \
	mcode.h \
	filereader.h \
	filereader.cxx \
	header.h \
	header.cxx \
	gcodeobjet.cc \
	gcodeobjet.h \
	irrlicht_function.cxx \
	irrlicht_function.h \
	trackball.cc \
	trackball.h \
	CSceneGcodeNode.cc \
	CSceneGcodeNode.h

gcode_LDFLAGS =  \
	-lIrrlicht \
	-lGL

gcode_LDADD =  \
	$(BLITZ_LIBS) \
	$(EIGEN3_LIBS)


