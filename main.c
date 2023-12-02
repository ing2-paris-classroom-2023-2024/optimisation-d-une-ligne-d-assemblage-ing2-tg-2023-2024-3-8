//
// Created by William on 12/11/2023.
//

#include "ToolBoxWilliam.h"

sTache* wReadFileTimeOperation(int* prTempsDeCycle);
sPoste* wRepartitionStationTemps(sTache* prTabTache,int prTempsDeCycle);

int main(){
    sTache *tListeTache;
    int vTempsDeCycle=0;
    int *pTempsDeCycle=&vTempsDeCycle;
    tListeTache=wReadFileTimeOperation(pTempsDeCycle);
    wRepartitionStationTemps(tListeTache,vTempsDeCycle);
    return 0;
}

sTache * wReadFileTimeOperation(int* prTempsDeCycle) {

    //Declaration des variables
    FILE *fFile;
    int v;
    int vNombreLignes = 0;
    int v2 = '\0';



    //Ouverture du fichier
    fFile = fopen("operations.txt", "r");

    //Vérification de l'ouverture du fichier
    if (fFile == NULL) {
        printf("File reading error");
    }


    while ((v = fgetc(fFile)) != EOF) {
        if (v == '\n')
            vNombreLignes++;
        v2 = v;
    }

    /* Ici, v2 est égal au caractère juste avant le EOF. */
    if (v2 != '\n')
        vNombreLignes++; /* Dernière ligne non finie */
    // Utilisez fseek pour déplacer le curseur au début du fichier
    printf("Le nombre de lignes est de %d",vNombreLignes);
    fseek(fFile, 0, SEEK_SET);

    sTache *tListeTache = (sTache *)malloc((vNombreLignes+1) * sizeof(sTache));
    tListeTache[0].id=vNombreLignes;
    for (int i=1;i<vNombreLignes+1;i++){
        fscanf(fFile,"%d %f",&tListeTache[i].id,&tListeTache[i].temps);
    }
    fclose(fFile);

    fFile= fopen("temps_cycle.txt","r");
    if (fFile == NULL) {
        printf("File reading error");
    }
    fscanf(fFile,"%d",prTempsDeCycle);
    fclose(fFile);
    return tListeTache;
}

sPoste* wRepartitionStationTemps(sTache* prTabTache, int prTempsDeCycle) {
    // Déclaration des variables
    int vNombreTaches = prTabTache[0].id;
    sTache sTacheTemp;

    // Création de la liste des tâches que l'on modifiera dynamiquement
    sPoste *tListePoste = (sPoste *) malloc((vNombreTaches + 1) * sizeof(sPoste));

    for (int j = 0; j < vNombreTaches + 1; j++) {
        tListePoste[j].taches = (int *) malloc(sizeof(int));
        tListePoste[j].taches[0] = 0; // Initialisez la taille du tableau de tâches à 0
    }
    int vNombreStations = 0; // Nombre de stations actuelles
    float vTempsTotalStation = 0; // Temps total dans la station actuelle

    // Tri à bulles
    for (int i = 1; i <= vNombreTaches - 1; i++) {
        for (int j = 1; j <= vNombreTaches - i; j++) {
            if (prTabTache[j].temps < prTabTache[j+1].temps) {
                sTacheTemp = prTabTache[j];
                prTabTache[j] = prTabTache[j+1];
                prTabTache[j+1] = sTacheTemp;
            }
        }
    }
    for (int i = 1; i <= vNombreTaches; i++) {
        sTache tacheCourante = prTabTache[i];

        if (vTempsTotalStation + tacheCourante.temps <= 10) {
            // Ajoute l'ID de la tâche à la station actuelle
            int stationIndex = vNombreStations;
            int index = tListePoste[stationIndex].taches[0]; // Obtenir la taille actuelle
            tListePoste[stationIndex].taches[index + 1] = tacheCourante.id;
            tListePoste[stationIndex].taches[0] = index + 1; // Mettre à jour la taille
            vTempsTotalStation += tacheCourante.temps;
        } else {
            // Crée une nouvelle station
            vNombreStations++;
            tListePoste[vNombreStations].id = vNombreStations;
            // Alloue de l'espace pour le tableau des tâches de la nouvelle station
            tListePoste[vNombreStations].taches = (int*) malloc(sizeof(int));
            tListePoste[vNombreStations].taches[0] = 1; // La nouvelle station a 1 tâche
            tListePoste[vNombreStations].taches[1] = tacheCourante.id;
            vTempsTotalStation = tacheCourante.temps;
        }
    }

    // Affichage du nombre de stations avec les tâches réalisées à l'intérieur
    printf("Nombre de stations : %d\n", vNombreStations);
    for (int i = 0; i <= vNombreStations; i++) {
        printf("Station %d : ", i);
        for (int j = 1; j <= tListePoste[i].taches[0]; j++) {
            printf("%d ", tListePoste[i].taches[j]);
        }
        printf("\n");
    }
    return tListePoste;
}
