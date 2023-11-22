//
// Created by super on 22/11/2023.
//

#include "LectureDonnees.h"
#include <stdio.h>
#include <stdlib.h>
#include "LectureDonnees.h"

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

/**
int main() {
    const char *nomFichier = "fichier.txt";
    int taille;

    // Appeler la fonction pour lire le fichier
    int *tableau = lireFichier(nomFichier, &taille);

    // Afficher les éléments du tableau
    printf("Contenu du tableau :\n");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    // Afficher la taille du tableau
    printf("Taille du tableau : %d\n", taille);

    // Libérer la mémoire allouée pour le tableau
    free(tableau);

    return 0;
}
**/