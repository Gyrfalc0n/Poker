#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdio.h>

#include "struct.c"
#include "fonctions.h"

int main(int argc, char** argv) {
    srand((unsigned)time(NULL));

    int i, j;
    Jeu jeu;
    
    // ---------------------------------------------INITIALISATION-------------------------------------------------------------
    //initialisation parametres généraux Jeu
    jeu.initial_solde = default_solde;
    for (i = 0; i < 5; i++) {
        jeu.composition_joueurs[i] = 0;
    }
    jeu.win.indice = 99;
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
    jeu.manche.dealer_indice = 0; // le premier dealer de la partie est le joueur 1
    jeu.manche.small_blind_indice = jeu.manche.dealer_indice + 1;
    jeu.manche.big_blind_indice = jeu.manche.dealer_indice + 2;
    jeu.manche.small_blind = default_small_blind;
    jeu.manche.big_blind = default_big_blind;
    jeu.manche.flop_indice = default_flop_indice;
    for (i = 0; i < 5; i++) {
        jeu.manche.couche[i] = 0; // initialise l'état des 5 joueurs a 0 (pas couché) (serait a 1 si joueur couché)
    }
    jeu.manche.nb_couche = 0;
    jeu.manche.is_end_round = false;

    // -------------------------------------------------------------------------------------------------------------------------

    // affichage menu initial
    int joueur_indice = 0; // compteur de 0 a 5 pour joueurs
    while (jeu.win.indice > 4) { //boucle des manches tant que personne a win
        distribution(&jeu);
        blind(&jeu, jeu.manche.dealer_indice); //affiche qui est le donneur
        blind(&jeu, jeu.manche.small_blind_indice);
        blind(&jeu, jeu.manche.big_blind_indice);

        //redemmarer une nouvelle manche
        for (i = 0; i < 3; i++) { // 4 FOIS / les 4 rounds (1, round a vide pour dévoiler cartes, 1 round pour flop un round pour 4eme carte et dernier roune pour cinquieme carte)
            while (!jeu.manche.is_end_round) { //on boucle l
                for (j = 0; j < 5; j++) {
                    if (jeu.manche.couche[joueur_indice] == 0) {
                        afficher_round(&jeu, joueur_indice, i);
                        choix(&jeu, joueur_indice);
                        system("pause");
                        system("cls");
                    }
                }
            }
            fin_round(&jeu);
        }
        nouvelle_manche(&jeu);
    }

    // TESTS 

    distribution(&jeu);
    printf("\n");
    afficher_round(&jeu, 0, 3);
    afficher_round(&jeu, 1, 3);
    afficher_round(&jeu, 2, 3);
    system("cls"); //pour faire trigger les blind
    afficher_round(&jeu, 3, 3);
    choix(&jeu, 3);
    system("pause");
    system("cls");
    afficher_round(&jeu, 4, 3);
    choix(&jeu, 4);
    system("pause");
    system("cls");
    afficher_round(&jeu, 0, 4);
    choix(&jeu, 0);
    system("pause");
    system("cls");
    afficher_round(&jeu, 1, 4);
    choix(&jeu, 1);
    system("pause");
    system("cls");
    afficher_round(&jeu, 2, 4);
    choix(&jeu, 2);
    system("pause");
    system("cls");
    afficher_round(&jeu, 3, 4);
    choix(&jeu, 3);

    return 0;
}
// premier joueur a jouer est celui apres le big blind
// premier tour cartes masquées les gens doivent s'aligner sur le big blind
// parole dispo apres


/* while (!done){
{

get input
actualiser variables
afficher

*/