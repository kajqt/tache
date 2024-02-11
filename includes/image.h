/****************************************************************************** 
  Interface du module image
******************************************************************************/

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <types_macros.h>

/* 
 Type enuméré Pixel équivalent au char avec BLANC=0 et NOIR=1
 */
typedef enum {BLANC=0,NOIR=1} Pixel;

/* 
 Type Image
 */
typedef struct Image_
{
	UINT la_largeur_de_l_image; 
	UINT la_hauteur_de_l_image; 
	Pixel* pointeur_vers_le_tableau_de_pixels; 
} Image;

/* création d'une image PBM de dimensions L x H avec tous les pixels blancs */
Image creer_image(UINT L, UINT H);

/* suppression de l'image I = *p_I */
void supprimer_image(Image *p_I);

/* renvoie la valeur du pixel (x,y) de l'image I
   si (x,y) est hors de l'image la fonction renvoie BLANC */
Pixel get_pixel_image(Image I, UINT x, UINT y);

/* renvoie la valeur du pixel (x,y) de l'image I
   si (x,y) est hors de l'image la fonction renvoie NOIR */
Pixel get_pixel_image_neg(Image I, UINT x, UINT y);


/* change la valeur du pixel (x,y) de l'image I avec la valeur v
   si (x,y) est hors de l'image la fonction ne fait rien */
void set_pixel_image(Image I, UINT x, UINT y, Pixel v);

/* renvoie la largeur de l'image I */
UINT largeur_image(Image I);

/* renvoie la hauteur de l'image I */
UINT hauteur_image(Image I);

/* lire l'image dans le fichier nomme nom_f
   s'il y a une erreur dans le fichier le programme s'arrete en affichant
   un message 
   version acceptant les fichiers avec 
   - ligne 1 : P1\n
   - zero, une ou plusieurs lignes commencant toutes par #
   - zero, un ou plusieurs separateurs
   - la largeur
   - un ou plusieurs separateurs
   - la hauteur
   - un ou plusieurs separateurs
   - les pixels de l'image
   */
Image lire_fichier_image(char *nom_f);

/*ecrit dans un fichier f l'image I sous format .pbm*/
void ecrire_fichier_image(Image I, char *nom_fx);

/* ecrire l'image I a l'ecran */
void ecrire_image(Image I);

/* calculer l'image "negatif" de l'image I */
/* l'image I n'est pas modifiee et */
/* la fonction renvoie l'image "negatif" de I */
Image negatif_image(Image I);

#endif /* _IMAGE_H_ */
