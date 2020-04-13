#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#include <Windows.h>
#include <mmsystem.h>

#include "lib/libgraphique.h"
#include "fonctions.h"


int check_couleur(Jeu* jeu, int joueur_indice, int jeu_joueur[]) {
	int range_carte[7] = { 0 }; // tableau pour couleur de chaque carte (1 coeur, 2 carreau, 3 pique, 4 trefle)
	//int min_coeur = 1, max_coeur = 13, min_carreau = 14, max_carreau = 26, min_pique = 27, max_pique = 39, min_trefle = 40, max_trefle = 52;
	int score[4] = { 0 }, score_global = 0;
	for (int i = 0; i < 7; i++) {//determination de la couleur de chaque carte
		if (jeu_joueur[i] <= 13) {
			range_carte[i] = 1;
		}
		else if (jeu_joueur[i] >= 40) {
			range_carte[i] = 4;
		}
		else if (jeu_joueur[i] > 13 && jeu_joueur[i] <= 26) {
			range_carte[i] = 2;
		}
		else {
			range_carte[i] = 3;
		}
	}
	//score[] est le max de cartes de chaque couleur
	for (int i = 1; i <= 4; i++) {
		for (int j = 0; j < 7; j++) {
			if (range_carte[j] = i) {
				score[i - 1]++;
			}
		}
	}
	int max = score[0];
	for (int i = 0; i < 4; i++) {
		if (score[i] >= 5) {
			return i;
		}
	}
	return 0;
}

// analyse de la main max courante en fonction du flop indice (pour IA)

// comparaison des mains

void compare_main(Jeu* jeu) {
	bool gagnant_unique = false;
	int max_indice = -1, nb_carte_haute = 0, nb_carte_haute2 = 0, max_indice2 = -1, indice1 = 0, indice2 = 0;
	int max = 0, nb_gagnants = 0, indice_gagnant;
	char joueurs_gagnants[5] = { 0 };//rempli de 0 si joueur n'a pas la main gagnante, 1 sinon
	char carte_hautes[5] = { 0 };//id des joueurs qui ont main gagnante et meme carte haute max = ceux qui vont se répartir le pot
	char carte_hautes2[5] = { 0 };//id des joueurs qui ont main gagnante et meme carte haute max = ceux qui vont se répartir le pot (cas double pair)
	for (int i = 0; i < 5; i++) { //determination main la pluys forte parmi les joueurs
		if (jeu->manche.couche[i] == 0 && jeu->joueur[i].score_main[0] > max) {
			max = jeu->joueur[i].score_main[0];
			indice_gagnant = i;
		}
	}
	printf("\nmain max = %d\n", indice_gagnant);
	bool couleur = false;
	for (int i = 0; i < 5; i++) { //calcul du nombre de joueurs a la meme main
		if (jeu->manche.couche[i] == 0 && jeu->joueur[i].score_main[0] == max) {
			joueurs_gagnants[i] = 1; //tableau des joueurs avec main gagnante
			nb_gagnants++; //calcul diviseur de gain parmi les gagnants
		}
	}
	printf("\nnb gagnants = %d\n", nb_gagnants);
	nb_gagnants -= 1; //on baisse de 1 parce qu'il s'incrémente la premiere fois pour prendre sa valeur max
	if (nb_gagnants != 1) {// plusieurs gagnants
		for (int i = 0; i < 5; i++) { //determination carte haute de la main gagnante
			if (jeu->manche.couche[i] == 0 && joueurs_gagnants[i] == 1) {
				switch (jeu->joueur[i].score_main[0]) {
				case 5: //cas couleur, tout joueur avec la main gagne
					couleur = true;
					break;
				default://tous les autres cas
					if (jeu->joueur[i].score_main[1] > max_indice) {
						max_indice = jeu->joueur[i].score_main[1];
					}
					break;
				}
			}
		}
		printf("\nmax indice1 = %d\n", max_indice);
		if (couleur) {
			for (int i = 0; i < 5; i++) {
				if (joueurs_gagnants[i] == 1) {
					jeu->manche.gagnants[i] = 1;
				}
			}
			int gain_couleur = jeu->manche.pot / nb_gagnants;
			background();
			afficher_flop_pot(jeu, 5);
			afficher_jeu_win(jeu);
			for (int i = 0; i < 5; i++) {
				if (joueurs_gagnants[i] == 1) {
					jeu->joueur[i].solde += gain_couleur;
					jeu->manche.gain = gain_couleur;
					afficher_main(jeu, i);
				}
			}
			goto end;
		}
		for (int i = 0; i < 5; i++) { //calcul du nombre de joueurs a la meme carte haute pour main gagnante
			if (jeu->manche.couche[i] == 0 && jeu->joueur[i].score_main[1] == max_indice) {
				carte_hautes[i] = 1; //tableau des joueurs avec main gagnante et meme carte haute gagnante
				jeu->manche.gagnants[i] = 1;
				indice1 = i;
				nb_carte_haute++;
			}
		}
		printf("\nnb carte haute = %d\n", nb_carte_haute);
		if ( (max == 3 || max == 2 || max == 7) && nb_carte_haute > 1) {//cas de la double pair, de la pair et du full ou il faut check le 2eme indice
			for (int i = 0; i < 5; i++) {//reset
				jeu->manche.gagnants[i] = 0;
				if (carte_hautes[i] && jeu->joueur[i].score_main[2] > max_indice2) {
					max_indice2 = jeu->joueur[i].score_main[2];
				}
			}
			printf("\nmax indice2 = %d\n", max_indice2);
			for (int i = 0; i < 5; i++) { //calcul du nombre de joueurs a la meme carte haute pour main gagnante
				if (carte_hautes[i] && jeu->manche.couche[i] == 0 && jeu->joueur[i].score_main[2] == max_indice2) {
					carte_hautes2[i] = 1; //tableau des joueurs avec main gagnante et meme carte haute gagnante
					jeu->manche.gagnants[i] = 1;
					indice2 = i;
					nb_carte_haute2++;
				}
			}
			printf("\nnb carte haute2 = %d\n", nb_carte_haute2);
			if (indice2 == 1) {//plusieurs joueurs qui ont la meme main, et la meme carte haute indice1, mais un seul a la max carte haute indice2
				int gain4 = jeu->manche.pot;
				jeu->manche.who_win = indice2;
				background();
				afficher_flop_pot(jeu, 5);
				afficher_jeu_win(jeu);
				jeu->joueur[indice2].solde += gain4;
				jeu->manche.gain = gain4;
				afficher_main(jeu, indice2);
			}
			else { //plusieurs joueurs qui ont la meme main, et la meme carte haute indice1, et plusieurs meme carte haute indice2
				int gain_dblpair = jeu->manche.pot / nb_carte_haute2;
				jeu->manche.who_win = indice2;
				background();
				afficher_flop_pot(jeu, 5);
				afficher_jeu_win(jeu);
				for (int i = 0; i < 5; i++) {
					if (joueurs_gagnants[i] == 1) {
						jeu->joueur[i].solde += gain_dblpair;
						jeu->manche.gain = gain_dblpair;
						afficher_main(jeu, i);
					}
				}
				goto end;
			}

		}
		else {
			if (nb_carte_haute != 1) {//plusieurs personnes qui ont la meme main et la meme carte haute sans etre dans les cas ou il faut check indice 2
				int gain = jeu->manche.pot / nb_carte_haute;
				background();
				afficher_flop_pot(jeu, 5);
				afficher_jeu_win(jeu);
				for (int i = 0; i < 5; i++) {
					if (carte_hautes[i] == 1) {
						jeu->joueur[i].solde += gain;
						jeu->manche.gain = gain;
						afficher_main(jeu, i);
					}
				}
			}
			else {// cas ou il y a  plusieurs personnes avec la meme main mais une seule avec indice1 max
				int gain3 = jeu->manche.pot;
				jeu->manche.who_win = indice1;
				background();
				afficher_flop_pot(jeu, 5);
				afficher_jeu_win(jeu);
				jeu->joueur[indice1].solde += gain3;
				jeu->manche.gain = gain3;
				afficher_main(jeu, indice1);
			}
		}
	}
	else {//un seul joueur qui a la main gagnante
		int gain2 = jeu->manche.pot;
		jeu->manche.who_win = indice_gagnant;
		background();
		afficher_flop_pot(jeu, 5);
		afficher_jeu_win(jeu);
		jeu->joueur[indice_gagnant].solde += gain2;
		jeu->manche.gain = gain2;
		afficher_main(jeu, indice_gagnant);
	}
end:;//etiquette fin de fonction
}

void afficher_main(Jeu* jeu, int joueur_indice) {
	char* indice1 = "";
	char* indice2 = "";
	char* couleur = "";
	switch (jeu->joueur[joueur_indice].score_main[1]) {
	case 0:
		indice1 = "As";
		break;
	case 1:
		indice1 = "2";
		break;
	case 2:
		indice1 = "3";
		break;
	case 3:
		indice1 = "4";
		break;
	case 4:
		indice1 = "5";
		break;
	case 5:
		indice1 = "6";
		break;
	case 6:
		indice1 = "7";
		break;
	case 7:
		indice1 = "8";
		break;
	case 8:
		indice1 = "9";
		break;
	case 9:
		indice1 = "10";
		break;
	case 10:
		indice1 = "Valet";
		break;
	case 11:
		indice1 = "Dame";
		break;
	case 12:
		indice1 = "Roi";
		break;
	default:
		break;
	}
	switch (jeu->joueur[joueur_indice].score_main[2]) {
	case 0:
		indice2 = "As";
		break;
	case 1:
		indice2 = "2";
		break;
	case 2:
		indice2 = "3";
		break;
	case 3:
		indice2 = "4";
		break;
	case 4:
		indice2 = "5";
		break;
	case 5:
		indice2 = "6";
		break;
	case 6:
		indice2 = "7";
		break;
	case 7:
		indice2 = "8";
		break;
	case 8:
		indice2 = "9";
		break;
	case 9:
		indice2 = "10";
		break;
	case 10:
		indice2 = "Valet";
		break;
	case 11:
		indice2 = "Dame";
		break;
	case 12:
		indice2 = "Roi";
		break;
	default:
		break;
	}
	switch (jeu->joueur[joueur_indice].score_main[3]) {
	case 1:
		couleur = "Coeur";
		break;
	case 2:
		couleur = "Carreau";
		break;
	case 3:
		couleur = "Pique";
		break;
	case 4:
		couleur = "Trefle";
		break;
	default:
		break;
	}
	//printf("\tMain actuelle :  \033[1;36m");
	printf("\033[1;36m");
	char joueur[120] = "Joueur ";
	char temp[2];
	char joueur2[] = " gagne avec ";
	_itoa(joueur_indice+1, temp, 10);
	strcat(joueur, temp);
	strcat(joueur, joueur2);
	char cartehaute[100] = "Carte haute (";
	char paire[100] = "Paire de ";
	char doublepair[100] = "Double paire aux ";
	char doublepair2[] = " et aux ";
	char brelan[100] = "Brelan aux ";
	char quinte[] = "Quinte ";
	char couleur2[100] = "Couleur ";
	char full[100] = "Full aux ";
	char full2[] = "par les ";
	char carre[100] = "Carre aux ";
	char quinteflush[100] = "Quinte Flush ";
	char quinteflushroyale[100] = "Quinte Flush Royale";
	char log_win[100] = "Joueur ";
	char log_win2[] = " : gagne ";
	char log_win_temp[10];
	char log_win3[] = "$";
	strcat(log_win, temp);
	strcat(log_win, log_win2);
	_itoa(jeu->manche.gain, log_win_temp, 10);
	strcat(log_win, log_win_temp);
	strcat(log_win, log_win3);
	char parenthese[] = ")";
	switch (jeu->joueur[joueur_indice].score_main[0]) {
	case 1:
		printf("Carte haute ");
		printf("\033[0m(\033[1;32m%s\033[0m)", indice1);
		strcat(cartehaute, indice1);
		//afficher_texte(cartehaute, 13, jeu->graph.log_texte, yellow);
		afficher_texte(log_win, 13, jeu->graph.log_texte, yellow);
		strcat(joueur, cartehaute);
		strcat(joueur, parenthese);
		clear_action(jeu);
		afficher_texte(joueur, 13, jeu->graph.action_texte1, yellow);
		break;
	case 2:
		printf("Paire de ");
		printf("\033[1;32m%s\033[0m", indice1);
		strcat(paire, indice1);
		//afficher_texte(paire, 13, jeu->graph.log_texte, yellow);
		afficher_texte(log_win, 13, jeu->graph.log_texte, yellow);
		strcat(joueur, paire);
		clear_action(jeu);
		afficher_texte(joueur, 13, jeu->graph.action_texte1, yellow);
		break;
	case 3:
		printf("Double paire aux ");
		printf("\033[1;32m%s\033[0m", indice1);
		printf("\033[1;36m et aux ");
		printf("\033[1;32m%s\033[0m", indice2);
		strcat(doublepair, indice1);
		strcat(doublepair, doublepair2);
		strcat(doublepair, indice2);
		//afficher_texte(doublepair, 13, jeu->graph.log_texte, yellow);
		afficher_texte(log_win, 13, jeu->graph.log_texte, yellow);
		strcat(joueur, doublepair);
		clear_action(jeu);
		afficher_texte(joueur, 13, jeu->graph.action_texte1, yellow);
		break;
	case 4:
		printf("Brelan aux ");
		printf("\033[1;32m%s\033[0m", indice1);
		strcat(brelan, indice1);
		//afficher_texte(brelan, 13, jeu->graph.log_texte, yellow);
		afficher_texte(log_win, 13, jeu->graph.log_texte, yellow);
		strcat(joueur, brelan);
		afficher_texte(joueur, 13, jeu->graph.action_texte1, yellow);
		break;
	case 5:
		printf("Quinte ");
		//afficher_texte(quinte, 13, jeu->graph.log_texte, yellow);
		afficher_texte(log_win, 13, jeu->graph.log_texte, yellow);
		strcat(joueur, quinte);
		afficher_texte(joueur, 13, jeu->graph.action_texte1, yellow);
		break;
	case 6:
		printf("Couleur ");
		printf("\033[0m(\033[1;32m%s\033[0m)", couleur);
		strcat(couleur2, couleur);
		//afficher_texte(couleur2, 13, jeu->graph.log_texte, yellow);
		afficher_texte(log_win, 13, jeu->graph.log_texte, yellow);
		strcat(joueur, couleur2);
		afficher_texte(joueur, 13, jeu->graph.action_texte1, yellow);
		break;
	case 7:
		printf("Full aux ");
		printf("\033[1;32m%s\033[0m", indice1);
		printf("\033[1;36m par les ");
		printf("\033[1;32m%s\033[0m", indice2);
		strcat(full, indice1);
		strcat(full, full2);
		strcat(full, indice2);
		//afficher_texte(full, 13, jeu->graph.log_texte, yellow);
		afficher_texte(log_win, 13, jeu->graph.log_texte, yellow);
		strcat(joueur, full);
		afficher_texte(joueur, 13, jeu->graph.action_texte1, yellow);
		break;
	case 8:
		printf("Carré aux ");
		printf("\033[1;32m%s\033[0m", indice1);
		strcat(carre, indice1);
		//afficher_texte(carre, 13, jeu->graph.log_texte, yellow);
		afficher_texte(log_win, 13, jeu->graph.log_texte, yellow);
		strcat(joueur, carre);
		afficher_texte(joueur, 13, jeu->graph.action_texte1, yellow);
		break;
	case 9:
		printf("Quinte flush ");
		printf("\033[0m(\033[1;32m%s\033[0m)", couleur);
		strcat(quinteflush, couleur);
		//afficher_texte(quinteflush, 13, jeu->graph.log_texte, yellow);
		afficher_texte(log_win, 13, jeu->graph.log_texte, yellow);
		strcat(joueur, quinteflush);
		afficher_texte(joueur, 13, jeu->graph.action_texte1, yellow);
		break;
	case 10:
		printf("Quinte flush royale ");
		printf("\033[0m(\033[1;32m%s\033[0m)", couleur);
		strcat(quinteflushroyale, couleur);
		//afficher_texte(quinteflushroyale, 13, jeu->graph.log_texte, yellow);
		afficher_texte(log_win, 13, jeu->graph.log_texte, yellow);
		strcat(joueur, quinteflushroyale);
		afficher_texte(joueur, 13, jeu->graph.action_texte1, yellow);
		break;
	default:
		printf("score_main du joueur = 0 ");
		break;
	}
	char tempx[] = "Appuyez sur ENTREE pour continuer";
	afficher_texte(tempx, 13, jeu->graph.action_texte2, lightgrey);
	int touche;
	do {
		touche = attendre_touche();
	} while (touche != SDLK_RETURN);
	clear_log(jeu);
	clear_action(jeu);
}




// analyse des mains du joueur courant. Modifie les valeurs de sa main (de score main de struct Joueur)

void check_main(Jeu* jeu, int joueur_indice) {
	int to_check[2] = { 0 }, jeu_joueur[7] = { 0 }; //les id dans cartes du joueur courant vont se mettre dedans
	switch (joueur_indice) {
	case 0:
		to_check[0] = jeu->manche.cartes[0];
		to_check[1] = jeu->manche.cartes[1];
		break;
	case 1:
		to_check[0] = jeu->manche.cartes[2];
		to_check[1] = jeu->manche.cartes[3];
		break;
	case 2:
		to_check[0] = jeu->manche.cartes[4];
		to_check[1] = jeu->manche.cartes[5];
		break;
	case 3:
		to_check[0] = jeu->manche.cartes[6];
		to_check[1] = jeu->manche.cartes[7];
		break;
	case 4:
		to_check[0] = jeu->manche.cartes[8];
		to_check[1] = jeu->manche.cartes[9];
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
	int effectif_carte[14] = { 0 };
	for (int i = 0; i < 7; i++) {
		if (jeu_joueur[i] == 1 || jeu_joueur[i] == 14 || jeu_joueur[i] == 27 || jeu_joueur[i] == 40) {
			effectif_carte[0]++; //as
			effectif_carte[13]++; //as
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
	for (int i = 0; i < 14; i++) {
		if (effectif_carte[i] > max) {
			max = effectif_carte[i];
			indice = i; //indice c'est l'ID de effectif carte le plus haut
		}
	}

	if (DEBUG == 1) {
		//debug
		for (int i = 0; i < 13; i++) {
			printf("debug: effectif_carte[%d] = %d\n", i, effectif_carte[i]);
		}
		printf("indice max : %d", max);
		printf("\n\n");
		//debug
	}


	// main
	// 0 - rien OK
	// 1 - carte haute OK
	// 2 - paire OK
	// 3 - 2 paires OK
	// 4 - brelan OK
	// 5 - quinte (suite) OK
	// 6 - couleur OK
	// 7 - full OK
	// 8 - carré OK
	// 9 - quinte flush (suite + couleur) OK
	// 10 - quinte flush royale OK

	int couleur = 0, j;
	int indice1, indice2 = -1;
	indice1 = indice;
	int count = 0, nombre_suite = 0;
	switch (max) {
	case 2: // pair ou double pair
		for (int i = 0; i < 13; i++) {
			if (effectif_carte[i] == 2 && i != indice1) {
				indice2 = i;
			}
		}
		if (indice2 != -1) { //double pair
			jeu->joueur[joueur_indice].score_main[0] = 3;
			jeu->joueur[joueur_indice].score_main[1] = indice;
			jeu->joueur[joueur_indice].score_main[2] = indice2;
		}
		else { //paire simple
			jeu->joueur[joueur_indice].score_main[0] = 2;
			jeu->joueur[joueur_indice].score_main[1] = indice;
		}
		break;
	case 3: //brelan min ou full
		for (int i = 0; i < 13; i++) {
			if (effectif_carte[i] == 2 && i != indice1) {//on recherche une paire en plus du brelan
				indice2 = i;
			}
		}
		if (indice2 != -1) { //full
			jeu->joueur[joueur_indice].score_main[0] = 7;
			jeu->joueur[joueur_indice].score_main[1] = indice1;
			jeu->joueur[joueur_indice].score_main[2] = indice2;
		}
		else { //brelan
			jeu->joueur[joueur_indice].score_main[0] = 4;
			jeu->joueur[joueur_indice].score_main[1] = indice;
		}
		break;
	case 4: //carré
		jeu->joueur[joueur_indice].score_main[0] = 8;
		jeu->joueur[joueur_indice].score_main[1] = indice;
		break;
	case 1: //quinte, flush, flush royale, couleur (pas quinte), carte haute
		if (effectif_carte[0] == 1) { //cas de la quinte flush ou royale (max as)
			indice1 = 0;
			int i = 12;
			while (count <= 4) {
				if (effectif_carte[i - 1] == effectif_carte[i]) {
					nombre_suite++;
					i--;
				}
				else {
					break;
				}
				count++;
			}
			count = 0;
			if (nombre_suite == 4) { //quinte flush ou flush royale
				// check couleur en plus pour quinte flush royale sinon quinte flush
				couleur = check_couleur(jeu, joueur_indice, jeu_joueur);
				if (couleur != 0) {
					jeu->joueur[joueur_indice].score_main[0] = 10; //quinte flush royale
					jeu->joueur[joueur_indice].score_main[1] = indice1;
					jeu->joueur[joueur_indice].score_main[3] = couleur;
					goto fin;
				}
				else {
					jeu->joueur[joueur_indice].score_main[0] = 9; //quinte flush non royale
					jeu->joueur[joueur_indice].score_main[1] = indice1;
					goto fin;
				}
			}
			nombre_suite = 0;
		}//ne fait rien si ni quinte flush, ni quinte flush royale
		if (jeu->joueur[joueur_indice].score_main[0] == 0) {//si score_main pas modifié
			for (int i = 12; i > 2; i--) {// 9 fois possible dans le tableau d'effectif d'avoir une suite de 5
			//detection quinte la plus haute (de droite a gauche)
				indice1 = i; //indice val max de la quinte
				j = i;
				while (count <= 5) {
					if (effectif_carte[j - 1] == effectif_carte[j]) {
						nombre_suite++;
						j--;
					}
					else {
						break;
					}
					count++;
				}
				count = 0;
				if (nombre_suite == 5) { //si pas couleur, quinte simple (pas possible quinte flush)
					//check couleur sinon quinte simple
					couleur = check_couleur(jeu, joueur_indice, jeu_joueur);
					if (couleur != 0) {
						jeu->joueur[joueur_indice].score_main[0] = 6; //couleur
						jeu->joueur[joueur_indice].score_main[1] = indice1;
						jeu->joueur[joueur_indice].score_main[3] = couleur;
						goto fin;
					}
					else {//il ne nous reste qu'une quinte simple = une suite
						jeu->joueur[joueur_indice].score_main[0] = 5; //suite
						jeu->joueur[joueur_indice].score_main[1] = indice1;
						goto fin;
					}
				}
				count = 0;
				nombre_suite = 0;
			}
		}
		if (jeu->joueur[joueur_indice].score_main[0] == 0) {// carte haute
			int carte_haute = 0;
			int i = 12;
			while (effectif_carte[i] == 0) {
				i--;
			}
			carte_haute = i;
			jeu->joueur[joueur_indice].score_main[0] = 1; //carte haute
			jeu->joueur[joueur_indice].score_main[1] = carte_haute;
		}
	fin://identificateur sortie de boucle
		break;
	default:
		if (DEBUG == 1) {
			printf("\ndebug default case max\n");
		}
		break;
	}
	if (DEBUG == 1) {
		//debug
		printf("\n");
		for (int i = 0; i < 5; i++) {
			printf("debug:j%d score main 0 = %d\n", i + 1, jeu->joueur[i].score_main[0]);
		}
		//debug
	}

}