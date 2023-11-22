//////////////////////////////////////////////////////////////////////////
///          Modele de données du projet                              ///
/////////////////////////////////////////////////////////////////////////

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_LECTUREDONNEES_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_LECTUREDONNEES_H
#include <stdio.h>
#include <stdlib.h>
#include "limits.h"

#define INFINI INT_MAX
#define NIL -1


// Workstation //
/***************/
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

// créer et detruit le graphe
Graphe* CreerGraphe(int ordre);
void    FreeGraphe(Graphe* graphe);

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet, int s1, int s2);

/* affichage des successeurs du sommet num*/
void AfficheSuccesseurs(pSommet * sommet, int num);

/*affichage du graphe avec les successeurs de chaque sommet */
void AffichePrecedences(Graphe* graphe);



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

//////////////////////////////////////////////////////////
//      Prototypes des fonctions de lecture des données
//////////////////////////////////////////////////////////
/* Lire le fichier d'exclusion */
int** lireExclusions(int *ordre);

// Lire le Fichier de precedences et constuit le graphe de precedences
Graphe* LirePrecedences(int taille);

/* Lire le fichier des temps d'opérations */
float* lireOperations(int taille);

/* Lire le temps de cycle */
float* lireTemps_cycle();

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_LECTUREDONNEES_H
