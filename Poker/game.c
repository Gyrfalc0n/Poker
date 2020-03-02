#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#include "struct.c"

int random(int lower, int upper) // génération basée sur le temps d'un entier aléatoire entre lower et upper
{
	int num = (rand() % (upper - lower + 1)) + lower;
	return num;
}

void translate_cartes(Carte *carte, int id) { //return un tableau qui quand on l'affiche, affiche la carte (exemple : As de coeur pour carte n°1)
	switch (id) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;
	case 15:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	default:
		break;
	}
	return carte;
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
	}
}

void mise(Jeu* jeu, int ammount, int joueur_indice) { //triger quand un joueur mise (n'actualise pas le pot)
	jeu->joueur[joueur_indice].mise += ammount;
	jeu->joueur[joueur_indice].solde -= ammount;
}

void actualisation_blind(Jeu *jeu) { //triger en debut de round pour triger les mises dues au blind
	mise(jeu, jeu->manche.small_blind, jeu->manche.small_blind_indice);
	mise(jeu, jeu->manche.big_blind, jeu->manche.big_blind_indice);
}

void afficher_cartes(Jeu* jeu, int joueur_indice) { //affiche en console les cartes du joueur courant

}

void afficher_manche(Jeu* jeu) { // affiche les infos qu'on voit en tant que joueur = les mises des joueurs, le flop, le pot, les blind et donneurs, ses propres cartes

}

void choix(Jeu* jeu, int joueur_indice) { //demande une action 
	printf("selectionnez une action");
}

void nouveau_round() { //reset les valeurs du pot, update donneur et blind, en somme mets tout pret pour re boucler
}