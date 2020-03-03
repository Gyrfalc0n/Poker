#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "struct.c"
#include "win.c"

int random(int lower, int upper) // g�n�ration bas�e sur le temps d'un entier al�atoire entre lower et upper
{
	int num = (rand() % (upper - lower + 1)) + lower;
	return num;
}

void afficher_cartes(int id) { //print quelle est la carte a partir de son id (ex : As de Coeur pour id = 1)
	// print valeur de la carte
	if (id == 1 || id == 14 || id == 27 || id == 40) {
		printf("\033[01;33mAs \033[0mde ");
	}
	else if (id == 2 || id == 15 || id == 28 || id == 41) {
		printf("\033[01;33m2 \033[0mde ");
	}
	else if (id == 3 || id == 16 || id == 29 || id == 42) {
		printf("\033[01;33m3 \033[0mde ");
	}
	else if (id == 4 || id == 17 || id == 30 || id == 43) {
		printf("\033[01;33m4 \033[0mde ");
	}
	else if (id == 5 || id == 18 || id == 31 || id == 44) {
		printf("\033[01;33m5 \033[0mde ");
	}
	else if (id == 6 || id == 19 || id == 32 || id == 45) {
		printf("\033[01;33m6 \033[0mde ");
	}
	else if (id == 7 || id == 20 || id == 33 || id == 46) {
		printf("\033[01;33m7 \033[0mde ");
	}
	else if (id == 8 || id == 21 || id == 34 || id == 47) {
		printf("\033[01;33m8 \033[0mde ");
	}
	else if (id == 9 || id == 22 || id == 35 || id == 48) {
		printf("\033[01;33m9 \033[0mde ");
	}
	else if (id == 10 || id == 23 || id == 36 || id == 49) {
		printf("\033[01;33m10 \033[0mde ");
	}
	else if (id == 11 || id == 24 || id == 37 || id == 50) {
		printf("\033[01;33mValet \033[0mde ");
	}
	else if (id == 12 || id == 25 || id == 38 || id == 51) {
		printf("\033[01;33mDame \033[0mde ");
	}
	else {
		printf("\033[01;33mRoi de ");
	}
	// print couleur de la carte
	if (id <= 13) {
		printf("\033[1;31mCoeur\033[0m");
	}
	else if (id > 13 && id <= 26) {
		printf("\033[1;31mCarreau\033[0m");
	}
	else if (id > 26 && id <= 39) {
		printf("\033[1;34mPique\033[0m");
	}
	else {
		printf("\033[1;34mTrefle\033[0m");
	}
}

void distribution(Jeu *jeu) {
	bool to_add;
	int random_carte, j;
	for (int i = 0; i<15;)
	{
		to_add = true;
		random_carte = random(1, 52);
		for (j = 0; j < 15; j++) // on teste si la valeur tir�e est deja dans les cartes distribu�es pour ne pas avoir de doublon
		{
			if (jeu->manche.cartes[j] == random_carte) {
				to_add = false;
			}
		}
		if (to_add) {
			jeu->manche.cartes[i] = random_carte;
			i++;
		}
	} //remplissage des mains des joueurs avec les cartes distribu�es
	jeu->joueur[0].main[0] = jeu->manche.cartes[0];
	jeu->joueur[0].main[1] = jeu->manche.cartes[1];
	jeu->joueur[1].main[0] = jeu->manche.cartes[2];
	jeu->joueur[1].main[1] = jeu->manche.cartes[3];
	jeu->joueur[2].main[0] = jeu->manche.cartes[4];
	jeu->joueur[2].main[1] = jeu->manche.cartes[5];
	jeu->joueur[3].main[0] = jeu->manche.cartes[6];
	jeu->joueur[3].main[1] = jeu->manche.cartes[7];
	jeu->joueur[4].main[0] = jeu->manche.cartes[8];
	jeu->joueur[4].main[1] = jeu->manche.cartes[9];
}

// GENERAL FONCTIONS

void mise(Jeu* jeu, int ammount, int joueur_indice) { //trigger quand un joueur mise (n'actualise pas le pot)
	jeu->joueur[joueur_indice].mise += ammount;
	jeu->joueur[joueur_indice].solde -= ammount;
}

void actualisation_blind(Jeu *jeu) { //trigger en debut de round pour trigger les mises dues au blind
	mise(jeu, jeu->manche.small_blind, jeu->manche.small_blind_indice);
	mise(jeu, jeu->manche.big_blind, jeu->manche.big_blind_indice);
}

// MANCHE



// ROUND


void afficher_round(Jeu* jeu, int joueur_indice, int flop_indice) { // affiche les infos qu'on voit en tant que joueur = les mises des joueurs, le flop, le pot, les blind et donneurs, ses propres cartes
	printf("Joueur %d\n", joueur_indice + 1);
	printf("Cartes en main : ");
	afficher_cartes(jeu->joueur[joueur_indice].main[0]);
	printf(" et ");
	afficher_cartes(jeu->joueur[joueur_indice].main[1]);
	printf("\n");
	printf("Cartes sur le tapis : ");
	for (int i = 10; i < 10 + flop_indice; i++) { //afficher les cartes sur la table (3 pour le 1er round, 4 pour le suivant et 5 pour le dernier)
		afficher_cartes(jeu->manche.cartes[i]);
		printf(" | ");
	}
	printf("\n\n");
	printf("Solde : \033[1;32m%d\033[0m$\t\t\t Mise actuelle : \033[1;32m%d\033[0m$", jeu->joueur[joueur_indice].solde, jeu->joueur[joueur_indice].mise);
	if (joueur_indice == jeu->manche.dealer_indice) {
		printf("\n\n");
		printf("Vous etes le donneur\n");
	}
	if (joueur_indice == jeu->manche.small_blind_indice) {
		printf("\n\n");
		printf("Vous payez le small blind (\033[1;32m%d\033[0m$)\n",jeu->manche.small_blind);
		actualisation_blind(jeu);
	}
	if (joueur_indice == jeu->manche.big_blind_indice) {
		printf("\n\n");
		printf("Vous payez le big blind (\033[1;32m%d\033[0m$)\n", jeu->manche.big_blind);
		actualisation_blind(jeu);
	}

	
}

void fin_round(Jeu* jeu) { //actualise le pot (reccupere les mises des joueurs), detecte le(s) joueurs gagnants et actualise les soldes des gagnants
	for (int i = 0; i < 5; i++) {
		jeu->manche.pot += jeu->joueur[i].mise; //le pot est egale a la somme des mises des joueurs
	}


}


void nouveau_round(Jeu* jeu) { //reset les valeurs du pot, update donneur et blind, en somme mets tout pret pour re boucler
	//actualiser gains TO CONTINUE
	jeu->manche.pot = 0;
}

void choix(Jeu* jeu, int joueur_indice) { //demande l'action de jeu pour le joueur courant (joueur_indice) 
	printf("selectionnez une action");
}