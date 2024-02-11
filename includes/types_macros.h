/****************************************************************************** 
  declaration de differents types et macros
******************************************************************************/
 
#ifndef _TYPES_MACROS_H_
#define _TYPES_MACROS_H_

#include <stdio.h>
#include <stdlib.h>

/* type booleen */
typedef char bool;
#define false 0
#define true  1

/* type entier positif */
typedef unsigned int UINT;

/* Couleur pour les affichages */
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define BLUBOLD   "\x1B[34;1m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


/* type double */
typedef double coordonnee;

/* macro affichant le message _m_ et s'arretant */
#define ERREUR_FATALE(_m_) \
{ \
fprintf(stderr, "%s\n", _m_); \
exit(1); \
}

/* macro affichant le message _m_ et NE s'arretant PAS*/
#define ERREUR_NON_FATALE(_m_) \
{ \
fprintf(stderr, "%s\n", _m_); \
}

#endif
