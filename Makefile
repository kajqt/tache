#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA 
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond à toutes les dépendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################
# Ce fichier compile si besoin une bibliothèque statique "image" depuis SRC et
# la met dans LIB. Puis compile les tests dans TEST
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

#Option de compilation
COMPILOPTS = -g -Wall -Wextra -Werror

# chemin d'acces aux librairies (interfaces)
INCDIR = INCLUDES

# Listes de tous les fichiers interfaces
FILEH = $(INCDIR)/$(wildcard *.h)

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# liste des executables
EXECUTABLES = test/test_struct_liste test/test_contour test/test_contour_a_la_volee

# chemin d'acces aux librairies (binaires)
LIBDIR = lib
# options pour l'édition des liens
LDOPTS = -L. -lm

# Nom pour la creation des différentes lib
GEOM2D = $(LIBDIR)/libgeom2d.a

IMAGE = $(LIBDIR)/libimage.a

STRUCT_LISTE = $(LIBDIR)/libstruct_liste.a

CONTOUR = $(LIBDIR)/libcontour.a

#############################################################################
# definition des regles
#############################################################################

########################################################
# la regle par defaut
all : $(EXECUTABLES)

# Règle pour la création de la lib point et vecteur
lgeom2d : $(GEOM2D)

limage : $(IMAGE)

lstruct : $(STRUCT_LISTE)

lcontour : $(CONTOUR)
#############################################################################
# Création de la lib "geom2d"
#############################################################################

$(GEOM2D) : bin/geom2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie geom2d"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "image"
#############################################################################

$(IMAGE) : bin/image.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie image"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "struct_liste"
#############################################################################

$(STRUCT_LISTE) : bin/struct_liste.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie struct_liste"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

#############################################################################
# Création de la lib "contour"
#############################################################################

$(CONTOUR) : bin/contour.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de librairie contour"
	@echo "---------------------------------------------"
	$(AR) rsc $@ $^

########################################################

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
bin/geom2d.o : src/geom2d.c includes/geom2d.h includes/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

bin/image.o : src/image.c includes/image.h includes/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

bin/contour.o : src/contour.c includes/contour.h includes/types_macros.h includes/struct_liste.h src/struct_liste.c includes/geom2d.h src/geom2d.c includes/image.h src/image.c
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

bin/struct_liste.o : src/struct_liste.c includes/struct_liste.h includes/geom2d.h src/geom2d.c includes/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module struct_liste"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

bin/test_struct_liste.o : test/test_struct_liste.c includes/geom2d.h includes/struct_liste.h includes/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_struct_liste"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

bin/test_contour.o : test/test_contour.c includes/geom2d.h src/geom2d.c includes/struct_liste.h src/struct_liste.c includes/image.h includes/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@


bin/test_contour_a_la_volee.o : test/test_contour_a_la_volee.c includes/geom2d.h src/geom2d.c includes/struct_liste.h includes/image.h src/image.c includes/types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_contour_a_la_volee"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $(INCLUDEOPTS) $< -o $@

########################################################
# regles explicites de creation des executables

test/test_struct_liste : bin/test_struct_liste.o $(STRUCT_LISTE) $(GEOM2D)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -L$(LIBDIR) -lgeom2d -o $@

test/test_contour : bin/test_contour.o $(STRUCT_LISTE) $(GEOM2D) $(IMAGE) $(CONTOUR)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) $(LIBDIR)/libstruct_liste.a -L$(LIBDIR) -limage -L$(LIBDIR) -lgeom2d $(LIBDIR)/libcontour.a -o $@

test/test_contour_a_la_volee : bin/test_contour_a_la_volee.o $(STRUCT_LISTE) $(GEOM2D) $(IMAGE) $(CONTOUR)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) $(LIBDIR)/libstruct_liste.a  -L$(LIBDIR) -limage -L$(LIBDIR) -lgeom2d $(LIBDIR)/libcontour.a -o $@



########################################################
# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) bin/*.o

# full clean
fclean : clean
	rm -fR LIB/*.a

re : fclean all
