/****************************************************************************** 
  Implementation du module image_pbm
******************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<types_macros.h>
#include<image.h>

/* macro donnant l'indice du pixel de coordonnees (_x,_y) de l'image _I 
   dans le tableau de pixels de l'image _I */
#define INDICE_PIXEL(_I,_x,_y) ((_x)-1)+(_I).la_largeur_de_l_image*((_y)-1)

/* creation d'une image PBM de dimensions L x H avec tous les pixels blancs */
Image creer_image(UINT L, UINT H)
{
    Image I;
    UINT i;

    I.la_largeur_de_l_image = L;
    I.la_hauteur_de_l_image = H;

    /* allocation dynamique d'un tableau de L*H Pixel*/
    I.pointeur_vers_le_tableau_de_pixels = (Pixel *)malloc(sizeof(Pixel)*L*H);

    /* test si le tableau a ete correctement alloue */
    if (I.pointeur_vers_le_tableau_de_pixels == (Pixel *)NULL)
    {
        ERREUR_FATALE(RED"Impossible de creer une image"RESET);
    }

    /* remplir le tableau avec des pixels blancs */
    for (i=0; i<L*H; i++)
        I.pointeur_vers_le_tableau_de_pixels[i] = BLANC;

    return I;
}

/* suppression de l'image I = *p_I */
void supprimer_image(Image *p_I)
{
    free(p_I->pointeur_vers_le_tableau_de_pixels);
    p_I->la_largeur_de_l_image = 0;
    p_I->la_hauteur_de_l_image = 0;
}

/* renvoie la valeur du pixel (x,y) de l'image I
   si (x,y) est hors de l'image la fonction renvoie BLANC */
Pixel get_pixel_image(Image I, UINT x, UINT y)
{
    if (x<1 || x>I.la_largeur_de_l_image || y<1 || y>I.la_hauteur_de_l_image)
        return BLANC;
    return I.pointeur_vers_le_tableau_de_pixels[INDICE_PIXEL(I,x,y)];
}

/* renvoie la valeur du pixel (x,y) de l'image I
   si (x,y) est hors de l'image la fonction renvoie NOIR */
Pixel get_pixel_image_neg(Image I, UINT x, UINT y)
{
    if (x<1 || x>I.la_largeur_de_l_image || y<1 || y>I.la_hauteur_de_l_image)
        return NOIR;
    return I.pointeur_vers_le_tableau_de_pixels[INDICE_PIXEL(I,x,y)];
}

/* change la valeur du pixel (x,y) de l'image I avec la valeur v
   si (x,y) est hors de l'image la fonction ne fait rien */
void set_pixel_image(Image I, UINT x, UINT y, Pixel v)
{
    if (x<1 || x>I.la_largeur_de_l_image || y<1 || y>I.la_hauteur_de_l_image)
        return;
    I.pointeur_vers_le_tableau_de_pixels[INDICE_PIXEL(I,x,y)] = v;
}

/* renvoie la largeur de l'image I */
UINT largeur_image(Image I)
{
    return I.la_largeur_de_l_image;
}

/* renvoie la hauteur de l'image I */
UINT hauteur_image(Image I)
{
    return I.la_hauteur_de_l_image;
}


/* fonction qui verifie si il y a au moins un seperateur (' ' ou '\n')
   -renvoie 0 si il y a aucun separateur
   -renvoie 1 si il y en a au moins un
   */
int verif_sep(FILE* f){
    char sep;
    sep = fgetc(f);
    if (sep != ' ' && sep != '\n'){
        return 0;
    }
    do
    {
        sep = fgetc(f);
    }while(sep == ' ' || sep =='\n');

    fseek(f, -1, SEEK_CUR);
    return 1;

}

/* lire l'image dans le fichier nomme nom_f
   s'il y a une erreur dans le fichier le programme s'arrete en affichant
   un message 
   version acceptant les fichiers avec 
   - ligne 1 : P1
   - zero, une ou plusieurs lignes commen�ant toutes par #
   - zero, un ou plusieurs separateurs
   - la largeur
   - un ou plusieurs separateurs
   - la hauteur
   - un ou plusieurs separateurs
   - les pixels de l'image
   */

/* teste si le fichier d'identificateur f debute par un en-tete
   valide pour un fichier PBM :
   - ligne 1 : P1\n
   - suivie de zero, une ou plusieurs lignes commen�ant toutes par #
   La fonction se termine correctement si le fichier est correct, 
   et le pointeur de fichier se trouve � la suite de l'entete.
   Sinon, l'execution du programme est arretee avec l'affichage d'un message
   d'erreur (appel � ERREUR_FATALE)
   */ 
void entete_fichier_pbm(FILE *f)
{
    char *ligne;
    size_t n;
    ssize_t l_ligne;

    /* se positionner en debut de fichier */
    fseek(f, 0, SEEK_SET);

    /* lecture et test de la ligne 1 */
    ligne = (char *)NULL;
    n = 0;
    l_ligne = getline(&ligne, &n, f);

    /* la ligne est correcte si et ssi 
       cas - fichier cree sous Linux : ligne = {'P','1',10} 
       soit une chaine de 3 caracteres (le dernier est le caractere nul) 
       cas - fichier cree sous Windows : ligne = {'P','1',13, 10} 
       soit une chaine de 4 caracteres (le dernier est le caractere nul) 
       */
    if (l_ligne < 3)
    {
        ERREUR_FATALE(RED"entete_fichier_pbm : ligne 1 incorrecte\n"RESET);
    }
    if (!((ligne[0] == 'P' && ligne[1] == '1' && ligne[2] == 13 && ligne[3] == 10) || (ligne[0] == 'P' && ligne[1] == '1' && ligne[2] == 10)))
    {
        ERREUR_FATALE(RED"entete_fichier_pbm : ligne 1 incorrecte\n"RESET);
    }
    free(ligne);

    /* lecture des eventuelles lignes commen�ant par # */
    bool boucle_ligne_commentaire = true;
    do
    {
        /* tester d'abord la fin de fichier */
        if (feof(f))
        {
            ERREUR_FATALE(RED"entete_fichier_pbm : fin fichier inattendue\n"RESET);
        }

        /* lire un caractere et tester par rapport � '#' */
        char c;
        fscanf(f, "%c", &c);
        if (c=='#')
        {
            /* lire le reste de la ligne */
            ligne = (char *)NULL;
            n = 0;
            l_ligne = getline(&ligne, &n, f);
            free(ligne);
        }
        else
        {
            /* reculer d'un caract�re dans f */
            fseek(f, -1, SEEK_CUR);
            boucle_ligne_commentaire = false;
        }
    } while (boucle_ligne_commentaire);

}

/* lire l'image dans le fichier nomme nom_f
   s'il y a une erreur dans le fichier le programme s'arrete en affichant
   un message */
Image lire_fichier_image(char *nom_f)
{
    FILE *f;
    UINT L,H;
    UINT x,y;
    int sep;
    int res_fscanf;
    char c;
    Image I;

    /* ouverture du fichier nom_f en lecture */
    f = fopen(nom_f, "r");
    if (f == (FILE *)NULL)
    {
        ERREUR_FATALE(RED"lire_fichier_image : ouverture du fichier impossible\n"RESET);
    }

    /* traitement de l'en-tete et arret en cas d'erreur */
    entete_fichier_pbm(f);

    /* lecture des dimensions */
    res_fscanf = fscanf(f, "%d", &L);
    if (res_fscanf != 1){
        ERREUR_FATALE(RED"lire_fichier_image : dimension L incorrecte\n"RESET);
    }
    //verification qu'il y a au moins un separateur 
    sep = verif_sep(f);
    if (sep == 0){
        ERREUR_FATALE(RED"lire_fichier_image : il faut un séparateur entre les deux entiers de dimensions\n"RESET);
    }

    res_fscanf = fscanf(f, "%d", &H);
    if (res_fscanf != 1)
    {
        ERREUR_FATALE(RED"lire_fichier_image : dimension H incorrecte\n"RESET);
    }

    //verification qu'il y a au moins un separateur 
    sep = verif_sep(f);
    if (sep == 0){
        ERREUR_FATALE(RED"lire_fichier_image : il faut un séparateur après la deuxième dimension\n"RESET);
    }


    /* creation de l'image de dimensions L x H */
    I = creer_image(L,H);

    /* lecture des pixels du fichier 
       seuls les caracteres '0' (BLANC) ou '1' (NOIR) 
       doivent etre pris en compte */
    x = 1; y = 1;
    while (!feof(f) && y<=H)
    {

        /* lire un caractere en passant les caracteres differents de '0' et '1' */
        fscanf(f, "%c", &c);
        while (!feof(f) && !(c == '0' || c == '1'))
        {
            fscanf(f, "%c", &c);
        }
        if (!feof(f))
        {
            set_pixel_image(I,x,y,c=='1' ? NOIR : BLANC );
            x++;
            if (x>L)
            {
                x = 1; y++;
            }
        }
    }   
    if (y < H){
        ERREUR_FATALE(RED"Il n'y a pas assez de pixel a remplir (peut-être un souci dans la séparation des dimension)\n"RESET);
    }

    do
    {
        sep = fgetc(f);
        if (sep != ' ' && sep != '\n' && sep != EOF)
            ERREUR_FATALE(RED"Il y a trop de Pixel dans le fichier\n"RESET);

    }while(sep != EOF);

    /* fermeture du fichier */
    fclose(f);

    return I;
}

/*ecrit dans un fichier f l'image I sous format .pbm*/
void ecrire_fichier_image(Image I, char *nom_f){

    /* ouverture du fichier nom_f en lecture */
    FILE* f = fopen(nom_f, "w");
    if (f == (FILE *)NULL)
    {
        ERREUR_FATALE(RED"ecrire_fichier_image : ouverture du fichier impossible\n"RESET);
    }

    UINT x, y;

    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);

    fprintf(f, "P1\n%d %d\n", L, H);

    x = 1; y = 1;

    while (y <= H){

        //si le pixel est blanc on affiche 0 et sinon on affiche 1
        if (get_pixel_image(I , x, y) == BLANC)
            fprintf(f, "0");
        else 
            fprintf(f, "1");

        x++;

        //si on arrvie a la fin de la ligne on reviens a la ligne et on reinitialise les valeurs x et y
        if (x > L){
            x = 1; y++;
            fprintf(f, "\n");
        }

    }

    /* fermeture du fichier */
    fclose(f);

}


/* ecrire l'image I a l'ecran 
   - affiche '.' si Pixel est blanc
   - affiche '#' si Pixel est noir
   */
void ecrire_image(Image I)
{
    UINT x, y;

    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);

    // affichage à l'écran de la largeur et de la hauteur
    printf("Largeur de l'image : %d\n", L);	
    printf("Hauteur de l'image : %d\n", H);	

    x = 1; y = 1;

    while (y <= H){

        //si le pixel est blanc on affiche . et sinon on affiche #
        if (get_pixel_image(I , x, y) == BLANC)
            printf(".");
        else 
            printf("#");

        x++;

        //si on arrvie a la fin de la ligne on reviens a la ligne et on reinitialise les valeurs x et y
        if (x > L){
            printf("\n");
            x = 1; y++;
        }

    }


}

/* calculer l'image "negatif" de l'image I */
/* l'image I n'est pas modifiee et */
/* la fonction renvoie l'image "negatif" de I */
Image negatif_image(Image I)
{
    UINT x, y;
    Image neg_I;

    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);

    //mettre les valeurs de la longueur et de la hauteur dans neg_I
    neg_I = creer_image(L, H);

    /* remplir le tableau avec des pixels négatif de l'image I */
    x = 1; y = 1;

    while (y <= H){

        /*mettre les pixel a l'inverse de I (si get_pixel_image(I, x, y) == Noir 
          - alors on ne fait rein car le pixel(neg_I, x, y) = blanc de base (creation de l'image) )
          */
        if (get_pixel_image(I, x, y) == BLANC)
            set_pixel_image(neg_I, x, y, NOIR);

        x++;

        if (x > L){
            x = 1; y++;
        }

    }

    return neg_I;

}
