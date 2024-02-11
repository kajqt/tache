#!/bin/bash



# Ce fichier prend en argument un dossier contenant au moins un fichier .pbm
# Il calcul ensuite son contour et le met dans un fichier suffixé par .contour
# Ce fichier est ensuite sotcké dans un dossier du même nom que le dossier
# passé en argument suffixé par _CONTOUR



# Vérification du bon nombre d'argument
if [ $# -ne 1 ] || [ ! -d $1 ]
then
    echo "Utilisation : ./contour <nom_dossier> (où nom_dossier est un dossier qui contient des .pbm)"
    exit 1
fi

# On fais le make
make

#si le make ne s'est pas bien passe on exit 
if [ $? -ne 0 ]
then
    echo "ERREUR DANS LA MAKE"
    exit 1
fi


nom_doss_cont=$1_contour

# Cette variable verifie si il y a au moins un contour cree et si c'est le cas
# alors on cree le dossier pour le et on fais la commande pour bouger le
# contour cree dans le bon dossier
exist_cont=0

for file in $1/*.pbm
do
    echo ""
    echo "calcul de l'image $file"

    ./test/test_contour $file

    if [ $? -eq 0 ]
    then
        exist_cont=1
    fi

done

if [ $exist_cont -eq 1 ]
then
    # si le dossier IMAGES_TESTS_CONTOUR n'existe pas on le cree
    mkdir -p $nom_doss_cont

    #On met tous les contours cree dans le dossier IMAGE_TESTS_CONTOUR
    echo ""
    echo ""
    echo "On met touts les contours dans le dossier $nom_doss_cont"
    mv $1/*contour* $nom_doss_cont
fi



