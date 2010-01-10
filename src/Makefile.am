## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/player/ui
ui_DATA = player.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(PLAYER_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = player

player_SOURCES = \
	main.cc \
	main-window.h \
	main-window.cc \
	main-notebook.h \
	main-notebook.cc

player_LDFLAGS = 

player_LDADD = $(PLAYER_LIBS)

EXTRA_DIST = $(ui_DATA)

SUBDIRS = \
	widgets

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/player
