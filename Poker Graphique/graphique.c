#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <Windows.h>
#include <mmsystem.h>

#include "lib/libgraphique.h"
#include "fonctions.h"


void afficher_ttes_cartes(Jeu* jeu) {
	Point p = { BASEX, BASEY };
	afficher_image("images/background.bmp", p);
	int count = 0;
	for (int i = 1; i < 53; i++) {
		if (count == 13) {
			p.y += 91;
			p.x = 0;
			count = 0;
		}
		afficher_image(jeu->graph.cartes[i], p);
		count++;
		p.x += 60;
	}
	Point k = { 0, 364 };
	afficher_image(jeu->graph.cartes[0], k);
	PlaySound(L"sounds/shuffle.wav", NULL, SND_ASYNC | SND_FILENAME);
}

void afficher_jeu(Jeu* jeu, int joueur_indice, int flop_indice) {
	int emplacement = 0, mise = 0;
	afficher_image(jeu->graph.cartes[jeu->joueur[joueur_indice].main[0]], jeu->graph.slot_carte[emplacement].slot[0]);
	afficher_image(jeu->graph.cartes[jeu->joueur[joueur_indice].main[1]], jeu->graph.slot_carte[emplacement].slot[1]);
	//affichage image et texte du pot
	mise = jeu->manche.pot;
	char tapis_string[10];
	_itoa(mise, tapis_string, 10);
	char* dollart = "$";
	strcat(tapis_string, dollart);
	afficher_texte(tapis_string, 15, jeu->graph.tapis_texte, yellow);
	if (mise != 0) {
		if (mise < 50) {
			afficher_image(jeu->graph.jetons[0], jeu->graph.tapis_image);

		}
		else if (mise < 100) {
			afficher_image(jeu->graph.jetons[1], jeu->graph.tapis_image);
		}
		else if (mise < 150) {
			afficher_image(jeu->graph.jetons[2], jeu->graph.tapis_image);
		}
		else if (mise < 200) {
			afficher_image(jeu->graph.jetons[3], jeu->graph.tapis_image);
		}
		else if (mise < 250) {
			afficher_image(jeu->graph.jetons[4], jeu->graph.tapis_image);
		}
		else if (mise < 300) {
			afficher_image(jeu->graph.jetons[5], jeu->graph.tapis_image);
		}
		else if (mise < 400) {
			afficher_image(jeu->graph.jetons[6], jeu->graph.tapis_image);
		}
		else if (mise < 500) {
			afficher_image(jeu->graph.jetons[7], jeu->graph.tapis_image);
		}
		else if (mise < 750) {
			afficher_image(jeu->graph.jetons[8], jeu->graph.tapis_image);
		}
		else { //1000
			afficher_image(jeu->graph.jetons[9], jeu->graph.tapis_image);
		}
	}
	for (int i = 0; i < 5; i++) {//on affiche les mises pour les 5 joueurs
		mise = jeu->joueur[joueur_indice].mise;
		char solde_string[10];
		_itoa(jeu->joueur[joueur_indice].mise, solde_string, 10);
		char* dollar = "$";
		strcat(solde_string, dollar);
		char joueur[10] = "Joueur ";
		char joueur2[2];
		_itoa(joueur_indice+1, joueur2, 10);
		strcat(joueur, joueur2);//joueur est le string Joueur exemple : "Joueur 1"
		if (mise != 0) {
			if (mise < 50) {
				afficher_image(jeu->graph.jetons[0], jeu->graph.slot_mises[i]);

			}
			else if (mise < 100) {
				afficher_image(jeu->graph.jetons[1], jeu->graph.slot_mises[i]);
			}
			else if (mise < 150) {
				afficher_image(jeu->graph.jetons[2], jeu->graph.slot_mises[i]);
			}
			else if (mise < 200) {
				afficher_image(jeu->graph.jetons[3], jeu->graph.slot_mises[i]);
			}
			else if (mise < 250) {
				afficher_image(jeu->graph.jetons[4], jeu->graph.slot_mises[i]);
			}
			else if (mise < 300) {
				afficher_image(jeu->graph.jetons[5], jeu->graph.slot_mises[i]);
			}
			else if (mise < 400) {
				afficher_image(jeu->graph.jetons[6], jeu->graph.slot_mises[i]);
			}
			else if (mise < 500) {
				afficher_image(jeu->graph.jetons[7], jeu->graph.slot_mises[i]);
			}
			else if (mise < 750) {
				afficher_image(jeu->graph.jetons[8], jeu->graph.slot_mises[i]);
			}
			else { //1000
				afficher_image(jeu->graph.jetons[9], jeu->graph.slot_mises[i]);
			}
		}
		afficher_texte(solde_string, 15, jeu->graph.slot_texte_mises[emplacement], yellow);//affichage mises par joueur
		afficher_texte(joueur, 15, jeu->graph.texte_joueur[emplacement], white);//afichage string "Joueur 1"
		char solde[20] = "Solde: ";
		char solde2[10];
		char solde3[] = "$";
		_itoa(jeu->joueur[joueur_indice].solde, solde2, 10);
		strcat(solde, solde2);//joueur est le string Joueur exemple : "Joueur 1"
		strcat(solde, solde3);
		int x_solde = jeu->graph.texte_joueur[joueur_indice].x;
		int y_solde = jeu->graph.texte_joueur[joueur_indice].y+20;
		Point coord_solde = { x_solde, y_solde };
		afficher_texte(solde, 11, coord_solde, cyan);//afichage solde joueur
		emplacement++;
		joueur_indice++;
		if (joueur_indice == 5) {
			joueur_indice = 0;
		}
	}
	for (int i = 1; i < 5; i++) { //affichage des cartes de dos
		afficher_image(jeu->graph.cartes[0], jeu->graph.slot_carte[i].slot[0]);
		afficher_image(jeu->graph.cartes[0], jeu->graph.slot_carte[i].slot[1]);
	}
	//affichage flop
	if (flop_indice >= 3) {
		afficher_image(jeu->graph.cartes[jeu->manche.cartes[10]], jeu->graph.flop[0]);
		afficher_image(jeu->graph.cartes[jeu->manche.cartes[11]], jeu->graph.flop[1]);
		afficher_image(jeu->graph.cartes[jeu->manche.cartes[12]], jeu->graph.flop[2]);
	}
	if (flop_indice >= 4) {
		afficher_image(jeu->graph.cartes[jeu->manche.cartes[13]], jeu->graph.flop[3]);
	}
	if (flop_indice == 5) {
		afficher_image(jeu->graph.cartes[jeu->manche.cartes[14]], jeu->graph.flop[4]);
	}

}