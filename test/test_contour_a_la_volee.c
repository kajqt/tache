#include <stdio.h>
#include <struct_liste.h>
#include <geom2d.h>
#include <image.h>
#include <contour.h>
#include <types_macros.h>


int main(int argc, char* argv[])
{
    // il faut au moin un fichier .pbm pour cet executable
    if (argc !=  2)
    {
        ERREUR_FATALE(RED"Uilisation : ./test_contour <fichier image>\n"RESET);
    }
    // Declaration des variable 
    Image I;

    printf("Contour du fichier %s\n", argv[1]);
    I = lire_fichier_image(argv[1]);
    calcul_contour_a_la_vole(I);

    return 0;
}

