#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "struct.c"

// analyse des mains du joueur courant. Modifie les valeurs de sa main (de score main de struct Joueur)

void check_main(Jeu* jeu, int joueur_indice) {
	int to_check[2] = { 0 }, jeu_joueur[7] = { 0 }; //les id dans cartes du joueur courant vont se mettre dedans
	switch (joueur_indice) {
	case 0:
		to_check[0] = 0;
		to_check[1] = 1;
		break;
	case 1:
		to_check[0] = 2;
		to_check[1] = 3;
		break;
	case 2:
		to_check[0] = 4;
		to_check[1] = 5;
		break;
	case 3:
		to_check[0] = 6;
		to_check[1] = 7;
		break;
	case 4:
		to_check[0] = 8;
		to_check[1] = 9;
		break;
	default:
		break;
	}

	jeu_joueur[0] = to_check[0];
	jeu_joueur[1] = to_check[1];
	jeu_joueur[2] = jeu->manche.cartes[10];
	jeu_joueur[3] = jeu->manche.cartes[11];
	jeu_joueur[4] = jeu->manche.cartes[12];
	jeu_joueur[5] = jeu->manche.cartes[13];
	jeu_joueur[6] = jeu->manche.cartes[14]; // jeu_joueur contient donc les 7 cartes du joueur courant

	//realisation tableau d'effectif
	int effectif_carte[15] = { 0 };
	for (int i = 0; i < 7; i++) {
		
	}




}

// faire un tableau d'effectif 

// analyse de la main max courante en fonction du flop indice (pour IA)

// comparaison des mains 