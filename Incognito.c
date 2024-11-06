#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define T 5

typedef enum _couleur {BLANC, NOIR} Couleur ;
typedef enum _type{CHEVALIER, ESPION} Type ;

typedef struct _pion {
    Type type;
    Couleur couleur;
} Pion;

typedef struct _jeu {
    Pion * plateau[T][T]; // chaque case va être l'adresse d'une struct Pion
    Couleur joueur;
} Jeu;

typedef struct {
    int x, y;
} Case, Direction;

typedef struct _mouvement {
    Case depart;
    Case arrivee;
} Mouvement;

/**
 * @brief Affiche le plateau de jeu en ASCII dans le terminal.
 *
 * Cette fonction affiche le plateau de jeu sous forme ASCII, en représentant chaque pion par un caractère spécifique.
 *
 * @param taille La taille du plateau de jeu.
 * @param jeu La structure du jeu contenant le plateau et le joueur courant.
 * @param chevnoir Pointeur vers le pion chevalier noir.
 * @param chevblanc Pointeur vers le pion chevalier blanc.
 * @param espnoir Pointeur vers le pion espion noir.
 * @param espblanc Pointeur vers le pion espion blanc.
 */
void affichePlateauAscii(int taille, Jeu jeu, Pion *chevnoir, Pion *chevblanc, Pion *espnoir, Pion *espblanc){
    printf("  |");
    // Affichage des numéros de colonne
    for (int i = 0; i < taille; i++) {
        printf(" %d|", i);
    }
    printf("\n");
    for (int i = 0; i < taille + 1; i++) {
        printf("--+");
    }
    printf("\n");
    for (int i = 0; i < taille; i++) {
        // Affichage des numéros de ligne
        printf("%d ", i);
        for (int j = 0; j < taille; j++) {
            if (jeu.plateau[i][j] == NULL){
                printf("|  ");
            } else if (jeu.plateau[i][j] -> couleur == NOIR) {
                // Afficher les pions noirs
                printf("| n");
            } else if (jeu.plateau[i][j] -> couleur == BLANC) {
                // Afficher les pions blancs
                printf("| b");
            } 
        }
        printf("| \n");
        for (int i = 0; i < taille + 1; i++) {
            printf("--+");
        }
        printf("\n");
    }
}

/**
 * @brief Affiche le plateau de jeu selon l'option choisie.
 *
 * Cette fonction permet de choisir entre l'affichage ASCII et graphique du plateau.
 *
 * @param opt Option d'affichage (0 pour ASCII, autre pour graphique).
 * @param taille La taille du plateau de jeu.
 * @param jeu La structure du jeu contenant le plateau et le joueur courant.
 * @param chevnoir Pointeur vers le pion chevalier noir.
 * @param chevblanc Pointeur vers le pion chevalier blanc.
 * @param espnoir Pointeur vers le pion espion noir.
 * @param espblanc Pointeur vers le pion espion blanc.
 */
void affiche(int opt, int taille, Jeu jeu, Pion *chevnoir, Pion *chevblanc, Pion *espnoir, Pion *espblanc){
    if (opt == 0){
        affichePlateauAscii(taille,  jeu, chevnoir, chevblanc, espnoir, espblanc);
    } else {
        // Affichage graphique (non implémenté)
    }
}

/**
 * @brief Vérifie si la diagonale entre deux cases est vide.
 *
 * Cette fonction vérifie que toutes les cases sur la diagonale entre la case de départ et la case d'arrivée d'un mouvement sont vides.
 *
 * @param jeu La structure du jeu contenant le plateau.
 * @param mov Le mouvement à vérifier.
 * @return 0 si la diagonale est vide, 1 sinon.
 */
int diagonaleVide(Jeu jeu, Mouvement mov){
    // Détermine d'abord quelle diagonale on vérifie
    // Diagonales côté droit
    if (mov.depart.x < mov.arrivee.x){
        // Diagonale bas droite
        if (mov.depart.y < mov.arrivee.y){
            for (int i = 1; i < abs(mov.arrivee.x - mov.depart.x); i++){
                if (jeu.plateau[mov.depart.x + i][mov.depart.y + i] != NULL){
                    return 1;
                }
            }
            return 0;
        // Diagonale haut droite
        } else if (mov.depart.y > mov.arrivee.y){
            for (int i = 1; i < abs(mov.arrivee.x - mov.depart.x); i++){
                if (jeu.plateau[mov.depart.x + i][mov.depart.y - i] != NULL){
                    return 1;
                }
            }
            return 0;
        }
    // Diagonales côté gauche
    } else if (mov.depart.x > mov.arrivee.x){
        // Diagonale bas gauche
        if (mov.depart.y < mov.arrivee.y){
            for (int i = 1; i < abs(mov.arrivee.x - mov.depart.x); i++){
                if (jeu.plateau[mov.depart.x - i][mov.depart.y + i] != NULL){
                    return 1;
                }
            }
            return 0;
        // Diagonale haut gauche
        } else if (mov.depart.y > mov.arrivee.y){
            for (int i = 1; i < abs(mov.arrivee.x - mov.depart.x); i++){
                if (jeu.plateau[mov.depart.x - i][mov.depart.y - i] != NULL){
                    return 1;
                }
            }
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Vérifie si l'abscisse entre deux cases est vide.
 *
 * Cette fonction vérifie que toutes les cases sur l'axe horizontal entre la case de départ et la case d'arrivée d'un mouvement sont vides.
 *
 * @param jeu La structure du jeu contenant le plateau.
 * @param mov Le mouvement à vérifier.
 * @return 0 si l'abscisse est vide, 1 sinon.
 */
int abscisseVide(Jeu jeu, Mouvement mov){
    // Abscisse côté droit
    if (mov.depart.x < mov.arrivee.x){
        for (int i = 1; i < abs(mov.arrivee.x - mov.depart.x); i++){
            if (jeu.plateau[mov.depart.x + i][mov.depart.y] != NULL){
                return 1;
            }
        }
        return 0;
    // Abscisse côté gauche
    } else if (mov.depart.x > mov.arrivee.x){
        for (int i = 1; i < abs(mov.arrivee.x - mov.depart.x); i++){
            if (jeu.plateau[mov.depart.x - i][mov.depart.y] != NULL){
                return 1;
            }
        }
        return 0;
    }
    return 1;
}

/**
 * @brief Vérifie si l'ordonnée entre deux cases est vide.
 *
 * Cette fonction vérifie que toutes les cases sur l'axe vertical entre la case de départ et la case d'arrivée d'un mouvement sont vides.
 *
 * @param jeu La structure du jeu contenant le plateau.
 * @param mov Le mouvement à vérifier.
 * @return 0 si l'ordonnée est vide, 1 sinon.
 */
int ordonneeVide(Jeu jeu, Mouvement mov){
    // Ordonnée bas
    if (mov.depart.y < mov.arrivee.y){
        for (int i = 1; i < abs(mov.arrivee.y - mov.depart.y); i++){
            if (jeu.plateau[mov.depart.x][mov.depart.y + i] != NULL){
                return 1;
            }
        }
        return 0;
    // Ordonnée haut
    } else if (mov.depart.y > mov.arrivee.y){
        for (int i = 1; i < abs(mov.arrivee.y - mov.depart.y); i++){
            if (jeu.plateau[mov.depart.x][mov.depart.y - i] != NULL){
                return 1;
            }
        }
        return 0;
    }
    return 1;
}

/**
 *@brief Vérifie si un joueur essaye de placer un de ses pions dans son chateau
 *
 * @param taille La taille du plateau de jeu.
 * @param jeu La structure du jeu contenant le plateau et le joueur courant.
 * @param x Abscisse du pion
 * @param y Ordonnée du pion
 */
int dansSonChateau(Jeu jeu, int x, int y, int taille){
    if (jeu.joueur == BLANC && x == taille - 1 && y == 0){
        return 1;
    }
    if (jeu.joueur == NOIR && x == 0 && y == taille -1){
        return 1;
    }
    return 0;
}


/**
 * @brief Vérifie si un mouvement est possible selon les règles du jeu.
 *
 * Cette fonction détermine si un mouvement est autorisé en fonction de l'état actuel du plateau et des règles du jeu.
 *
 * @param taille La taille du plateau de jeu.
 * @param jeu La structure du jeu contenant le plateau et le joueur courant.
 * @param mov Le mouvement à vérifier.
 * @param chevnoir Pointeur vers le pion chevalier noir.
 * @param chevblanc Pointeur vers le pion chevalier blanc.
 * @param espnoir Pointeur vers le pion espion noir.
 * @param espblanc Pointeur vers le pion espion blanc.
 * @return 0 si le mouvement est possible, 1 sinon.
 */
int movPossible(int taille, Jeu jeu, Mouvement mov, Pion *chevnoir, Pion *chevblanc, Pion *espnoir, Pion *espblanc){
    // Vérifie que les points de départ et d'arrivée sont bien dans le plateau
    if (0 <= mov.depart.x && mov.depart.x < taille && 0 <= mov.arrivee.x && mov.arrivee.x < taille
        && 0 <= mov.depart.y && mov.depart.y < taille && 0 <= mov.arrivee.y && mov.arrivee.y < taille){

        // Vérifie que le pion de départ appartient au joueur courant
        if (jeu.plateau[mov.depart.x][mov.depart.y] != NULL && jeu.plateau[mov.depart.x][mov.depart.y]->couleur == jeu.joueur){

            // Vérifie que le joueur ne déplace pas un pion dans son propre château
            if (dansSonChateau(jeu, mov.arrivee.x, mov.arrivee.y, taille)){
                printf("Vous ne pouvez pas entrer dans votre propre ch%cteau.\n", 226);
                return 1;
            }

            // Vérifie que la case d'arrivée est vide
            if (jeu.plateau[mov.arrivee.x][mov.arrivee.y] != NULL){
                printf("La case d'arriv%ce est occup%ce.\n", 130, 130);
                return 1;
            }

            // Vérifie le mouvement (diagonale, horizontale ou verticale)
            if ((mov.depart.x != mov.arrivee.x && mov.depart.y != mov.arrivee.y)){
                if (diagonaleVide(jeu, mov) == 0){
                    return 0;
                } else {
                    printf("Diagonale non vide\n");
                }
            } else if ((mov.depart.x != mov.arrivee.x && mov.depart.y == mov.arrivee.y)){
                if (abscisseVide(jeu, mov) == 0){
                    return 0;
                } else {
                    printf("Abscisse non vide\n");
                }
            } else if ((mov.depart.x == mov.arrivee.x && mov.depart.y != mov.arrivee.y)){
                if (ordonneeVide(jeu, mov) == 0){
                    return 0;
                } else {
                    printf("Ordonn%ce non vide\n", 130);
                }
            } else {
                printf("Mouvement invalide.\n");
            }
        } else {
            printf("Vous essayez de d%cplacer un pion ennemi ou une case vide.\n", 130);
        }
    } else {
        printf("D%cplacement en dehors du plateau.\n", 130);
    }
    return 1;
}


/**
 * @brief Vérifie si la case d'arrivée est dans les quatre voisins orthogonaux de la case départ.
 *
 * @param taille La taille du plateau de jeu.
 * @param jeu Pointeur vers la structure du jeu.
 * @param mov Le mouvement à vérifier.
 * @return 0 si la case d'arrivée est un voisin valide, 1 sinon.
 */
int dansQuatreVoisins(int taille, Jeu *jeu, Mouvement mov){
    // Vérifie que le pion interrogateur est bien dans le tableau
    if (0 <= mov.depart.x && mov.depart.x < taille && 0 <= mov.depart.y && mov.depart.y < taille){
        // Vérifie qu'il y a bien un pion dans la case qui interroge
        if (jeu->plateau[mov.depart.x][mov.depart.y] != NULL) {
            // Vérifie que le pion qui interroge est bien un allié
            if (jeu->plateau[mov.depart.x][mov.depart.y]->couleur == jeu->joueur){
                // Vérifie si le pion interrogé est bien dans le plateau
                if (0 <= mov.arrivee.x && mov.arrivee.x < taille && 0 <= mov.arrivee.y && mov.arrivee.y < taille){
                    // Vérifie qu'il y a bien un pion dans la case qui est interrogée
                    if (jeu->plateau[mov.arrivee.x][mov.arrivee.y] != NULL) {
                        // Vérifie que le pion interrogé est bien un ennemi
                        if (jeu->plateau[mov.arrivee.x][mov.arrivee.y]->couleur != jeu->joueur){
                            // Vérifie si la case arrivée est un voisin de la case départ
                            int dx = abs(mov.arrivee.x - mov.depart.x);
                            int dy = abs(mov.arrivee.y - mov.depart.y);

                            // Vérifie si mov.arrivee est l'une des 4 cases voisines
                            if ((dx == 1 && dy == 0) || (dx == 0 && dy == 1)){
                                return 0; // Cas valide
                            } else {
                                printf("La case d'arrivée n'est pas un voisin valide.\n");
                            }
                        } else { printf("Le pion qui est interrog%c est un alli%c.\n", 130, 130);}
                    } else {printf("Pas de pion dans la case qui est interrog%ce.\n", 130);}
                }
            } else {printf("Le pion qui interroge n'est pas un alli%c.\n", 130);}
        } else {printf("Pas de pion dans la case qui interroge.\n");}
    }
    printf("Interrogation impossible.\n");
    return 1;
}

/**
 * @brief Gère le déplacement des pions sur le plateau.
 *
 * Cette fonction permet au joueur dont c'est le tour de déplacer un de ses pions selon les règles du jeu.
 *
 * @param f Pointeur vers le fichier de sauvegarde.
 * @param jeu Pointeur vers la structure du jeu.
 * @param taille La taille du plateau de jeu.
 * @param chevnoir Pointeur vers le pion chevalier noir.
 * @param chevblanc Pointeur vers le pion chevalier blanc.
 * @param espnoir Pointeur vers le pion espion noir.
 * @param espblanc Pointeur vers le pion espion blanc.
 * @return 0 si le déplacement a été effectué, 1 en cas d'erreur.
 */
int deplacement(FILE *f, Jeu *jeu, int taille, Pion *chevnoir, Pion *chevblanc, Pion *espnoir, Pion *espblanc){
    Mouvement mov;
    // Boucle pour redemander tant que le déplacement n'est pas licite
    int valMovPossible = 1;
    while (valMovPossible != 0){
        printf("Quel d%cplacement pour le joueur %s?\n     Saisie sous la forme (a, b) --> (c, d).\n", 130, jeu->joueur == BLANC ? "BLANC" : "NOIR");
        if (scanf(" (%d, %d) --> (%d, %d)", &mov.depart.x, &mov.depart.y, &mov.arrivee.x, &mov.arrivee.y) != 4){
            printf("Entr%ce invalide. Veuillez réessayer au format (a, b) --> (c, d).\n", 130);
            return 1;
        }
        if(f != NULL)
            fprintf(f, "%c %c%d->%c%d\n", 'D', 'a' + mov.depart.y, mov.depart.x + 1, 'a' + mov.arrivee.y, mov.arrivee.x + 1);
        valMovPossible = movPossible(taille, *jeu, mov, chevnoir, chevblanc, espnoir, espblanc);
    }

    jeu->plateau[mov.arrivee.x][mov.arrivee.y] = jeu->plateau[mov.depart.x][mov.depart.y];
    jeu->plateau[mov.depart.x][mov.depart.y] = NULL;

    return 0;
}

/**
 * @brief Gère l'interrogation d'un pion ennemi.
 *
 * Cette fonction permet au joueur courant d'interroger un pion ennemi situé dans l'une des quatre cases adjacentes à l'un de ses pions.
 *
 * @param f Pointeur vers le fichier de sauvegarde.
 * @param jeu Pointeur vers la structure du jeu.
 * @param taille La taille du plateau de jeu.
 * @param chevnoir Pointeur vers le pion chevalier noir.
 * @param chevblanc Pointeur vers le pion chevalier blanc.
 * @param espnoir Pointeur vers le pion espion noir.
 * @param espblanc Pointeur vers le pion espion blanc.
 * @return 0 si l'interrogation a révélé l'espion ennemi, 1 si l'espion allié a été perdu, 2 si l'interrogation n'a pas abouti.
 */
int interrogation(FILE *f, Jeu *jeu, int taille, Pion *chevnoir, Pion *chevblanc, Pion *espnoir, Pion *espblanc){
    Pion *espennemi;
    Pion *espallie;
    if (jeu->joueur == BLANC){
        espennemi = espnoir;
        espallie = espblanc;
    } else {
        espennemi = espblanc;
        espallie = espnoir;
    }

    int res4voisins = 1;
    Mouvement interro;

    while (res4voisins != 0){
        printf("Quel pion %s est l'interrogateur ?\n   Saisie sous la forme (x, y)\n", jeu->joueur == BLANC ? "blanc" : "noir");
        if (scanf(" (%d, %d)", &interro.depart.x, &interro.depart.y) != 2){
            printf("Entr%ce invalide.\n", 130);
            return 3;
        }

        printf("Quel pion est questionné ?\n   Saisie sous la forme (x, y)\n");
        if (scanf(" (%d, %d)", &interro.arrivee.x, &interro.arrivee.y) != 2){
            printf("Entr%ce invalide.\n", 130);
            return 3;
        }
        if(f != NULL)
            fprintf(f, "%c %c%d->%c%d\n", 'I', 'a' + interro.depart.y, interro.depart.x + 1, 'a' + interro.arrivee.y, interro.arrivee.x + 1);
        res4voisins = dansQuatreVoisins(taille, jeu, interro);
    }

    if (jeu->plateau[interro.arrivee.x][interro.arrivee.y] == espennemi){
        printf("Le gagnant est le joueur %s : BRAVO ! \n", jeu->joueur == BLANC ? "BLANC" : "NOIR");
        if(f != NULL)
            fprintf(f, "%s\n", jeu->joueur == BLANC ? "B" : "N");
        return 0; // Interrogé : espion
    } else if (jeu->plateau[interro.depart.x][interro.depart.y] == espallie){
        printf("Joueur %s, vous avez interrog%c un chevalier avec votre espion...\n\n Le gagnant est le joueur %s\n", jeu->joueur == BLANC ? "blanc" : "noir", 130, jeu->joueur == BLANC ? "noir" : "blanc");
        return 1; // Interrogé : chevalier & interrogateur espion
    }
    printf("Joueur %s, vous n'avez pas trouv%c l'espion de votre adversaire...\n    Et en plus, votre chevalier s'est fait empoisonner...\n", jeu->joueur == BLANC ? "blanc" : "noir", 130);
    jeu->plateau[interro.depart.x][interro.depart.y] = NULL;
    return 2;  // Partie continue car interrogateur pas espion et interrogé pas espion
}

/**
 * @brief Vérifie si un espion a atteint le château adverse.
 *
 * Cette fonction vérifie si un espion a atteint le château adverse, ce qui signifie la fin de la partie.
 *
 * @param jeu Pointeur vers la structure du jeu.
 * @param taille La taille du plateau de jeu.
 * @param espnoir Pointeur vers le pion espion noir.
 * @param espblanc Pointeur vers le pion espion blanc.
 * @return 1 si un espion a atteint le château adverse, 0 sinon.
 */
int checkChateau(Jeu *jeu, int taille, Pion *espnoir, Pion *espblanc){
    // Vérifier si l'espion adverse a atteint votre château
    if ((jeu->plateau[taille - 1][0] == espnoir) || (jeu->plateau[0][taille - 1] == espblanc)){
        return 1; // La partie est gagnée par l'adversaire
    }
    return 0;
}

/**
 * @brief Initialise le plateau de jeu avec les pions en position de départ.
 *
 * Cette fonction place les pions chevaliers et espions sur le plateau selon les règles du jeu, et détermine aléatoirement la position des espions.
 *
 * @param f Pointeur vers le fichier de sauvegarde.
 * @param jeu Pointeur vers la structure du jeu.
 * @param taille La taille du plateau de jeu.
 * @param chevnoir Pointeur vers le pion chevalier noir.
 * @param chevblanc Pointeur vers le pion chevalier blanc.
 * @param espnoir Pointeur vers le pion espion noir.
 * @param espblanc Pointeur vers le pion espion blanc.
 */
void initPlateau(Jeu *jeu, int taille, Pion *chevnoir, Pion *chevblanc){
    
    // Initialisation de toutes les cases du plateau à NULL
    for (int i = 0; i < taille; i++){
        for (int j = 0; j < taille; j++){
            jeu->plateau[i][j] = NULL;
        }
    }

    // Placement des pions de type chevalier dans les angles
    for (int i = 2; i < taille; i++){
        for (int j = 0; j < i - 1; j++){
            jeu->plateau[i][j] = chevblanc;
            jeu->plateau[j][i] = chevnoir; // On inverse i et j pour obtenir directement l'angle opposé
        }
    }

    // Remplacement des coins par NULL pour les châteaux
    jeu->plateau[taille - 1][0] = NULL; // Château blanc
    jeu->plateau[0][taille - 1] = NULL; // Château noir

}

void initEspion(FILE *f, Jeu *jeu, int taille, Pion *espnoir, Pion *espblanc){
    int nbpions = ((taille-1)*(taille-2)/2)-1; // Calcul du nombre de pions par équipe selon la taille du plateau
    // Randomisation du numéro des espions
    int numinterdit = ((taille * taille) / 2 - (taille * 5 / 2) + 4);
    int numespblanc = rand() % (nbpions + 2);
    int numespnoir = rand() % (nbpions + 2);
    while (numespblanc == 0 || numespblanc == numinterdit){
        numespblanc = rand() % (nbpions + 2);
    }
    while (numespnoir == 0 || numespnoir == numinterdit){
        numespnoir = rand() % (nbpions + 2);
    }

    // Remplacement de 2 chevaliers par les espions
    int cpt = 0;
    for (int i = 2; i < taille; i++){
        for (int j = 0; j < i - 1; j++){
            cpt += 1;
            if (cpt == numespblanc){
                jeu->plateau[i][j] = espblanc;
            }
            if (cpt == numespnoir){
                jeu->plateau[j][i] = espnoir;
            }
        }
    }
    // écriture de la position des espions dans le fichier sauvegarde si l'on sauvegarde
    if(f != NULL){
        for (int i = 0; i < taille; i++){
            for (int j = 0; j < taille; j++){
                if (jeu->plateau[i][j] == espblanc){
                    fprintf(f, "B %c%d\n", 'a' + j, i + 1);
                } else if (jeu->plateau[i][j] == espnoir){
                    fprintf(f, "N %c%d\n", 'a' + j, i + 1);
                }
            }
        }
    }
}

/**
 * @brief Vide le buffer d'entrée pour éviter les problèmes de saisie.
 */
void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Vide le buffer d'entrée jusqu'à la fin de la ligne
}

/**
 * @brief Charge une partie sauvegardée depuis un fichier.
 *
 * Cette fonction lit un fichier de sauvegarde et initialise le plateau de jeu en conséquence.
 *
 * @param f Pointeur vers le fichier de sauvegarde.
 * @param jeu Pointeur vers la structure du jeu.
 * @param taille La taille du plateau de jeu.
 * @param chevnoir Pointeur vers le pion chevalier noir.
 * @param chevblanc Pointeur vers le pion chevalier blanc.
 * @param espnoir Pointeur vers le pion espion noir.
 * @param espblanc Pointeur vers le pion espion blanc.
 */
void chargeJeu(FILE *f, Jeu *jeu, int taille, Pion *chevnoir, Pion *chevblanc, Pion *espnoir, Pion *espblanc) {
    initPlateau(jeu, taille, chevnoir, chevblanc); // Initialisation du plateau
    Pion *espennemi;

    // Lecture du fichier
    char line[256];
    while (fgets(line, sizeof(line), f)){
        if (jeu->joueur == BLANC){
            espennemi = espnoir;
        } else {
            espennemi = espblanc;
        }
        if (line[0] == 'B' || line[0] == 'N'){
            if (line[1] == ' '){
                // Positions des espions
                char col;
                int row;
                //lecture de la ligne dans le fichier
                sscanf(line + 2, "%c%d", &col, &row);
                int x = row - 1;
                int y = col - 'a';
                if (line[0] == 'B'){
                    jeu->plateau[x][y] = espblanc; // placement de l'espion blanc dans le plateau
                } else {
                    jeu->plateau[x][y] = espnoir; // placement de l'espion noir dans le plateau
                }
            } else {
                // Détermine quel joueur commence
                jeu->joueur = (line[0] == 'B') ? BLANC : NOIR;
            }

        } else if (line[0] == 'D' || line[0] == 'I'){
            // Actions interrogation et mouvement
            char moveType;
            char a, c;
            int b, d;
            sscanf(line, "%c %c%d->%c%d", &moveType, &a, &b, &c, &d);
            Mouvement mov;
            mov.depart.x = a - 1;
            mov.depart.y = b - 'a';
            mov.arrivee.x = c - 1;
            mov.arrivee.y = d - 'a';

            if (moveType == 'D'){
                jeu->plateau[mov.arrivee.x][mov.arrivee.y] = jeu->plateau[mov.depart.x][mov.depart.y];
                jeu->plateau[mov.depart.x][mov.depart.y] = NULL;
            } else if (moveType == 'I'){
                if (dansQuatreVoisins(taille, jeu, mov) == 0){
                    // Si le pion interrogé n'est pas l'espion ennemi alors l'interrogateur disparaît
                    if (jeu->plateau[mov.arrivee.x][mov.arrivee.y] != espennemi){
                        jeu->plateau[mov.depart.x][mov.depart.y] = NULL;
                    }
                }
            }
            // Changement de tour
            jeu->joueur = (jeu->joueur == BLANC) ? NOIR : BLANC;
        }
    }

}

/**
 * @brief Point d'entrée principal du programme.
 *
 * Cette fonction gère la boucle principale du jeu, y compris l'initialisation, le traitement des options en ligne de commande, et la gestion des tours de jeu.
 *
 * @param argc Le nombre d'arguments en ligne de commande.
 * @param argv Le tableau des arguments en ligne de commande.
 * @return 0 si le programme s'est exécuté correctement, une autre valeur en cas d'erreur.
 */
int main(int argc, char* argv[]){
    srand( time( NULL ) );
    int taille=T;
    int optg = 0; // Option graphique
    Jeu jeu;
    FILE *f = NULL;
    FILE *fLoad = NULL;
    char *fichierSave = NULL;
    char *fichierCharger = NULL;
    int ascii = 0, graph= 0;

    // Gestion des paramètres transmis en ligne de commande
    for (int i = 1; i < argc; i++){
        // Option pour choisir entre affichage ASCII ou graphique
        if (strcmp(argv[i], "-a") == 0){
            optg = 0;
            ascii = 1;
        } else if (strcmp(argv[i], "-g") == 0){
            optg = 1;
            graph = 1;
        // Option pour sauvegarder
        } else if (strcmp(argv[i], "-s") == 0){
            if (i + 1 < argc){
                fichierSave = argv[++i];
            } else {
                printf("Erreur : Chemin de fichier manquant pour l'option de sauvegarde -s\n");
                return 1;
            }
        // Option chargement d'une sauvegarde
        } else if (strcmp(argv[i], "-c") == 0){
            if (i + 1 < argc){
                fichierCharger = argv[++i];
            } else {
                printf("Erreur : Chemin de fichier manquant pour l'option de chargement de sauvegarde -c\n");
                return 1;
            }
        // Option inconnue
        } else {
            printf("Option inconnue : %s\n", argv[i]);
            return 1;
        }
    }

    // Empêche de mettre à la fois l'option d'affichage ASCII et graphique
    if (ascii && graph){
        printf("Erreur : Les options -a et -g s'excluent\n");
        return 1;
    }

    // Si on a fourni un nom de fichier d'enregistrement
    if (fichierSave != NULL){
        f = fopen(fichierSave,"w");
        if(f == NULL){
            printf("Erreur lors de l'ouverture du fichier de sauvegarde choisi.\n");
            return 1;
        }
    }

    // Initialisation des 4 pions différents
    Pion chevblanc = {CHEVALIER, BLANC};
    Pion chevnoir = {CHEVALIER, NOIR};
    Pion espblanc = {ESPION, BLANC};
    Pion espnoir = {ESPION, NOIR};

    if(fichierCharger != NULL){
        fLoad = fopen(fichierCharger, "r");
        if(fLoad == NULL){
            printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
            return 1;
        }
        chargeJeu(fLoad, &jeu, taille, &chevnoir, &chevblanc, &espnoir, &espblanc);
        fclose(fLoad);
    } else {
        initPlateau(&jeu, taille, &chevnoir, &chevblanc); // Initialisation du plateau
        initEspion(f, &jeu, taille, &espnoir, &espblanc); // initialisation des espions

        int commence = rand() %10;
        if (commence % 2 == 0){
            jeu.joueur = NOIR;
        } else {
            jeu.joueur = BLANC;
        }
        if(f != NULL)
            fprintf(f, "%c\n", jeu.joueur == BLANC ? 'B' : 'N');
    }

    printf("Bienvenue dans Incognito\n");
    affiche(optg, taille, jeu, &chevnoir, &chevblanc, &espnoir, &espblanc); // Affichage du plateau de départ

    int resinterro = 0;
    // Boucle de jeu
    int gamestatus = 1;
    while (gamestatus){
        int suivant = 1;
        // Boucle pour permettre au joueur de rechoisir entre 'd', 'i' et 'q'
        while (suivant){
            char choix = '0';
            while(choix != 'i' && choix != 'd' && choix != 'q'){
                printf("Joueur %s, voulez-vous faire un d%cplacement, une interrogation ou quitter (et sauvegarde si l'option est activ%ce) la partie ? ('d' ou 'i' ou 'q')\n", jeu.joueur == BLANC ? "BLANC" : "NOIR", 130, 130);
                if (scanf(" %c", &choix) != 1){
                    while (getchar() != '\n');
                    clearInputBuffer();
                    choix = '0';
                    continue;
                }
            }
            if (choix == 'q'){
                if(f != NULL)
                    fclose(f);
                suivant = 0;
                gamestatus = 0;

            }
            if (choix == 'd'){
                if (deplacement(f, &jeu, taille, &chevnoir, &chevblanc, &espnoir, &espblanc) == 0){
                    if (checkChateau(&jeu, taille, &espnoir, &espblanc) == 1){
                        printf("Le gagnant est le joueur %s : BRAVO ! \n", jeu.joueur == BLANC ? "BLANC" : "NOIR");
                        gamestatus = 0;
                    }
                    suivant = 0;
                }

            } else if (choix == 'i'){
                resinterro = interrogation(f, &jeu, taille, &chevnoir, &chevblanc, &espnoir, &espblanc);
                if (resinterro == 0){ // Interrogé : espion
                    if(f != NULL)
                        fclose(f);
                    suivant = 0;
                    gamestatus = 0;
                } else if (resinterro == 1) {  // Interrogé : chevalier & interrogateur espion
                    if(f != NULL)
                        fclose(f);
                    suivant = 0;
                    gamestatus = 0;
                } else if (resinterro == 2){
                    suivant = 0;
                    affiche(optg, taille, jeu, &chevnoir, &chevblanc, &espnoir, &espblanc);
                }
            }
            affiche(optg, taille, jeu, &chevnoir, &chevblanc, &espnoir, &espblanc);
        }
        jeu.joueur = (jeu.joueur == BLANC ? NOIR : BLANC);
        if(f != NULL)
            fprintf(f, "%c\n", jeu.joueur == BLANC ? 'B' : 'N');
    }
    return 0;
}
