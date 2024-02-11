#include <stdio.h>
#include <math.h> 
#include "geom2d.h"
#include"types_macros.h"


/******************/
/* initialisation */
/******************/

/* cree le point de coordonnées (x, y) et utilisable pour depuis l'origine vers un point */
Point set_point (coordonnee x, coordonnee y){
    Point P = {x, y};
    return P;
}

/* vecteur correspondant au bipoint AB */
Vecteur vect_bipoint(Point A, Point B){
    Vecteur V = {B.x - A.x, B.y - A.y};
    return V;
}

/*--------------------------------------------------------------------------------------------------------*/

/*********/
/* Somme */
/*********/

/* somme dess points P1 + P2 */
Point add_point (Point P1, Point P2){
    Point P = {P1.x + P2.x, P1.y + P2.y};
    return P;
}

/* somme des vecteurs V1 et V2 */
Vecteur add_vect(Vecteur V1, Vecteur V2){
    Vecteur V = {V1.x + V2.x, V1.y + V2.y};
    return V;
}

/*--------------------------------------------------------------------------------------------------------*/

/********/
/* Mult */
/********/

/* produit du point P par un reel (double) */
Point mult_scalaire_point(Point P, double lambda){
    Point Pt = {lambda * P.x, lambda * P.y};
    return Pt;
}

/* produit du vecteur V par un reel (double) */
Vecteur mult_scalaire_vect(Vecteur V, double lambda){
    Vecteur Vect = {lambda * V.x, lambda * V.y};
    return Vect;
}

/* Pruduit scalaire entre V1 et V2 */
double prod_scal(Vecteur V1, Vecteur V2){
    return ((V1.x * V2.x) + (V1.y * V2.y));
}

/*--------------------------------------------------------------------------------------------------------*/

/*********************/
/* Norme et distance */
/*********************/

/* renvoie la norme du vecteur V */
double norme(Vecteur V){
    return sqrt(prod_scal(V, V));
}

/* renvoie la distance entre les point P1 et P2 */
double distance(Point P1, Point P2){
    return sqrt(pow(P2.x - P1.x, 2.) + pow(P2.y - P1.y, 2.));
}

/*--------------------------------------------------------------------------------------------------------*/
