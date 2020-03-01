#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


//     VALEUR DES CARTES DANS LE JEU COMPLET 
//     /!\ indice = valeur - 1

// +-------+-------+---------+-------+--------+
// | Carte | Coeur | Carreau | Pique | Trefle |
// +-------+-------+---------+-------+--------+
// | As    | 1     | 14      | 27    | 40     |
// | 2     | 2     | 15      | 28    | 41     |
// | 3     | 3     | 16      | 29    | 42     |
// | 4     | 4     | 17      | 30    | 43     |
// | 5     | 5     | 18      | 31    | 44     |
// | 6     | 6     | 19      | 32    | 45     |
// | 7     | 7     | 20      | 33    | 46     |
// | 8     | 8     | 21      | 34    | 47     |
// | 9     | 9     | 22      | 35    | 48     |
// | 10    | 10    | 23      | 36    | 49     |
// | Valet | 11    | 24      | 37    | 50     |
// | Dame  | 12    | 25      | 38    | 51     |
// | Roi   | 13    | 26      | 39    | 52     |
// +-------+-------+---------+-------+--------+


// STRUCTURES DE JEU

typedef struct {
	int solde; // solde d'argent
	int mise; // mise actuelle perso
	int main[2]; // tableau de deux elements pour les valeur des 2 cartes
	bool is_dealer; // est dealer pour la manche ?
	bool is_big_blind; // est big blind pour la manche ?
	bool is_small_blind; // est small blind pour la manche ?
	int score_main; // score de la main calculé à la fin de la manche pour déterminer WIN
}Joueur;

//     REPARTITION DES CARTES DANS LE TABLEAU actuel
// fonction du nombre de joueurs (les 5 derniers slots réservés pour les cartes du jeu et pas des joueurs)

// +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------++-----------+-----------+-----------+-----------+-----------+
// | Valeur 1    | Valeur 2    | Valeur 3    | Valeur 4    | Valeur 5    | Valeur 6    | Valeur 7    | Valeur 8    | Valeur 9    | Valeur 10   || Valeur 11 | Valeur 12 | Valeur 13 | Valeur 14 | Valeur 15 |
// +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------++-----------+-----------+-----------+-----------+-----------+
// | Carte 1 J 1 | Carte 2 J 1 | Carte 1 J 2 | Carte 2 J 2 | Carte 1 J 3 | Carte 2 J 3 | Carte 1 J 4 | Carte 2 J 4 | Carte 1 J 5 | Carte 2 J 5 || Flop 1    | Flop 2    | Flop 3    | Carte 4   | Carte 5   |
// +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------++-----------+-----------+-----------+-----------+-----------+


typedef struct {
	int actuel[15]; // 5 joueurs x2 + 5 cartes
	int pot; // valeur du pot
	int dealer_indice; // indice du joueur donneur (0 a 4)
	int small_blind; // valeur small blind
	int big_blind; // valeur big blind (= small_blind x2)
}Manche;

// STRUCTURES SYSTEMES





