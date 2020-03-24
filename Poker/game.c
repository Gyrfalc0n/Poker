#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "struct.c"
//#include "win.c"

// GENERAL FONCTIONS

int random(int lower, int upper) // génération basée sur le temps d'un entier aléatoire entre lower et upper
{
	int num = (rand() % (upper - lower + 1)) + lower;
	return num;
}

bool is_winner_game(Jeu* jeu) { //return true si tous les joueurs sont couchés = quand un joueur a win la partie (on lui mets sa variable couché a 1) false sinon // AJOUTER ID JOUEUR QUI WIN LE JEU
	for (int i = 0; i < 5; i++) {
		if (jeu->manche.couche[i] == 0) { //METTRE CETTE FONCTION AVANT NOUVELLE MANCHE DANS BOUCLE
			return false;
		}
	}
	return true;
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

void blind(Jeu* jeu, int joueur_indice) {
	if (joueur_indice == jeu->manche.dealer_indice) {
			printf("\n");
			printf("\033[1;35mJoueur %d est le donneur\033[0m\n", joueur_indice+1);
	}
	if (joueur_indice == jeu->manche.small_blind_indice) {
			printf("\n");
			printf("\033[1;35mJoueur %d paye le small blind\033[0m (\033[1;32m%d\033[0m$)\n", joueur_indice+1, jeu->manche.small_blind);
			actualisation_blind(jeu);
	}
	if (joueur_indice == jeu->manche.big_blind_indice) {
			printf("\n");
			printf("\033[1;35mJoueur %d paye le big blind\033[0m (\033[1;32m%d\033[0m$)\n\n", joueur_indice+1,jeu->manche.big_blind);
			actualisation_blind(jeu);
	}
}

void afficher_round(Jeu* jeu, int joueur_indice, int flop_indice) { // affiche les infos qu'on voit en tant que joueur = les mises des joueurs, le flop, le pot, les blind et donneurs, ses propres cartes
	printf("--------------------------------------------------------------------------");
	printf("\n\nTable :\n");
	for (int i = 0; i < 5; i++) {
		if (i != joueur_indice && jeu->manche.couche[i] == 0) {
			printf("Joueur %d : \033[1;32m%d\033[0m$\n", i+1,jeu->joueur[i].mise);
		}
	}
	printf("\nCartes sur le tapis : ");
	if (flop_indice != 2) { //ne commence a afficher des cates que apres avoir fait un tour a vide
		for (int i = 10; i < 10 + flop_indice; i++) { //afficher les cartes sur la table (3 pour le 1er round, 4 pour le suivant et 5 pour le dernier)
			afficher_cartes(jeu->manche.cartes[i]);
			printf(" | ");
		}
	}
	printf("\n\n");
	printf("--------------------------------------------------------------------------\n");
	printf("\t\t\t\t[ \033[1;36mJoueur %d\033[0m ]\n", joueur_indice + 1);
	printf("--------------------------------------------------------------------------\n");
	printf("\n\nCartes en main : ");
	afficher_cartes(jeu->joueur[joueur_indice].main[0]);
	printf(" et ");
	afficher_cartes(jeu->joueur[joueur_indice].main[1]);
	printf("\n");
	printf("\n\n");
	printf("Solde : \033[1;32m%d\033[0m$\t\t\t Mise actuelle : \033[1;32m%d\033[0m$", jeu->joueur[joueur_indice].solde, jeu->joueur[joueur_indice].mise);
}

void fin_round(Jeu* jeu) { //actualise le pot (reccupere les mises des joueurs), detecte le(s) joueurs gagnants et actualise les soldes des gagnants
	for (int i = 0; i < 5; i++) {
		jeu->manche.pot += jeu->joueur[i].mise; //le pot est egal a la somme des mises des joueurs
		//jeu->joueur[i].mise = 0; desactiver pour continuer a afficher les mises des gens (comme le pot est actualisé, on effacera les mises a la nouvelle manche)
		jeu->manche.parole[i] = 0; //reset des paroles
	}
}

int joueur_precedent(Jeu* jeu, int joueur_indice) { //fonction qui teste pour le joueur courant qui est le joueur précédent encore en jeu (pas couché) et renvoie son id dans jeu.manche.carte[]
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

void choix(Jeu* jeu, int joueur_indice, int flop_indice) { //demande l'action de jeu pour le joueur courant et la fait(joueur_indice) 
	int entry, entry2, i;
	bool just_couche = false;
	int suivre = jeu->joueur[joueur_precedent(jeu, joueur_indice)].mise - jeu->joueur[joueur_indice].mise; //montant pour suivre
	if (suivre < 0) {
		suivre = 0;
	}
	// calcul de la relance par défaut
	int mise_val = jeu->manche.small_blind;
	int relance_base = jeu->manche.big_blind;
	int relance = relance_base * 2 + suivre;
	int relance2 = relance_base * 5 + suivre;
	int relance3 = relance_base * 10 + suivre;
	// calcul de la relance par rapport a la difference de mise avec le joueur précédent = calcul de la relance par defaut + suivre (valeur de la mise pour egaliser)
	int tapis = jeu->joueur[joueur_indice].solde;
	int precedent = joueur_precedent(jeu, joueur_indice);
	if (jeu->joueur[joueur_indice].mise == jeu->joueur[precedent].mise) { //test si parole possible
		printf("\n\n\t>>>  Miser(\033[1;32m%d\033[0m$) [\033[1;36m1\033[0m] - Miser plus [\033[1;36m2\033[0m] - Parole [\033[1;36m3\033[0m] - Se coucher [\033[1;36m4\033[0m]\n\n", mise_val); //affiche les options avec le montant pour suivre (= difference de mise entre le dernier joueur sur la table et le joueur courant)
	}
	else {
		printf("\n\n\t>>>  Suivre(\033[1;32m%d\033[0m$) [\033[1;36m1\033[0m] - Relancer [\033[1;36m2\033[0m] - Se coucher [\033[1;36m4\033[0m]\n\n", suivre); //idem mais sans parole
	}
	printf("Choix : ");
	scanf_s("%d", &entry);
	switch (entry) {
	case 4: // se coucher
		jeu->manche.couche[joueur_indice] = 1;
		jeu->manche.nb_couche++;
		if (jeu->manche.nb_couche == 4) {// si se coucher pour le joueur courant laisse un seul joueur en jeu = ce joueur a gagné la manche
			jeu->manche.is_end_round = true;
			for (int i = 0; i < 5; i++) { //condition pour coucher le dernier joueur en vie = le gagnant pour mettre fin a la manche
				if (jeu->manche.couche[i] == 0) { //le gagnant de la manche est le seul a etre encore en jeu (pas couché) = victoire par forfait
					jeu->manche.who_win = i; // RESTE A AJOUTER DETERMINATION WIN POUR QUAND RESTE PLUS QUE 1 JOUEUR EN JEU A LA FIN DE LA MANCHE
					jeu->manche.couche[i] = 1; //on couche le joueur pour passer a la manche suivante
				}
			}
		}
		just_couche = true;
		printf("\n\033[1;35mJoueur %d s'est couche\033[0m\n\n", joueur_indice + 1);
		break;
	case 3: // parole
		printf("\n\033[1;35mJoueur %d a parle\033[0m\n\n", joueur_indice + 1);
		jeu->manche.parole[joueur_indice] = 1;
		break;
	case 1: // suivre
		if (jeu->joueur[joueur_indice].mise == jeu->joueur[precedent].mise) {
			mise(jeu, mise_val, joueur_indice);
			printf("\n\033[1;35mJoueur %d mise\033[0m \033[1;32m%d\033[0m$\n\n", joueur_indice + 1, mise_val); //option choisie miser
		}
		else {
			mise(jeu, suivre, joueur_indice);
			printf("\n\033[1;35mJoueur %d suit avec\033[0m \033[1;32m%d\033[0m$\n\n", joueur_indice + 1, suivre); //option choisie suivre
		}
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
			printf("\n\033[1;35mJoueur %d relance\033[0m \033[1;32m%d\033[0m$\n\n", joueur_indice + 1, relance2);
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

	jeu->manche.is_end_round = true;
	if (entry == 3) { //le cas ou tous les joueurs ont fait parole
		for (i = 0; i < 5; i++) {
			if (jeu->manche.parole[i] != 1 && jeu->manche.couche[i] == 0) { //le joueur n'a pas fait parole et n'est pas couché
				jeu->manche.is_end_round = false;
			}
		}
	}
	else {
		for (i = 0; i < 5; i++) {
			if (jeu->manche.couche[i] == 0 || just_couche) { //si le joueur n'est pas couché, ou vient de se coucher
				for (int j = 0; j < 5; j++) {
					if (jeu->manche.couche[j] == 0 && jeu->joueur[i].mise != 0 && jeu->joueur[i].mise != jeu->joueur[j].mise) { //si joueur comparés en lignes, mises pas 0 (pas trigger quand parole) et si les mises sont pas égales
						jeu->manche.is_end_round = false;
						break;
					}
				}
			}
		}
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
	jeu->manche.flop_indice = 2;
	jeu->manche.small_blind += jeu->manche.big_blind/2;
	jeu->manche.big_blind += jeu->manche.big_blind/2;

	for (int i = 0; i < 5; i++) { //tous les joueurs sont de nouveau dans la partie
		jeu->manche.couche[i] = 0;
	}
	jeu->manche.nb_couche = 0;
	jeu->manche.is_end_round = false;

	for (int i = 0; i < 5; i++) {
		jeu->joueur[i].mise = 0; //reset des mises
		jeu->joueur[i].score_main[0] = -1;
		jeu->joueur[i].score_main[1] = -1;// reset des scores et type de mains
		jeu->joueur[i].score_main[1] = 0;
		jeu->joueur[i].score_main[1] = 0;
	}
	
}
