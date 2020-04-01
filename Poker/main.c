#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>

#include "fonctions.h"

// DECLARATIONS CONSTANTES & VALEUR PAR DEFAUT POUR UN JEU NON PARAMÉTRÉ

//const int reference_jeu[52] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52 };
const int default_solde = 2000;
const int default_small_blind = 10;
const int default_big_blind = 20;
const int default_pot = 0;
const int dealer_indice = 0;
const int default_flop_indice = 2;

int main(int argc, char** argv) {
    srand((unsigned)time(NULL));

    int i, compteur=1;
    Jeu jeu; //instanciation du jeu
    
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
        jeu.joueur[i].score_main[0] = 0;
        jeu.joueur[i].score_main[1] = -1;
        jeu.joueur[i].score_main[2] = -1;
        jeu.joueur[i].score_main[3] = 0;
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
        jeu.manche.parole[i] = 0;
    }

    jeu.manche.who_win = -1;
    jeu.manche.nb_couche = 0;
    jeu.manche.is_end_round = false;

    // -------------------------------------------------------------------------------------------------------------------------

    // affichage menu initial

    printf("\n\t8888888b.  .d88888b. 888    d8P 88888888888888888b.  \n");
    printf("\t888   Y88bd88P\" \"Y88b888   d8P  888       888   Y88b \n");
    printf("\t888    888888     888888  d8P   888       888    888\n");
    printf("\t888   d88P888     888888d88K    8888888   888   d88P \n");
    printf("\t8888888P\" 888     8888888888b   888       8888888P\"  \n");
    printf("\t888       888     888888  Y88b  888       888 T88b  \n");
    printf("\t888       Y88b. .d88P888   Y88b 888       888  T88b  \n");
    printf("\t888        \"Y88888P\" 888    Y88b8888888888888   T88b \n");
    printf("\t                                Enguerrand VIE");


    int joueur_indice = 0; // compteur de 0 a 5 pour joueurs
    int count = 0;
    while (jeu.win.indice > 4) { //boucle des manches tant que personne a win
        printf("\n\n\n\n--------------------------------------------------------------------------\n");
        printf("\t\t\t\t\033[1;35m[ Manche %d ]\033[0m", compteur);
        printf("\n--------------------------------------------------------------------------\n");

        distribution(&jeu);
        blind(&jeu, jeu.manche.dealer_indice); //affiche qui est le donneur
        blind(&jeu, jeu.manche.small_blind_indice); //trigger blind & afiche
        blind(&jeu, jeu.manche.big_blind_indice);//trigger blind & afiche
        joueur_indice = jeu.manche.big_blind_indice + 1; // initialisation des indices


        //redemmarer une nouvelle manche
        for (i = 2; i <= 5; i++) { // 4 FOIS / les 4 rounds (1, round a vide pour dévoiler cartes, 1 round pour flop un round pour 4eme carte et dernier roune pour cinquieme carte)
            joueur_indice = jeu.manche.big_blind_indice+1;
            while (!jeu.manche.is_end_round) { //on boucle le round courant tant que les mises sont pas égales
                    joueur_indice += count;
                    if (joueur_indice >= 5) {
                        joueur_indice = 0;
                        count = 0;
                    }
                    if (jeu.manche.couche[joueur_indice] == 0) { //test si le joueur est toujours dans la manche
                        afficher_round(&jeu, joueur_indice, i);
                        choix(&jeu, joueur_indice, i);
                        system("pause");
                        system("cls");
                    }
                    count = 1;
            }
            fin_round(&jeu);
            printf("\n\n\n\n--------------------------------------------------------------------------\n");
            printf("\033[1;35m\t\t\t      Le pot est a \033[1;32m%d\033[0m$\n", jeu.manche.pot);
            count = 0;
            jeu.manche.is_end_round = false;
        }
        for (int i = 0; i < 5; i++) {
            if (jeu.manche.couche[i] == 0) {
                check_main(&jeu, i);
                printf("\n\tJoueur %d : ", i);
                afficher_main(&jeu, i);
            }
        }
        system("pause");
        compare_main(&jeu);
        nouvelle_manche(&jeu);
        compteur++;
        printf("\n\nNouvelle manche");
    }
    return 0;
}
// premier joueur a jouer est celui apres le big blind
// premier tour cartes masquées les gens doivent s'aligner sur le big blind
// parole dispo apres


// MODELE
/* while (!done){
{

get input
actualiser variables
afficher

*/