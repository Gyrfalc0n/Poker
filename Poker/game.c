#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "struct.c"
#include "win.c"

int random(int lower, int upper) // génération basée sur le temps d'un entier aléatoire entre lower et upper
{
	int num = (rand() % (upper - lower + 1)) + lower;
	return num;
}

void afficher_cartes(int id) { //print quelle est la carte a partir de son id (ex : As de Coeur pour id = 1)
	// print valeur de la carte
	if (id == 1 || id == 14 || id == 27 || id == 40) {
		printf("As de ");
	}
	else if (id == 2 || id == 15 || id == 28 || id == 41) {
		printf("2 de ");
	}
	else if (id == 3 || id == 16 || id == 29 || id == 42) {
		printf("3 de ");
	}
	else if (id == 4 || id == 17 || id == 30 || id == 43) {
		printf("4 de ");
	}
	else if (id == 5 || id == 18 || id == 31 || id == 44) {
		printf("5 de ");
	}
	else if (id == 6 || id == 19 || id == 32 || id == 45) {
		printf("6 de ");
	}
	else if (id == 7 || id == 20 || id == 33 || id == 46) {
		printf("7 de ");
	}
	else if (id == 8 || id == 21 || id == 34 || id == 47) {
		printf("8 de ");
	}
	else if (id == 9 || id == 22 || id == 35 || id == 48) {
		printf("9 de ");
	}
	else if (id == 10 || id == 23 || id == 36 || id == 49) {
		printf("10 de ");
	}
	else if (id == 11 || id == 24 || id == 37 || id == 50) {
		printf("Valet de ");
	}
	else if (id == 12 || id == 25 || id == 38 || id == 51) {
		printf("Dame de ");
	}
	else {
		printf("Roi de ");
	}
	// print couleur de la carte
	if (id <= 13) {
		printf("Coeur");
	}
	else if (id > 13 && id <= 26) {
		printf("Carreau");
	}
	else if (id > 26 && id <= 39) {
		printf("Pique");
	}
	else {
		printf("Trefle");
	}
}

void distribution(Jeu *jeu) {
	bool to_add;
	int random_carte, j;
	for (int i = 0; i<15;)
	{
		to_add = true;
		random_carte = random(1, 52);
		for (j = 0; j < 15; j++) // on teste si la valeur tirée est deja dans les cartes distribuées pour ne pas avoir de doublon
		{
			if (jeu->manche.cartes[j] == random_carte) {
				to_add = false;
			}
		}
		if (to_add) {
			jeu->manche.cartes[i] = random_carte;
			i++;
		}
	} //remplissage des mains des joueurs avec les cartes distribuées
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

void actualisation_blind(Jeu* jeu) { //trigger en debut de round pour trigger les mises dues au blind
	mise(jeu, jeu->manche.small_blind, jeu->manche.small_blind_indice);
	mise(jeu, jeu->manche.big_blind, jeu->manche.big_blind_indice);
}

// MANCHE



// ROUND


void afficher_round(Jeu* jeu, int joueur_indice) { // affiche les infos qu'on voit en tant que joueur = les mises des joueurs, le flop, le pot, les blind et donneurs, ses propres cartes

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