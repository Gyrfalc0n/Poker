#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "struct.c"
#include "fonctions.h"


int main(int argc, char** argv) {
    srand((unsigned)time(NULL));
    Jeu jeu;

    distribution(jeu);
    for (int k = 0; k < 15; k++) {
        printf("%d\t", jeu.manche.cartes[k]);
    }
    printf("\n");
    return 0;
}

