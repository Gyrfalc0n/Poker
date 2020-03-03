// DECLARATIONS CONSTANTES & VALEUR PAR DEFAUT POUR UN JEU NON PARAMÉTRÉ

const int reference_jeu[52] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52 };
const int default_solde = 2000;
const int default_small_blind = 10;
const int default_big_blind = 20;
const int default_pot = 0;
const int dealer_indice = 0;

// PROTOTYPES

int random(int, int);
void afficher_cartes(int);
void distribution(Jeu*);
void actualisation_blind(Jeu*);
void mise(Jeu*, int, int);
void afficher_round(Jeu*);