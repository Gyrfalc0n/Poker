# Poker Graphique v2.3
Poker Graphique est un projet étudiant en première année de DUT Réseaux et Télécoms. Il s'agit d'un jeu de poker en variante *Texas Hold'em*.

![Poker Graphique](https://github.com/Gyrfalc0n/Poker/blob/master/poker1.png)
## Description
Poker Graphique est un jeu codé en **C**, s'executant en fenêtre grâce à la **SDL 1.2**. Le jeu comprends aussi quelques sons. Pour information, il est compilé en 32 bits.

## Comment jouer ?
Suivez ces instructions pour savoir comment jouer et comment faire fonctionner le jeu.
### Lancer le jeu
* **Extraire** le fichier *.rar* que vous trouverez dans les [*Releases*](https://github.com/Gyrfalc0n/Poker/releases)
* **Executer** le *.exe*
### Jouer
* Chaque joueur commence avec un solde d'argent correspondant à 2000$.
* Lors d'une manche, chaque joueur reçoit 2 cartes.
* Un joueur est désigné donneur, le suivant doit s’acquitter d'une petite somme (small blind) , le suivant du double de cette somme (big blind)  . Le donneur tourne à chaque manche. Il est visible par le jeton D.
* 3 cartes sont alors révélées au milieu de la table.
* Vient alors un tour de mise pour chaque joueur. Une carte suivante est révélée une fois que tous les joueurs encore en jeu ont des mises identiques. Il y a jusqu'à 5 cartes au milieu amenant le total de cartes par joueur à 7.
* Chaque joueur peut choisir de suivre (aligner sa mise avec celle du joueur précédent), relancer (miser plus) se coucher (se retirer de la manche) ou parole (action de ne pas miser mais continuer quand même la partie. Cette option n'est disponible que lorsque le joueur précédent l'a faite).
* Une fois les 5 cartes présentes au milieu, si les mises sont identiques, les mains des joueurs restants sont analysées et le(s) gagnant(s) sont trouvés et gagnent le pot. (Ou se le partagent dans le cas de plusieurs gagnants).
* La partie continue jusqu'à ce qu'il ne reste qu'un joueur avec de l'argent en réserve, en sachant qu'au fur à mesure des manches, les small blind et big blind vont augmenter.

*Liste des mains gagnantes par ordre décroissant :*

> Quinte Flush Royale (suite de 5 cartes de la même couleur : 10, valet, dame, roi, as)

> Quinte Flush (suite de 5 cartes de la même couleur)

> Carré (4 cartes identiques)

> Full (Un brelan et une paire)

> Couleur (5 cartes de la même couleur)

> Quinte (suite de 5 cartes)

> Brelan (3 cartes identiques)

> Double Paire (2 paires)

> Paire (2 cartes identiques)

> Carte haute (la main la plus basse se joue à la carte de la valeur la plus haute)

### Contrôles
Le jeu utilise les touches du clavier comme contrôles. Plus particulièrement, les touches sont les chiffres **1**, **2**, **3** et **4** du pavé numérique ainsi que la touche **Entrée**.

## Auteur
* [**Gyrfalc0n**](https://github.com/Gyrfalc0n)
