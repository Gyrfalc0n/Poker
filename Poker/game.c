#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "struct.c"

int random(int lower, int upper)
{
	int num = (rand() % (upper - lower + 1)) + lower;
	return num;
}

void distribution(Jeu *jeu) {
	bool to_add;
	int random_carte, j;
	for (int i = 0; i<15;)
	{
		to_add = true;
		random_carte = random(1, 52);
		for (j = 0; j < 15; j++) // on teste si la valeur tirée est deja dans les cartes distribuées
		{
			if (jeu->manche.cartes[j] == random_carte) {
				to_add = false;
			}
		}
		if (to_add) {
			jeu->manche.cartes[i] = random_carte;
			i++;
		}
	}
}

void actualisation_blind(Jeu *jeu) { //triger en debut de round pour triger les mises dues au blind
	mise(jeu, jeu->manche.small_blind, jeu->manche.small_blind_indice);
	mise(jeu, jeu->manche.big_blind, jeu->manche.big_blind_indice);
}

void mise(Jeu* jeu, int ammount, int joueur_indice) { //triger quand un joueur mise (n'actualise pas le pot)
	jeu->joueur[joueur_indice].mise += ammount;
	jeu->joueur[joueur_indice].solde -= ammount;
}

void afficher_cartes(Jeu* jeu, int joueur_indice) { //affiche en console les cartes du joueur courant

}

void afficher_manche(Jeu* jeu) { // affiche les infos qu'on voit en tant que joueur = les mises des joueurs, le flop, le pot, les blind et donneurs, ses propres cartes

}

void choix(Jeu* jeu, int joueur_indice) { //demande une action 
	printf("selectionnez une action");
}