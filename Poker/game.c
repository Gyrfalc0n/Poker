#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "struct.c"
#include "win.c"

// GENERAL FONCTIONS

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
		printf("\033[01;33mRoi \033[0mde ");
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

void distribution(Jeu* jeu) {
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

void mise(Jeu* jeu, int ammount, int joueur_indice) { //trigger quand un joueur mise (n'actualise pas le pot)
	int entry;
	int tapis = jeu->joueur[joueur_indice].solde;
	if (jeu->joueur[joueur_indice].solde >= ammount) {
		jeu->joueur[joueur_indice].mise += ammount;
		jeu->joueur[joueur_indice].solde -= ammount;
	}
	else {
		printf("\n\033[0;36mVous ne pouvez pas miser, fonds insuffisants\033[0m"); //rajouter all in ou se coucher si pas assez de thunes
		printf("\nChoix possibles : Se coucher [1] - Tapis (\033[1;32m%d\033[0m$)[2]\n",tapis);
		scanf_s("%d", &entry);
		switch (entry)
		{
		case 1:
			jeu->manche.couche[joueur_indice] = 1;
			printf("\n\033[1;35mJoueur %d s'est couche\033[0m", joueur_indice + 1);
		case 2:
			mise(jeu, tapis, joueur_indice);
			printf("\n\033[1;35mJoueur %d fait tapis avec\033[0m \033[1;32m%d\033[0m$", joueur_indice + 1, tapis);
			break;
		default:
			break;
		}
	}
}

void actualisation_blind(Jeu* jeu) { //trigger en debut de round pour trigger les mises dues au blind
	mise(jeu, jeu->manche.small_blind, jeu->manche.small_blind_indice);
	mise(jeu, jeu->manche.big_blind, jeu->manche.big_blind_indice);
}

// ROUND

void afficher_round(Jeu* jeu, int joueur_indice, int flop_indice) { // affiche les infos qu'on voit en tant que joueur = les mises des joueurs, le flop, le pot, les blind et donneurs, ses propres cartes
	printf("--------------------------------------------------------------------------");
	printf("\nTable :\n");
	for (int i = 0; i < 5; i++) {
		if (i != joueur_indice && jeu->manche.couche[i] == 0) {
			printf("Joueur %d : \033[1;32m%d\033[0m$\n", i+1,jeu->joueur[i].mise);
		}
	}
	printf("--------------------------------------------------------------------------\n");
	printf("\t\t\t\t[ \033[1;36mJoueur %d\033[0m ]\n", joueur_indice + 1);
	printf("--------------------------------------------------------------------------\n");
	printf("Cartes sur le tapis : ");
	for (int i = 10; i < 10 + flop_indice; i++) { //afficher les cartes sur la table (3 pour le 1er round, 4 pour le suivant et 5 pour le dernier)
		afficher_cartes(jeu->manche.cartes[i]);
		printf(" | ");
	}
	printf("\n\nCartes en main : ");
	afficher_cartes(jeu->joueur[joueur_indice].main[0]);
	printf(" et ");
	afficher_cartes(jeu->joueur[joueur_indice].main[1]);
	printf("\n");
	printf("\n\n");
	printf("Solde : \033[1;32m%d\033[0m$\t\t\t Mise actuelle : \033[1;32m%d\033[0m$", jeu->joueur[joueur_indice].solde, jeu->joueur[joueur_indice].mise);
	if (flop_indice == 3) { // on ne paye les blinds qu'une fois par manche au debut (pas a chaque tour de table!)
		if (joueur_indice == jeu->manche.dealer_indice) {
			printf("\n\n");
			printf("Vous etes le donneur\n");
		}
		if (joueur_indice == jeu->manche.small_blind_indice) {
			printf("\n\n");
			printf("Vous payez le small blind (\033[1;32m%d\033[0m$)\n", jeu->manche.small_blind);
			actualisation_blind(jeu);
		}
		if (joueur_indice == jeu->manche.big_blind_indice) {
			printf("\n\n");
			printf("Vous payez le big blind (\033[1;32m%d\033[0m$)\n", jeu->manche.big_blind);
			actualisation_blind(jeu);
		}
	}
}

void fin_round(Jeu* jeu) { //actualise le pot (reccupere les mises des joueurs), detecte le(s) joueurs gagnants et actualise les soldes des gagnants
	for (int i = 0; i < 5; i++) {
		jeu->manche.pot += jeu->joueur[i].mise; //le pot est egale a la somme des mises des joueurs
		jeu->joueur[i].mise = 0;
	}
	jeu->manche.flop_indice += 1;
}

int joueur_precedent(Jeu* jeu, int joueur_indice) { //fonction qui teste pour le joueur courant qui est le joueur pr�c�dent encore en jeu (pas couch�) et renvoie son id dans jeu.manche.carte[]
	int indice = joueur_indice, to_check;
	bool found = false;
	while (!found) {
		if (indice == 0) {
			to_check = 4;
		}
		else {
			to_check = indice - 1;
		}
		if (jeu->manche.couche[to_check] == 0) {
			found = true;
			indice = to_check;
		}
		else {
			if (indice == 0) {
				indice = 4;
			}
			else {
				indice--;
			}
		}
	}
	return indice;
}

void choix(Jeu* jeu, int joueur_indice) { //demande l'action de jeu pour le joueur courant et la fait(joueur_indice) 
	int entry, entry2;
	int suivre = jeu->joueur[joueur_precedent(jeu, joueur_indice)].mise - jeu->joueur[joueur_indice].mise; //montant pour suivre
	if (suivre < 0) {
		suivre = 0;
	}
	// calcul de la relance par d�faut
	int relance_base = jeu->manche.big_blind;
	int relance = relance_base*2 + suivre;
	int relance2 = relance_base * 5 + suivre;
	int relance3 = relance_base * 10 + suivre;
	// calcul de la relance par rapport a la difference de mise avec le joueur pr�c�dent = calcul de la relance par defaut + suivre (valeur de la mise pour egaliser)
	int tapis = jeu->joueur[joueur_indice].solde;
	int precedent = joueur_precedent(jeu, joueur_indice);
	printf("\n\t>>> Suivre(\033[1;32m%d\033[0m$) [1] - Relancer [2] - Parole [3] - Se coucher [4]\n\n",suivre); //affiche les options avec le montant pour suivre (= difference de mise entre le dernier joueur sur la table et le joueur courant)
	scanf_s("%d", &entry);
	switch (entry) {
	case 4: // se coucher
		jeu->manche.couche[joueur_indice] = 1;
		printf("\n\033[1;35mJoueur %d s'est couche\033[0m\n\n", joueur_indice+1);
		break;
	case 3: // parole
		if (jeu->joueur[joueur_indice].mise == jeu->joueur[precedent].mise) {
			printf("\n\033[1;35mJoueur %d a parle\033[0m\n\n", joueur_indice+1);
		}
		else {
			printf("\n\033[0;36mVous ne pouvez pas parler\033[0m\n");
		}
		break;
	case 1: // suivre
		mise(jeu, suivre, joueur_indice);
		printf("\n\033[1;35mJoueur %d suit avec\033[0m \033[1;32m%d\033[0m$\n\n", joueur_indice+1, suivre);
		break;
	case 2: // relancer
		printf("\n\t>>> Relancer : \033[1;32m%d\033[0m$ [1] - \033[1;32m%d\033[0m$ [2] - \033[1;32m%d\033[0m$ [3] - \033[1;32m%d\033[0m$ (Tapis)[4]\n\n", relance, relance2, relance3, tapis); //affichage des options de relance
		scanf_s("%d", &entry2);
		switch (entry2) {
		case 1:
			mise(jeu, relance, joueur_indice);
			printf("\n\033[1;35mJoueur %d relance\033[0m \033[1;32m%d\033[0m$\n\n", joueur_indice + 1, relance);
			break;
		case 2:
			mise(jeu, relance2, joueur_indice);
			printf("\n\033[1;35mJoueur %d relance\033[0m \033[1;32m%d\033[0m$\n\n", joueur_indice + 1,relance2);
			break;
		case 3:
			mise(jeu, relance3, joueur_indice);
			printf("\n\033[1;35mJoueur %d relance\033[0m \033[1;32m%d\033[0m$\n\n", joueur_indice + 1, relance3);
			break;
		case 4:
			mise(jeu, tapis, joueur_indice);
			printf("\n\033[1;35mJoueur %d fait tapis avec\033[0m \033[1;32m%d\033[0m$\n\n", joueur_indice + 1, tapis);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

// MANCHE

void nouvelle_manche(Jeu* jeu) { //reset les valeurs du pot, update donneur et blind, en somme mets tout pret pour re boucler
	jeu->joueur[jeu->win.indice].solde += jeu->manche.pot; //la gagnant remporte les gains
	jeu->manche.pot = 0; // reset du pot
	if (jeu->manche.big_blind_indice <= 3) { //update big blind indice
		jeu->manche.big_blind_indice += 1;
	}
	else {
		jeu->manche.big_blind_indice = 0;
	}
	if (jeu->manche.small_blind_indice <= 3) { //  update small blind indice
		jeu->manche.small_blind_indice += 1;
	}
	else {
		jeu->manche.small_blind_indice = 0;
	}
	if (jeu->manche.dealer_indice <= 3) { // update donneur indice
		jeu->manche.dealer_indice += 1;
	}
	else {
		jeu->manche.dealer_indice = 0;
	}
	jeu->manche.flop_indice = 3;
	jeu->manche.small_blind *= 2;
	jeu->manche.big_blind *= 2;

	for (int i = 0; i < 5; i++) { //tous les joueurs sont de nouveau dans la partie
		jeu->manche.couche[i] = 0;
	}
}
