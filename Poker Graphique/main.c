#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>

#include <Windows.h>
#include <mmsystem.h>

#include "lib/libgraphique.h"
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

    int i, compteur = 1;
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

    //initialisation graphique

    //fichiers images
    jeu.graph.cartes[0] = "images/back.bmp";
    jeu.graph.cartes[1] = "images/AH.bmp";
    jeu.graph.cartes[2] = "images/2H.bmp";
    jeu.graph.cartes[3] = "images/3H.bmp";
    jeu.graph.cartes[4] = "images/4H.bmp";
    jeu.graph.cartes[5] = "images/5H.bmp";
    jeu.graph.cartes[6] = "images/6H.bmp";
    jeu.graph.cartes[7] = "images/7H.bmp";
    jeu.graph.cartes[8] = "images/8H.bmp";
    jeu.graph.cartes[9] = "images/9H.bmp";
    jeu.graph.cartes[10] = "images/10H.bmp";
    jeu.graph.cartes[11] = "images/JH.bmp";
    jeu.graph.cartes[12] = "images/QH.bmp";
    jeu.graph.cartes[13] = "images/KH.bmp";
    jeu.graph.cartes[14] = "images/AD.bmp";
    jeu.graph.cartes[15] = "images/2D.bmp";
    jeu.graph.cartes[16] = "images/3D.bmp";
    jeu.graph.cartes[17] = "images/4D.bmp";
    jeu.graph.cartes[18] = "images/5D.bmp";
    jeu.graph.cartes[19] = "images/6D.bmp";
    jeu.graph.cartes[20] = "images/7D.bmp";
    jeu.graph.cartes[21] = "images/8D.bmp";
    jeu.graph.cartes[22] = "images/9D.bmp";
    jeu.graph.cartes[23] = "images/10D.bmp";
    jeu.graph.cartes[24] = "images/JD.bmp";
    jeu.graph.cartes[25] = "images/QD.bmp";
    jeu.graph.cartes[26] = "images/KD.bmp";
    jeu.graph.cartes[27] = "images/AS.bmp";
    jeu.graph.cartes[28] = "images/2S.bmp";
    jeu.graph.cartes[29] = "images/3S.bmp";
    jeu.graph.cartes[30] = "images/4S.bmp";
    jeu.graph.cartes[31] = "images/5S.bmp";
    jeu.graph.cartes[32] = "images/6S.bmp";
    jeu.graph.cartes[33] = "images/7S.bmp";
    jeu.graph.cartes[34] = "images/8S.bmp";
    jeu.graph.cartes[35] = "images/9S.bmp";
    jeu.graph.cartes[36] = "images/10S.bmp";
    jeu.graph.cartes[37] = "images/JS.bmp";
    jeu.graph.cartes[38] = "images/QS.bmp";
    jeu.graph.cartes[39] = "images/KS.bmp";
    jeu.graph.cartes[40] = "images/AC.bmp";
    jeu.graph.cartes[41] = "images/2C.bmp";
    jeu.graph.cartes[42] = "images/3C.bmp";
    jeu.graph.cartes[43] = "images/4C.bmp";
    jeu.graph.cartes[44] = "images/5C.bmp";
    jeu.graph.cartes[45] = "images/6C.bmp";
    jeu.graph.cartes[46] = "images/7C.bmp";
    jeu.graph.cartes[47] = "images/8C.bmp";
    jeu.graph.cartes[48] = "images/9C.bmp";
    jeu.graph.cartes[49] = "images/10C.bmp";
    jeu.graph.cartes[50] = "images/JC.bmp";
    jeu.graph.cartes[51] = "images/QC.bmp";
    jeu.graph.cartes[52] = "images/KC.bmp";
    //jetons
    jeu.graph.jetons[0] = "images/jeton1.bmp";
    jeu.graph.jetons[1] = "images/jeton2.bmp";
    jeu.graph.jetons[2] = "images/jeton3.bmp";
    jeu.graph.jetons[3] = "images/jeton4.bmp";
    jeu.graph.jetons[4] = "images/jeton5.bmp";
    jeu.graph.jetons[5] = "images/jeton6.bmp";
    jeu.graph.jetons[6] = "images/jeton7.bmp";
    jeu.graph.jetons[7] = "images/jeton8.bmp";
    jeu.graph.jetons[8] = "images/jeton9.bmp";
    jeu.graph.jetons[9] = "images/jeton10.bmp";
    // emplacement joueur 0
    jeu.graph.slot_carte[0].slot[0].x = 579;
    jeu.graph.slot_carte[0].slot[0].y = 538;
    jeu.graph.slot_carte[0].slot[1].x = 642;
    jeu.graph.slot_carte[0].slot[1].y = 538;
    jeu.graph.slot_mises[0].x = 605;
    jeu.graph.slot_mises[0].y = 427;
    jeu.graph.slot_texte_mises[0].x = 605;
    jeu.graph.slot_texte_mises[0].y = 499;
    // emplacement joueur 1
    jeu.graph.slot_carte[1].slot[0].x = 40;
    jeu.graph.slot_carte[1].slot[0].y = 315;
    jeu.graph.slot_carte[1].slot[1].x = 103;
    jeu.graph.slot_carte[1].slot[1].y = 315;
    jeu.graph.slot_mises[1].x = 186;
    jeu.graph.slot_mises[1].y = 314;
    jeu.graph.slot_texte_mises[1].x = 186;
    jeu.graph.slot_texte_mises[1].y = 386;
    // emplacement joueur 2
    jeu.graph.slot_carte[2].slot[0].x = 203;
    jeu.graph.slot_carte[2].slot[0].y = 18;
    jeu.graph.slot_carte[2].slot[1].x = 266;
    jeu.graph.slot_carte[2].slot[1].y = 18;
    jeu.graph.slot_mises[2].x = 312;
    jeu.graph.slot_mises[2].y = 124;
    jeu.graph.slot_texte_mises[2].x = 312;
    jeu.graph.slot_texte_mises[2].y = 196;
    // emplacement joueur 3
    jeu.graph.slot_carte[3].slot[0].x = 952;
    jeu.graph.slot_carte[3].slot[0].y = 18;
    jeu.graph.slot_carte[3].slot[1].x = 1015;
    jeu.graph.slot_carte[3].slot[1].y = 18;
    jeu.graph.slot_mises[3].x = 900;
    jeu.graph.slot_mises[3].y = 124;
    jeu.graph.slot_texte_mises[3].x = 900;
    jeu.graph.slot_texte_mises[3].y = 197;
    // emplacement joueur 4
    jeu.graph.slot_carte[4].slot[0].x = 1118;
    jeu.graph.slot_carte[4].slot[0].y = 315;
    jeu.graph.slot_carte[4].slot[1].x = 1181;
    jeu.graph.slot_carte[4].slot[1].y = 315;
    jeu.graph.slot_mises[4].x = 1024;
    jeu.graph.slot_mises[4].y = 314;
    jeu.graph.slot_texte_mises[4].x = 1024;
    jeu.graph.slot_texte_mises[4].y = 386;
    // cartes communes & emplacements
    jeu.graph.flop[0].x = 728;
    jeu.graph.flop[1].x = 669;
    jeu.graph.flop[2].x = 610;
    jeu.graph.flop[3].x = 551;
    jeu.graph.flop[4].x = 492;
    for (int i = 0; i < 5; i++) {
        jeu.graph.flop[i].y = 315;
    }
    jeu.graph.actions.x = 380;
    jeu.graph.actions.y = 637;
    //emplacement textes joueurs
    jeu.graph.texte_joueur[0].x = 492;
    jeu.graph.texte_joueur[0].y = 573;
    jeu.graph.texte_joueur[1].x = 66;
    jeu.graph.texte_joueur[1].y = 419;
    jeu.graph.texte_joueur[2].x = 117;
    jeu.graph.texte_joueur[2].y = 53;
    jeu.graph.texte_joueur[3].x = 865;
    jeu.graph.texte_joueur[3].y = 53;
    jeu.graph.texte_joueur[4].x = 1144;
    jeu.graph.texte_joueur[4].y = 419;
    //flop tapis
    jeu.graph.tapis_image.x = 605;
    jeu.graph.tapis_image.y = 197;
    jeu.graph.tapis_texte.x = 605;
    jeu.graph.tapis_texte.y = 269;
    //log & action
    jeu.graph.action_clear.x = 384;
    jeu.graph.action_clear.y = 642;
    jeu.graph.action_texte1.x = 410;
    jeu.graph.action_texte1.y = 650;
    jeu.graph.action_texte2.x = 410;
    jeu.graph.action_texte2.y = 686;
    jeu.graph.action_texte3.x = 670;
    jeu.graph.action_texte3.y = 650;
    jeu.graph.action_texte4.x = 670;
    jeu.graph.action_texte4.y = 686;
    jeu.graph.log_clear.x = 55;
    jeu.graph.log_clear.y = 530;
    jeu.graph.log_texte.x = 55;
    jeu.graph.log_texte.y = 539;
    // -------------------------------------------------------------------------------------------------------------------------

    /*
    if (CONSOLE == 0) {

        ouvrir_fenetre(1280, 720);        
        distribution(&jeu);
        background();
        afficher_flop_pot(&jeu, 5);
        afficher_jeu(&jeu, 2);
        clear_log(&jeu);
        clear_action(&jeu);
        Point p = { BASEX, BASEY };
        p = attendre_clic();
    }
    */

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

    ouvrir_fenetre(1280, 720);

    int joueur_indice = 0; // compteur de 0 a 5 pour joueurs
    int count = 0;
    while (jeu.win.indice > 4) { //boucle des manches tant que personne a win
        printf("\n\n\n\n--------------------------------------------------------------------------\n");
        printf("\t\t\t\t\033[1;35m[ Manche %d ]\033[0m", compteur);
        printf("\n--------------------------------------------------------------------------\n");
        background();
        distribution(&jeu);
        blind(&jeu, jeu.manche.dealer_indice); //affiche qui est le donneur
        blind(&jeu, jeu.manche.small_blind_indice); //trigger blind & afiche
        blind(&jeu, jeu.manche.big_blind_indice);//trigger blind & afiche
        joueur_indice = jeu.manche.big_blind_indice + 1; // initialisation des indices
        //redemmarer une nouvelle manche
        for (i = 2; i <= 5; i++) { // 4 FOIS / les 4 rounds (1, round a vide pour dévoiler cartes, 1 round pour flop un round pour 4eme carte et dernier roune pour cinquieme carte)
            joueur_indice = jeu.manche.big_blind_indice + 1;
            while (!jeu.manche.is_end_round) { //on boucle le round courant tant que les mises sont pas égales
                joueur_indice += count;
                if (joueur_indice >= 5) {
                    joueur_indice = 0;
                    count = 0;
                }
                if (jeu.manche.couche[joueur_indice] == 0) { //test si le joueur est toujours dans la manche
                    afficher_round(&jeu, joueur_indice, i);
                    afficher_flop_pot(&jeu, i);
                    afficher_jeu(&jeu, joueur_indice);
                    choix(&jeu, joueur_indice, i);
                    if (CONSOLE) {
                        system("pause");
                        system("cls");
                    }

                }
                count = 1;
            }
            fin_round(&jeu);
            printf("\n\n\n\n--------------------------------------------------------------------------\n");
            printf("\033[1;35m\t\t\t      Le pot est a \033[1;32m%d\033[0m$\n", jeu.manche.pot);
            count = 0;
            jeu.manche.is_end_round = false;
        }
        //affichage des mains
        printf("\n\n\n\n--------------------------------------------------------------------------\n");
        printf("\t\t\t\t\033[1;35m[  Mains  ]\033[0m");
        printf("\n--------------------------------------------------------------------------\n");
        for (int i = 0; i < 5; i++) {
            if (jeu.manche.couche[i] == 0) {
                check_main(&jeu, i);
                printf("\n\tJoueur %d : ", i + 1);
                afficher_main(&jeu, i);
            }
        }
        printf("\n\n");
        if (CONSOLE) {
            system("pause");
        }
        compare_main(&jeu);
        //rajouter print pour qui a gagné
        nouvelle_manche(&jeu);
        compteur++;
        if (CONSOLE) {
            system("cls");
        }
        if (DEBUG == 1) {
            printf("\n\nNouvelle manche");
        }
    }
    fermer_fenetre();
    return 0;
}
// premier joueur a jouer est celui apres le big blind
// premier tour cartes masquées les gens doivent s'aligner sur le big blind
// parole dispo apres