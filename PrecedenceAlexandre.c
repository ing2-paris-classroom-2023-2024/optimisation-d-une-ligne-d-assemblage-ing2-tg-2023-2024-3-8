//
// Created by super on 03/12/2023.
//

#include <stdio.h>
#include "ToolBoxWilliam.h"
#include "Exclusionalexandre.h"

#include <stdlib.h>

struct Tache {
    int id;
    // Autres informations sur la tâche
    // ...
};

struct Probleme {
    int** grapheExclusion;
    int** graphePrecedence;
    int nbTaches;
    int* stations;
    int* tacheAssignee;
};

// Fonction pour calculer le degré d'une tâche dans le graphe de précédence
int calculerDegre(struct Probleme* probleme, int tache) {
    int degre = 0;
    for (int i = 1; i <= probleme->nbTaches; i++) {
        if (probleme->graphePrecedence[i][tache]) {
            degre++;
        }
    }
    return degre;
}

// Fonction pour trouver la tâche avec le degré minimal non assignée
int trouverTacheAvecMinDegre(struct Probleme* probleme) {
    int minDegre = probleme->nbTaches + 1;
    int tacheSelectionnee = -1;

    for (int tache = 1; tache <= probleme->nbTaches; tache++) {
        if (probleme->tacheAssignee[tache] == 0) {
            int degre = calculerDegre(probleme, tache);
            if (degre < minDegre) {
                minDegre = degre;
                tacheSelectionnee = tache;
            }
        }
    }

    return tacheSelectionnee;
}

// Fonction pour vérifier si une tâche peut être ajoutée à une station donnée
int estTacheValide(struct Probleme* probleme, int tache, int station) {
    for (int i = 1; i <= station; i++) {
        if (probleme->grapheExclusion[tache][probleme->stations[i]] != 0) {
            return 0;
        }
    }
    return 1;
}

// Fonction principale pour générer les stations
void genererStations(struct Probleme* probleme) {
    for (int station = 1; station <= probleme->nbTaches; station++) {
        int tache = trouverTacheAvecMinDegre(probleme);

        if (tache == -1) {
            break; // Toutes les tâches ont été assignées
        }

        // Vérifier si la tâche peut être ajoutée à la station
        if (estTacheValide(probleme, tache, station)) {
            probleme->stations[station] = tache;
            probleme->tacheAssignee[tache] = 1;
        } else {
            // Créer une nouvelle station pour la tâche
            probleme->stations[station + 1] = tache;
            probleme->tacheAssignee[tache] = 1;
        }
    }
}

int main() {
    struct Probleme monProbleme;
    int nbTacheexclu,nbTacheprece;

    // Allocation dynamique des tableaux
    monProbleme.grapheExclusion = ContrainteExclusion("exclusions.txt",&nbTacheexclu);
    monProbleme.graphePrecedence = malloc((monProbleme.nbTaches + 1) * sizeof(int*));
    monProbleme.stations = malloc((monProbleme.nbTaches + 1) * sizeof(int));
    monProbleme.tacheAssignee = malloc((monProbleme.nbTaches + 1) * sizeof(int));

    for (int i = 1; i <= monProbleme.nbTaches; i++) {
        monProbleme.tacheAssignee[i] = 0; // Initialisation à zéro
    }

    // Initialisation des graphes d'exclusion et de précédence à partir de l'entrée utilisateur ou d'un fichier
    // ...

    // Générer les stations en utilisant l'heuristique de degré minimal
    genererStations(&monProbleme);

    // Afficher la configuration des stations
    printf("Configuration de stations : ");
    for (int i = 1; i <= monProbleme.nbTaches; i++) {
        printf("%d ", monProbleme.stations[i]);
    }
    printf("\n");

    // Libérer la mémoire allouée
    for (int i = 1; i <= monProbleme.nbTaches; i++) {
        free(monProbleme.grapheExclusion[i]);
        free(monProbleme.graphePrecedence[i]);
    }
    free(monProbleme.grapheExclusion);
    free(monProbleme.graphePrecedence);
    free(monProbleme.stations);
    free(monProbleme.tacheAssignee);

    return 0;
}
