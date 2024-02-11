#ifndef _GEOM2D_H_
#define _GEOM2D_H_

#include <types_macros.h>


typedef struct Point_ {
    coordonnee x;
    coordonnee y;
}Point;

typedef struct Vecteur_ {
    coordonnee x;
    coordonnee y;
}Vecteur;

/******************/
/* initialisation */
/******************/

/* cree le point de coordonnées (x, y) et utilisable pour depuis l'origine vers un point */
Point set_point (coordonnee x, coordonnee y);

/* vecteur correspondant au bipoint AB */
Vecteur vect_bipoint(Point A, Point B);

/*--------------------------------------------------------------------------------------------------------*/

/*********/
/* Somme */
/*********/

/* somme dess points P1 + P2 */
Point add_point (Point P1, Point P2);

/* somme des vecteurs V1 et V2 */
Vecteur add_vect(Vecteur V1, Vecteur V2);

/*--------------------------------------------------------------------------------------------------------*/

/********/
/* Mult */
/********/

/* produit du point P par un reel (double) */
Point mult_scalaire_point(Point P, double lambda);

/* produit du vecteur V par un reel (double) */
Vecteur mult_scalaire_vect(Vecteur V, double lambda);

/* Pruduit scalaire entre V1 et V2 */
double prod_scal(Vecteur V1, Vecteur V2);

/*--------------------------------------------------------------------------------------------------------*/

/*********************/
/* Norme et distance */
/*********************/

/* renvoie la norme du vecteur V */
double norme(Vecteur V);

/* renvoie la distance entre les point P1 et P2 */
double distance(Point P1, Point P2);

/*--------------------------------------------------------------------------------------------------------*/

#endif
