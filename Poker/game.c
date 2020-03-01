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

// rajouter dans l'instanciations du jeu, l'initialisations des valeurs

void distribution(Jeu jeu) {
	bool to_add;
	int random_carte, j;
	for (int i = 0; i<15;)
	{
		to_add = true;
		random_carte = random(1, 52);
		for (j = 0; j < 15; j++) // on teste si la valeur tirée est deja dans les cartes distribuées
		{
			if (jeu.manche.cartes[j] == random_carte) {
				to_add = false;
			}
		}
		if (to_add) {
			jeu.manche.cartes[i] = random_carte;
			i++;
		}
	}
}