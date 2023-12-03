//
// Created by clementt on 02/12/23.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_ALEXANDRE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_ALEXANDRE_H

typedef struct Workstation WS;
struct {
    int  num; // numero de la station de travail
    int  nbTaches;     // nombres de tâches de la station de travail
    int* taches; // listes des tâches de la station de travail
    int  duree; // duree totale d'execution des taches dans la station de travail
} Workstation ;


// Solution du problème //
/************************/
typedef struct Solution LigneAssemblage;
struct {
    int nombreDeStations; // nombre de stations
    WS* WS; // tableau des WS
} Solution;

// Graphe de précédence //
/************************/

/* Structure d'un arc */
struct Arc
{
    int sommet_j; // numéro de sommet d'un arc adjacent au sommet initial
    struct Arc* arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet*/
struct Sommet
{
    struct Arc* arc;
    int sommet_i;
    int wsNumber;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int taille;
    int ordre;
    pSommet* pSommet;
} Graphe;

// Donnees chargees //
/********************/
typedef struct Data Donnees;
struct {
    int     maxTaches;     // nombre de taches maximum à exécuter par la ligne d'assemblage
    float*  dureeDeTache;  // tableau des temps d'exécution de chaque tâche
    float   tempsDeCycle;  // temps de cycle max d'une station de travail
    Graphe* precedence;    // graphe orienté de précédences des tâches d'ordre maxTaches
    int**   exclusion;     // matrice d'adjacence du graphe d'exclusions de dimension maxTaches x maxTaches
} Data;

int** lireExclusions(int *ordre) {
    int** exclusions;
    FILE *fichier = fopen("exclusions.txt", "r");

    // Vérifier si le fichier a pu être ouvert
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    int capacite = 10;  // Capacité initiale du tableau
    int *tableau = (int *)malloc(capacite * sizeof(int));

    // Vérifier si l'allocation de mémoire a réussi
    if (tableau == NULL) {
        fprintf(stderr, "Allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }

    int nombre1, nombre2;
    int index = 0;
    *ordre = 0;

    // Lire les nombres du fichier et les stocker dans le tableau
    while (fscanf(fichier, "%d %d", &nombre1, &nombre2) == 1) {
        if (index == capacite) {
            // Si le tableau est plein, augmenter sa capacité
            capacite *= 2;
            tableau = (int *)realloc(tableau, capacite * sizeof(int));

            // Vérifier si la réallocation de mémoire a réussi
            if (tableau == NULL) {
                fprintf(stderr, "Réallocation mémoire échouée.\n");
                exit(EXIT_FAILURE);
            }
        }

        tableau[index++] = nombre1;
        tableau[index++] = nombre2;
        if (nombre1 > *ordre)
            *ordre = nombre1;
        if (nombre2 > *ordre)
            *ordre = nombre2;
    }

    // Fermer le fichier
    fclose(fichier);

    // Mettre à jour la taille pour calculer l'ordre du graphe d'exclusions
    *ordre = *ordre + 1;
    exclusions = (int**) malloc(index*sizeof(int*));
    for(int i=0; i<*ordre ; i++){
        exclusions[i] = (int*) malloc(*ordre *sizeof(int));
        for(int j=0 ; j<*ordre ; j++)
            exclusions[i][j] = 0;
    }
    for(int i=0; i<index; i=i+2){
        exclusions[tableau[i]][tableau[i+1]] = 1;
        exclusions[tableau[i+1]][tableau[i]] = 1;
    }
    free(tableau);

    return exclusions;
}










#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_ALEXANDRE_H
