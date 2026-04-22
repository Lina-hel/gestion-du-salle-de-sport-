## Process this file with automake to produce Makefile.in

INCLUDES = \
        -DPACKAGE_DATA_DIR=\""$(datadir)"\" \
        -DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
        @PACKAGE_CFLAGS@

bin_PROGRAMS = gestion_salle_de_sport

gestion_salle_de_sport_SOURCES = \
        main.c \
        support.c \
        interface.c \
        callbacks.c \
        gestioncours.c \
	coach.c \
	centre.c \
	event.c \
	gestion_membre.c 

include_HEADERS = \
        support.h \
        interface.h \
        callbacks.h \
        gestion_cours.h \
	coach.h \
	centre.h \
	event.h \
	gestion_membre.h

gestion_salle_de_sport_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)
