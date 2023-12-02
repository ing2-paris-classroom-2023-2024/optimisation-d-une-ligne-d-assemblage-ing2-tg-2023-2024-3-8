//
// Created by Willyson on 02/12/2023.
//

#include "ToolBoxWilliam.h"

void wTriTopologique(sTache *prListeTache) {
    int n = prListeTache[0].id; // Nombre total de tâches
    int *successeurs = calloc(n + 1, sizeof(int));
    int *queue = calloc(n, sizeof(int)), front = 0, rear = 0;

    // Calculer le nombre de successeurs pour chaque tâche
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < prListeTache[i].nbPrecedentes; j++) {
            successeurs[prListeTache[i].tListeTachePrecedente[j]]++;
        }
    }

    // Ajouter les tâches sans prédécesseurs à la file d'attente
    for (int i = 1; i <= n; i++) {
        if (successeurs[i] == 0) {
            queue[rear++] = i;
        }
    }

    // Appliquer le tri topologique
    while (front < rear) {
        int actuel = queue[front++];
        printf("Tache %d\n", prListeTache[actuel].id);

        for (int i = 0; i < prListeTache[actuel].nbPrecedentes; i++) {
            int precedente = prListeTache[actuel].tListeTachePrecedente[i];
            if (--successeurs[precedente] == 0) {
                queue[rear++] = precedente;
            }
        }
    }
    free(successeurs);
    free(queue);
}



