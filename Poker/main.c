#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "struct.c"
#include "fonctions.h"

int main(int argc, char** argv) {
    srand((unsigned)time(NULL));
    int i;
    Jeu jeu;
    
    // ---------------------------------------------INITIALISATION-------------------------------------------------------------
    //initialisation parametres généraux Jeu
    jeu.initial_solde = default_solde;
    for (i = 0; i < 5; i++) {
        jeu.composition_joueurs[i] = 0;
    }
    jeu.win.indice = 0;
    jeu.win.main = 0;
    //initialisation parametres Joueur
    for (i = 0; i < 5; i++) {
        jeu.joueur[i].main[0] = 0;
        jeu.joueur[i].main[1] = 0;
        jeu.joueur[i].solde = default_solde;
        jeu.joueur[i].score_main = 0;
        jeu.joueur[i].mise = 0;
    }
    //initialisation parametres Manche
    for (i = 0; i < 15; i++) {
        jeu.manche.cartes[i] = 0;
    }
    jeu.manche.pot = 0;
    jeu.manche.dealer_indice = random(0, 4); // le premier dealer de la partie est aléatoire parmi les 5 joueurs
    jeu.manche.small_blind_indice = jeu.manche.dealer_indice + 1;
    jeu.manche.big_blind_indice = jeu.manche.dealer_indice + 2;
    jeu.manche.small_blind = default_small_blind;
    jeu.manche.big_blind = default_big_blind;

    // -------------------------------------------------------------------------------------------------------------------------

    distribution(&jeu);
    printf("Disribution :\n\n");
    for (i = 0; i < 15; i++) {
        printf("%d\t", jeu.manche.cartes[i]);
    }
    printf("\n");

    printf("Traduction jeu :\n\n");
    for (i = 0; i < 15; i++) {
        afficher_cartes(jeu.manche.cartes[i]);
        printf("\n");
    }
    
    printf("\n");
    return 0;
}



/* while (!done){
{

get input
actualiser variables
afficher

*/