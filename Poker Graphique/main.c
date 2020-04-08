#include "lib/libgraphique.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define COTE 122 // taille d'un côté d'une image
#define BASEX 0 // posx de départ du plateau de jeu
#define BASEY 0  // posy de départ du plateau de jeu0



void affiche_plateau()
{
    Point p = { BASEX,BASEY };
    afficher_image("images/background.bmp", p); //affiche l'image
    actualiser();
}


int main(int argc, char* argv[]){
    Point p;
    int l, c;

    //indispensable pour commencer
    ouvrir_fenetre(1280, 720);


    affiche_plateau();

    while (1)
    {
        p = attendre_clic();
        l = (p.y - BASEY) / COTE;
        c = (p.x - BASEX) / COTE;
        printf("Ligne %d Colonne %d\n", l, c);
    }
    fermer_fenetre();
    return 0;
}


