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
	int effectif_carte[13] = { 0 };
	for (int i = 0; i < 7; i++) {
		if (jeu_joueur[i] == 1 || jeu_joueur[i] == 14 || jeu_joueur[i] == 27 || jeu_joueur[i] == 40) {
			effectif_carte[0]++;
		}
		if (jeu_joueur[i] == 2 || jeu_joueur[i] == 15 || jeu_joueur[i] == 28 || jeu_joueur[i] == 41) {
			effectif_carte[1]++;
		}
		if (jeu_joueur[i] == 3 || jeu_joueur[i] == 16 || jeu_joueur[i] == 29 || jeu_joueur[i] == 42) {
			effectif_carte[2]++;
		}
		if (jeu_joueur[i] == 4 || jeu_joueur[i] == 17 || jeu_joueur[i] == 30 || jeu_joueur[i] == 43) {
			effectif_carte[3]++;
		}
		if (jeu_joueur[i] == 5 || jeu_joueur[i] == 18 || jeu_joueur[i] == 31 || jeu_joueur[i] == 44) {
			effectif_carte[4]++;
		}
		if (jeu_joueur[i] == 6 || jeu_joueur[i] == 19 || jeu_joueur[i] == 32 || jeu_joueur[i] == 45) {
			effectif_carte[5]++;
		}
		if (jeu_joueur[i] == 7 || jeu_joueur[i] == 20 || jeu_joueur[i] == 33 || jeu_joueur[i] == 46) {
			effectif_carte[6]++;
		}
		if (jeu_joueur[i] == 8 || jeu_joueur[i] == 21 || jeu_joueur[i] == 34 || jeu_joueur[i] == 47) {
			effectif_carte[7]++;
		}
		if (jeu_joueur[i] == 9 || jeu_joueur[i] == 22 || jeu_joueur[i] == 35 || jeu_joueur[i] == 48) {
			effectif_carte[8]++;
		}
		if (jeu_joueur[i] == 10 || jeu_joueur[i] == 23 || jeu_joueur[i] == 36 || jeu_joueur[i] == 49) {
			effectif_carte[9]++;
		}
		if (jeu_joueur[i] == 11 || jeu_joueur[i] == 24 || jeu_joueur[i] == 37 || jeu_joueur[i] == 50) {
			effectif_carte[10]++;
		}
		if (jeu_joueur[i] == 12 || jeu_joueur[i] == 25 || jeu_joueur[i] == 38 || jeu_joueur[i] == 51) {
			effectif_carte[11]++;
		}
		if (jeu_joueur[i] == 13 || jeu_joueur[i] == 26 || jeu_joueur[i] == 39 || jeu_joueur[i] == 52) {
			effectif_carte[12]++;
		}
	}

//	bool high = true, pair = false, dble_pair = false, brelan = false, quinte = false, couleur = false, full = false, carre = false, flush = false, flush_royal = false;

	int max = INT_MIN, indice = -1;
	for (int i = 0; i < 13; i++) {
		if (jeu_joueur[i] > max) {
			max = jeu_joueur[i];
			indice = i;
		}
	}

// main
// 0 - rien
// 1 - carte haute
// 2 - paire
// 3 - 2 paires
// 4 - brelan
// 5 - quinte (suite)
// 6 - couleur
// 7 - full
// 8 - carré
// 9 - quinte flush (suite + couleur)
// 10 - quinte flush royale

	int indice1, indice2 = -1;
	indice1 = indice;
	switch (max)
	{
	case 2: // pair ou double pair
		for (int i = 0; i < 13; i++) {
			if (jeu_joueur[i] == 2 && i != indice1) {
				indice2 = i;
			}
		}
		if (indice2 != -1) { //double pair
			jeu->joueur[joueur_indice].score_main[0] = 2;
			jeu->joueur[joueur_indice].score_main[1] = indice1;
			jeu->joueur[joueur_indice].score_main[1] = indice2;
		}
		else { //paire simple
			jeu->joueur[joueur_indice].score_main[0] = 2;
			jeu->joueur[joueur_indice].score_main[1] = indice;
		}
		break;
	case 3: //brelan min ou full
		for (int i = 0; i < 13; i++) {
			if (jeu_joueur[i] == 2 && i != indice1) {
				indice2 = i;
			}
		}
		if (indice2 != -1) { //full
			jeu->joueur[joueur_indice].score_main[0] = 7;
			jeu->joueur[joueur_indice].score_main[1] = indice1;
			jeu->joueur[joueur_indice].score_main[1] = indice2;
		}
		else { //brelan
			jeu->joueur[joueur_indice].score_main[0] = 7;
			jeu->joueur[joueur_indice].score_main[1] = indice;
		}
		break;
	case 4: //carré
		jeu->joueur[joueur_indice].score_main[0] = 8;
		jeu->joueur[joueur_indice].score_main[1] = indice;
		//TO FIX recupperer la couleur
		break;
	default:
		break;
	}









}

//determination carte haute ou carte valeur pour les mains 

// analyse de la main max courante en fonction du flop indice (pour IA)

// comparaison des mains 