#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include <image.h>
#include <types_macros.h>
#include <struct_liste.h>

//definition de l'orientation
typedef enum {NORD, SUD, EST, OUEST} Orientation;

//definition du robot
typedef struct Robot_ {
    Orientation o;  //orientation courante du robot
    Point pt;       //coordonnée courante du robot 
}Robot;

/* initialise un robot qui a pour coordonnée (x,y) est une orientaion vers
** l'Est */
Robot init_robot(Point p);


/* fais avancer le robot d'une case en fonction de son orientation */
Point avancer_robot(Robot R);


/* Les 4 fonction pixel_NW/NE/SW/SE renvoie la coordonné du pixel a la position voulu (NW = nord ouest...) en fonction de la position du robot */
Point pixel_NW(Point P);

Point pixel_NE(Point P);

Point pixel_SW(Point P);

Point pixel_SE(Point P);


/* La fonction rot_90 renvoie l'orientation apres une rotation de 90 degres
** dans le ses trigonometrique */
/* Le fonction rot_n_90 fais le meme sorte de rotation mais n fais */
Orientation rot_90(Orientation O);

Orientation rot_n_90(Orientation O, int n);


/* Calcul et renvoie l'orientation du robot en fonction des 4 cas possible du
** cours */
Orientation calcul_orient(Image I, Robot R);


/* fonction qui calcule et renvoi les coordonnées de la position initial du
** robot pour le calcul de l'image */
Point calcul_pos_init(Image I);


/* Calcul le contour de l'image et renvoie une liste chainé de chaque point de
** ce contour */
Contour calcul_contour(Image I);


/* Calcul le contour de l'image et affiche a la volee son contour */
void calcul_contour_a_la_vole(Image I);

#endif
