//
// Created by William on 12/11/2023.
//

#include "ToolBoxWilliam.h"

sTache* wReadFileTimeOperation();
sPoste* wRepartitionStationTemps(sTache* prTabTache);

int main(){
    sTache *tListeTache;
    tListeTache=wReadFileTimeOperation();
    wRepartitionStationTemps(tListeTache);
    return 0;
}

sTache * wReadFileTimeOperation() {

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

    return tListeTache;
}

sPoste* wRepartitionStationTemps(sTache* prTabTache) {
    //Déclaration des variables
    //Récupération du nombre de taches
    int vNombreTaches = prTabTache[0].id;

    //Création d'une tâche temporaire
    sTache sTacheTemp;
    //Création de la liste des tâches que l'on modifiera dynamiquement
    sPoste *tListePoste = (sPoste *) malloc((vNombreTaches + 1) * sizeof(sPoste));

    int vNombreStations = 0; // Nombre de stations actuelles
    float vTempsTotalStation = 0; // Temps total dans la station actuelle


    //Tri à bulles
    for (int i = 1; i <= vNombreTaches - 1; i++) {
        for (int j = 1; j <= vNombreTaches - i; j++) {
            if (prTabTache[j].temps < prTabTache[j+1].temps) {
                sTacheTemp = prTabTache[j];
                prTabTache[j] = prTabTache[j+1];
                prTabTache[j+1] = sTacheTemp;
            }
        }
    }

    return tListePoste;
}
