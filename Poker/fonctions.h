#ifndef _FONCTIONS_H
#define _FONCTIONS_H
// STRUCTURES


//             TERMINOLOGIE
//  Jeu = une partie complete jusqua win d'un joueur
//  Manche = une manche de poker = tous les round qui sont faits avec un meme flop
//  Round = un tour de table avec les mises �galis�es. Se termine par l'apparition d'une nouvelle carte sur le flop (1 manche = 3 round)


//     VALEUR DES CARTES DANS LE JEU COMPLET 

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
	int mise; // mise actuelle perso pour la manche courante
	int main[2]; // tableau de deux elements pour les valeur des 2 cartes
	int score_main[4]; // score de la main calcul� � la fin de la manche pour d�terminer WIN | 1er valeur : main | 2eme valeur valeur de la main (ex : carr� par les as) [3eme valeur 2eme valeur (ex : dble pair de 2 et de 8) | 4eme valeur couleur
}Joueur;

//     REPARTITION DES CARTES DANS LE TABLEAU actuel ( 5 JOUEURS )

// +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------++-----------+-----------+-----------+-----------+-----------+
// | Valeur 1    | Valeur 2    | Valeur 3    | Valeur 4    | Valeur 5    | Valeur 6    | Valeur 7    | Valeur 8    | Valeur 9    | Valeur 10   || Valeur 11 | Valeur 12 | Valeur 13 | Valeur 14 | Valeur 15 |
// +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------++-----------+-----------+-----------+-----------+-----------+
// | Carte 1 J 1 | Carte 2 J 1 | Carte 1 J 2 | Carte 2 J 2 | Carte 1 J 3 | Carte 2 J 3 | Carte 1 J 4 | Carte 2 J 4 | Carte 1 J 5 | Carte 2 J 5 || Flop 1    | Flop 2    | Flop 3    | Carte 4   | Carte 5   |
// +-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------++-----------+-----------+-----------+-----------+-----------+


typedef struct {
	int cartes[15]; // 5 joueurs x2 + 5 cartes
	int pot; // valeur du pot
	int dealer_indice; // indice du joueur donneur (0 a 4)
	int small_blind_indice; // indice du joueur small blind (0 a 4) (= indice donneur + 1)
	int big_blind_indice; // indice du joueur donneur (0 a 4) (= indice donneur +2)
	int small_blind; // valeur small blind
	int big_blind; // valeur big blind (= small_blind x2)
	int flop_indice; // 3 pour premier round, 4 pour 2eme et 5 pour dernier (correspond au nb de cartes sur la table)
	int couche[5]; //tableau rempli de 0 pour joueurs qui jouent et devient un 1 pour un joueur couch�
	int parole[5]; //tableau rempli de 0 par defaut et se rempli de 1 pour un round de parole
	int nb_couche; //compteur de personnes couch�es
	bool is_end_round; //est a true si le round est fini
	int who_win; //id du joueur qui gagne la manche
}Manche;

typedef struct {
	int main; // variable donnant la main qui win (ex: 1 = carte haute, 2 = paire etc) POUR LA MANCHE
	int indice; //indice du joueur qui win la PARTIE.
}Win;


// STRUCTURE SYSTEME

typedef struct {
	int initial_solde; // valeur de solde de base (= default solde si pas indiqu�)
	int composition_joueurs[5]; // valeur pour indiquer pour chaque joueur s'il est humain ou la personnalit� tir�e pour l'IA
	Joueur joueur[5]; //instanciation des 5 joueurs de la partie
	Manche manche; // instanciation de la manche
	Win win; //instanciation de la victoire
}Jeu;

//   WIN
//  indice
// 0 - personne
// 1 - J1
// 2 -J2
// ...
// main
// 0 - rien
// 1 - carte haute
// 2 - paire
// 3 - 2 paires
// 4 - brelan
// 5 - quinte (suite)
// 6 - couleur
// 7 - full
// 8 - carr�
// 9 - quinte flush (suite + couleur)
// 10 - quinte flush royale

// COULEURS (code echappement : \033 )

// +---------+--------------+
// |  CODE   |    COLOR     |
// +---------+--------------+
// | [0;31m  | Red          |
// | [1;31m  | Bold Red     |
// | [0;32m  | Green        |
// | [1;32m  | Bold Green   |
// | [0;33m  | Yellow       |
// | [01;33m | Bold Yellow  |
// | [0;34m  | Blue         |
// | [1;34m  | Bold Blue    |
// | [0;35m  | Magenta      |
// | [1;35m  | Bold Magenta |
// | [0;36m  | Cyan         |
// | [1;36m  | Bold Cyan    |
// | [0m     | Reset        |
// +---------+--------------+


// STRUCTURE BOT


// PROTOTYPES

int random(int, int);
bool is_winner_game(Jeu*); //pas utilis� encore
void afficher_cartes(int);
void distribution(Jeu*);
void mise(Jeu*, int, int);
void actualisation_blind(Jeu*);
void blind(Jeu*, int);
void afficher_round(Jeu*, int, int);
void fin_round(Jeu*);
void choix(Jeu*, int, int);
void afficher_main(Jeu*, int);
void compare_main(Jeu*);
int check_couleur(Jeu*, int, int[]);
void check_main(Jeu*, int);
void nouvelle_manche(Jeu*);
int joueur_precedent(Jeu*, int);

#endif




