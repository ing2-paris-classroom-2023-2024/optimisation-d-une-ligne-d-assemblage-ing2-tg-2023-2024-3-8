//
// Created by Willyson on 02/12/2023.
//

#include "ToolBoxWilliam.h"

sPoste* wRepartitionStationTemps(sTache* prTabTache, float prTempsDeCycle,sParametre *prParametre) {
//https://www.geeksforgeeks.org/program-best-fit-algorithm-memory-management/ UTilisation d'un algorithmme de type best fit
    //Nombre de taches
    int vNombreTaches = prParametre->cNombreOperations;


    //Variables pour les stations
    //Création d'une liste de vNombreTaches stations
    sPoste *tListePoste = (sPoste *) malloc((vNombreTaches) * sizeof(sPoste));
    //Index de la station (commence à -1 car le numéro de la station commence à 0)
    int vIndexStation = -1;
    //Tableau contenant les temps totaux de chaque station
    float *vTempsParStation = (float *) malloc((vNombreTaches) * sizeof(float));

    //Variable temporaire pour le tri à bulles
    sTache sTacheTemp;

    for (int j = 0; j < vNombreTaches + 1; j++) {
        tListePoste[j].taches = (int *) malloc(sizeof(int));
        tListePoste[j].taches[0] = 0; // Initialise la taille du tableau de tâches à 0
        vTempsParStation[j] = 0; // Initialise le temps total de chaque station à 0
    }

    // Tri à bulles
    for (int i = 0; i < vNombreTaches ; i++) {
        for (int j = 0; j < vNombreTaches-i; j++) {
            if (prTabTache[j].temps < prTabTache[j+1].temps) {
                sTacheTemp = prTabTache[j];
                prTabTache[j] = prTabTache[j+1];
                prTabTache[j+1] = sTacheTemp;
            }
        }
    }

    //Boucle principale
    for (int vTaches = 0; vTaches < vNombreTaches; vTaches++) {
        //On parcourt chaque tache et on la stocke dans une variable temporaire
        sTache tacheCourante = prTabTache[vTaches];
        //la tache pour l'instant n'est pas placé
        bool TachePlace = false;

        // Verifie toutes les stations existantes pour placer la tâche
        for (int vNumeroStationExistantes = 0; vNumeroStationExistantes <= vIndexStation; vNumeroStationExistantes++) {
            //Contrainte de temps
            if (vTempsParStation[vNumeroStationExistantes] + tacheCourante.temps <= prTempsDeCycle) {
                // Ajoute la tâche à cette station

                //Stocke le nombre de taches de la station dans le premier élement de la station
                int vNombreTacheStation = tListePoste[vNumeroStationExistantes].cNombreTaches;

                //Realloue le tableau des taches de la station pour y accueilir uniquement les taches qui sont dedans
                tListePoste[vNumeroStationExistantes].taches = realloc(tListePoste[vNumeroStationExistantes].taches,(vNombreTacheStation + 1) * sizeof(int));

                //Ajoute la tache au vNombreTacheStation+1 ème élement du tableau
                tListePoste[vNumeroStationExistantes].taches[vNombreTacheStation] = tacheCourante.id;

                tListePoste[vNumeroStationExistantes].cNombreTaches++; // Mets à jour le nombre de tâches
                vTempsParStation[vNumeroStationExistantes] += tacheCourante.temps;//Met à jour le temps total de la station
                TachePlace = true;//La tache est placé
                break;
            }
        }

        // Si la tâche ne peut être placée dans aucune station existante, créer une nouvelle station
        // Créer une nouvelle station si nécessaire
        if (!TachePlace) {
            vIndexStation++;
            tListePoste[vIndexStation].id = vIndexStation;
            tListePoste[vIndexStation].taches = malloc(1 * sizeof(int));
            tListePoste[vIndexStation].taches[0] = tacheCourante.id;
            tListePoste[vIndexStation].cNombreTaches = 1;
            vTempsParStation[vIndexStation] = tacheCourante.temps;
        }
    }
    // Libérer la mémoire pour vTempsParStation
    free(vTempsParStation);

    // Affichage du nombre de stations avec les tâches réalisées à l'intérieur
    printf("Nombre de stations : %d\n", vIndexStation + 1);
    for (int i = 0; i <= vIndexStation; i++) {
        printf("Station %d : ", i);
        for (int j = 0; j < tListePoste[i].cNombreTaches; j++) { // Commencez à l'indice 0
            printf("%d ", tListePoste[i].taches[j]);
        }
        printf(" - Nombre total de taches dans la station: %d\n", tListePoste[i].cNombreTaches);
    }
    printf("\n");
    return tListePoste;
}
