#include "lib/libgraphique.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define COTE 122 // taille d'un côté d'une image
#define BASEX 0 // posx de départ du plateau de jeu
#define BASEY 0  // posy de départ du plateau de jeu0

char *fichiers_cartes[53] = {"images/back.bmp", "images/AH.bmp", "images/2H.bmp", "images/3H.bmp", "images/4H.bmp", "images/5H.bmp", "images/6H.bmp", "images/7H.bmp", "images/8H.bmp", "images/9H.bmp", "images/10H.bmp", "images/JH.bmp", "images/QH.bmp", "images/KH.bmp",
"images/AD.bmp", "images/2D.bmp", "images/3D.bmp", "images/4D.bmp", "images/5D.bmp", "images/6D.bmp", "images/7D.bmp", "images/8D.bmp", "images/9D.bmp", "images/10D.bmp", "images/JD.bmp", "images/QD.bmp", "images/KD.bmp",
"images/AS.bmp", "images/2S.bmp", "images/3S.bmp", "images/4S.bmp", "images/5S.bmp", "images/6S.bmp", "images/7S.bmp", "images/8S.bmp", "images/9S.bmp", "images/10S.bmp", "images/JS.bmp", "images/QS.bmp", "images/KS.bmp",
"images/AC.bmp", "images/2C.bmp", "images/3C.bmp", "images/4C.bmp", "images/5C.bmp", "images/6C.bmp", "images/7C.bmp", "images/8C.bmp", "images/9C.bmp", "images/10C.bmp", "images/JC.bmp", "images/QC.bmp", "images/KC.bmp"};

void affiche_plateau()
{
    Point p = { BASEX,BASEY };
    afficher_image("images/background.bmp", p);
    actualiser();
    afficher_image(fichiers_cartes[1], p);
    actualiser();
    p.x += 60;
    afficher_image("images/AS.bmp", p);
    actualiser();
}

void afficher_ttes_cartes() {
    Point p = { BASEX, BASEY };
    afficher_image("images/background.bmp", p);
    actualiser();
    int count = 0;
    for (int i = 1; i < 53; i++) {
        if (count == 13) {
            p.y += 91;
            p.x = 0;
            count = 0;
        }
        afficher_image(fichiers_cartes[i], p);
        actualiser();
        count++;
        p.x += 60;
    }
    Point k = { 0, 364 };
    afficher_image(fichiers_cartes[0], k);
    actualiser();
}


int main(int argc, char* argv[]){
    Point p;
    int l, c;

    //indispensable pour commencer
    ouvrir_fenetre(1280, 720);


    afficher_ttes_cartes();

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


