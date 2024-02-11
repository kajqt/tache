#include <stdio.h>
#include <contour.h>
#include <geom2d.h>
#include <image.h>
#include <types_macros.h>
#include <struct_liste.h>

/* initialise un robot qui a pour coordonnée (0,0) est une orientaion vers
** l'Est */
Robot init_robot(Point P)
{
    Robot r;
    r.o = EST;
    r.pt.x = P.x;
    r.pt.y = P.y;
    return r;
}


/* fonction qui calcule et renvoi les coordonnées de la position initial du
** robot pour le calcul de l'image 
** quitte l'execution si il n'y a pas de point noir */
Point calcul_pos_init(Image I)
{
    UINT i,j;
    Pixel p, p_1; //p_1 correspondra au pixel au dessu de p

    // i represente l'abscisse et j l'ordonnée
    for(j = 1 ; j <= hauteur_image(I) ; j++)
    {
        for (i = 1 ; i <= largeur_image(I) ; i++)
        {
            p = get_pixel_image(I, i, j);
            p_1 = get_pixel_image(I, i, j-1);

            if (p == NOIR && p_1 == BLANC)
                return set_point(i, j);
        }
    }

    //si on arrive ici c'est que l'image est toute blance et donc pas de contour
    ERREUR_FATALE("Il n'y a pas de pixel noir dans cette image\n");

    return set_point(0,0);

}


/* fais avncer le robot d'une case en fonction de son orientation */
Point avancer_robot(Robot R)
{
    switch(R.o)
    {
        case NORD:
            R.pt.y = R.pt.y - 1;
            break;
        case SUD:
            R.pt.y = R.pt.y + 1;
            break;
        case EST:
            R.pt.x = R.pt.x + 1;
            break;
        case OUEST:
            R.pt.x = R.pt.x - 1;
            break;
        default : 
            ERREUR_FATALE("avancer_robot : Erreur dans l'orientation du robot");
            break;
    }

    return R.pt;
}

/* Les 4 fonction pixel_NW/NE/SW/SE renvoie la coordonné du pixel au la
** position voulu en fonction de la position du robot */
Point pixel_NW(Point P)
{
    return P;
}

Point pixel_NE(Point P)
{
    return set_point(P.x + 1, P.y);
}

Point pixel_SW(Point P)
{
    return set_point(P.x, P.y + 1);
}

Point pixel_SE(Point P)
{
    return set_point(P.x + 1, P.y + 1);
}


/* La fonction rot_90 renvoie l'orientation apres une rotation de 90 degres
** dans le ses trigonometrique */
/* Le fonction rot_i_90 fais le meme sorte de rotation mais n fais */
Orientation rot_90(Orientation O)
{
    switch (O)
    {
        case NORD:
            return OUEST;
        case SUD:
            return EST;
        case OUEST:
            return SUD;
        case EST:
            return NORD;
    }
}

Orientation rot_n_90(Orientation O, int n)
{
    for (int i = 0; i < n ; i++)
    {
        O = rot_90(O);
    }

    return O; 
}


Orientation calcul_orient(Image I, Robot R)
{
    Point pt_devant_gauche, pt_devant_droit; //coordonné des point devant gauche et devant droit du robot
    Pixel pix_devant_gauche, pix_devant_droit;

    //devant gauche et droit depandent de l'orientation du robot 
    switch(R.o)
    {
        case NORD:
            pt_devant_gauche = pixel_NW(R.pt);
            pt_devant_droit = pixel_NE(R.pt);
            break;
       case SUD:
            pt_devant_gauche = pixel_SE(R.pt);
            pt_devant_droit = pixel_SW(R.pt);
            break;
        case EST:
            pt_devant_gauche = pixel_NE(R.pt);
            pt_devant_droit = pixel_SE(R.pt);
            break;
        case OUEST:
            pt_devant_gauche = pixel_SW(R.pt);
            pt_devant_droit = pixel_NW(R.pt);
            break;
    }

    //recuperation de la couleur des pixel devant gauche et droit
    pix_devant_gauche = get_pixel_image(I, pt_devant_gauche.x, pt_devant_gauche.y);
    pix_devant_droit = get_pixel_image(I, pt_devant_droit.x, pt_devant_droit.y);

    switch (pix_devant_gauche)
    {
        case 0: //pixel blanc
            if (pix_devant_droit == 0)
               return  rot_n_90(R.o, 3); //on tourne 3 fois de 90 degres = 270
            else
                //si le pixel droit est noir alors on garde la meme orientation
                return R.o;
        case 1 : //pixel noir
            //on tourne dans les deux cas (pixel droit blanc ou noir) de 90 degres
            return rot_90(R.o);
    }
}


/* Calcul le contour de l'image et renvoie une liste chainé de chaque point de
** ce contour */
Contour calcul_contour(Image I)
{
    Robot R;
    Contour C;
    Point pos_pix, pos_point, pos_courante;
    bool boucle;

    pos_pix = calcul_pos_init(I); //position du PIXEL de départ
    pos_point = set_point(pos_pix.x - 1, pos_pix.y - 1);    //position du POINT de depart

    R = init_robot(pos_point); 
    pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;

    C = creer_liste_Point_vide();

    boucle = true;

    while (boucle)
    {
        C = ajouter_element_liste_Point(C, pos_courante);
        R.pt = avancer_robot(R);
        pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;
        R.o = calcul_orient(I, R);

        if (pos_courante.x == pos_point.x && pos_courante.y == pos_point.y && R.o == EST)
            boucle = false;
    }
    C = ajouter_element_liste_Point(C, pos_courante); //Pour ajouter la position intiale a la fin de la liste
    return C;
}




/* Calcul le contour de l'image et affiche a la volee son contour */
void calcul_contour_a_la_vole(Image I)
{
    Robot R;
    Point pos_pix, pos_point, pos_courante;
    bool boucle;

    pos_pix = calcul_pos_init(I); //position du PIXEL de départ
    pos_point = set_point(pos_pix.x - 1, pos_pix.y - 1);    //position du POINT de depart

    R = init_robot(pos_point); 
    pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;

    boucle = true;

    while (boucle)
    {
        printf("(%.1f,%.1f)", pos_courante.x, pos_courante.y);
        R.pt = avancer_robot(R);
        pos_courante.x = R.pt.x; pos_courante.y = R.pt.y;
        R.o = calcul_orient(I, R);

        if (pos_courante.x == pos_point.x && pos_courante.y == pos_point.y && R.o == EST)
            boucle = false;
    }
    printf("(%.1f,%.1f)\n", pos_courante.x, pos_courante.y);
}





