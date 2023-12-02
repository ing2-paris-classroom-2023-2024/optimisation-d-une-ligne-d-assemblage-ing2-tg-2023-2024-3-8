//
// Created by William on 12/11/2023.
//

#include "ToolBoxWilliam.h"

sTache* wReadFileTimeOperation(float* prTempsDeCycle);
sPoste* wRepartitionStationTemps(sTache* prTabTache,float prTempsDeCycle);

int main(){
    sTache *tListeTache;
    float vTempsDeCycle=0;
    float *pTempsDeCycle=&vTempsDeCycle;
    tListeTache=wReadFileTimeOperation(pTempsDeCycle);
    wRepartitionStationTemps(tListeTache,vTempsDeCycle);
    return 0;
}

sTache * wReadFileTimeOperation(float* prTempsDeCycle) {

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
    fscanf(fFile,"%f",prTempsDeCycle);
    fclose(fFile);
    return tListeTache;
}
sPoste* wRepartitionStationTemps(sTache* prTabTache, float prTempsDeCycle) {
//https://www.geeksforgeeks.org/program-best-fit-algorithm-memory-management/ UTilisation d'un algorithmme de type best fit
    //Nombre de taches
    int vNombreTaches = prTabTache[0].id;


    //Variables pour les stations
        //Création d'une liste de vNombreTaches stations
    sPoste *tListePoste = (sPoste *) malloc((vNombreTaches + 1) * sizeof(sPoste));
        //Index de la station (commence à -1 car le numéro de la station commence à 0)
    int vIndexStation = -1;
        //Tableau contenant les temps totaux de chaque station
    float *vTempsParStation = (float *) malloc((vNombreTaches + 1) * sizeof(float));

    //Variable temporaire pour le tri à bulles
    sTache sTacheTemp;

    for (int j = 0; j < vNombreTaches + 1; j++) {
        tListePoste[j].taches = (int *) malloc(sizeof(int));
        tListePoste[j].taches[0] = 0; // Initialise la taille du tableau de tâches à 0
        vTempsParStation[j] = 0; // Initialise le temps total de chaque station à 0
    }

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

    //Boucle principale
    for (int vTaches = 1; vTaches <= vNombreTaches; vTaches++) {
        //On parcourt chaque tache et on la stocke dans une variable temporaire
        sTache tacheCourante = prTabTache[vTaches];
        //la tache pour l'instant n'est pas placé
        bool TachePlace = false;

        // Veirifie toutes les stations existantes pour placer la tâche
        for (int vNumeroStationExistantes = 0; vNumeroStationExistantes <= vIndexStation; vNumeroStationExistantes++) {
            //Contrainte de temps
            if (vTempsParStation[vNumeroStationExistantes] + tacheCourante.temps <= prTempsDeCycle) {
                // Ajoute la tâche à cette station

                //Stocke le nombre de taches de la station dans le premier élement de la station
                int vNombreTacheStation = tListePoste[vNumeroStationExistantes].taches[0];

                //Realloue le tableau des taches de la station pour y accueilir uniquement les taches qui sont dedans
                tListePoste[vNumeroStationExistantes].taches = realloc(tListePoste[vNumeroStationExistantes].taches,
                                                                       (vNombreTacheStation + 2) * sizeof(int));

                //Ajoute la tache au vNombreTacheStation+1 ème élement du tableau
                tListePoste[vNumeroStationExistantes].taches[vNombreTacheStation + 1] = tacheCourante.id;

                tListePoste[vNumeroStationExistantes].taches[0] =
                        vNombreTacheStation + 1; // Mets à jour le nombre de tâches
                vTempsParStation[vNumeroStationExistantes] += tacheCourante.temps;//Met à jour le temps total de la station
                TachePlace = true;//La tache est placé
                break;
            }
        }

        // Si la tâche ne peut être placée dans aucune station existante, créer une nouvelle station
        if (!TachePlace) {
            vIndexStation++;
            tListePoste[vIndexStation].id = vIndexStation;
            tListePoste[vIndexStation].taches = (int *) realloc(tListePoste[vIndexStation].taches, 2 * sizeof(int));
            tListePoste[vIndexStation].taches[0] = 1; // Initialiser à 1 tâche
            tListePoste[vIndexStation].taches[1] = tacheCourante.id;
            vTempsParStation[vIndexStation] = tacheCourante.temps;
        }
    }
    //Utilisation d'une variable temporaire pour redimmensionner la liste des stations convenablement
    sPoste *temp = realloc(tListePoste, (vIndexStation + 1) * sizeof(sPoste));

    // Vérifiez si realloc a réussi
    if (temp == NULL) {
        free(tListePoste);
        return NULL;
    }
    tListePoste = temp;

    // Libérer la mémoire pour vTempsParStation
    free(vTempsParStation);

    // Affichage du nombre de stations avec les tâches réalisées à l'intérieur
    printf("Nombre de stations : %d\n", vIndexStation + 1);
    for (int i = 0; i <= vIndexStation; i++) {
        printf("Station %d : ", i);
        for (int j = 1; j <= tListePoste[i].taches[0]; j++) {
            printf("%d ", tListePoste[i].taches[j]);
        }
        printf("Nombre de taches dans la station: %d",tListePoste[i].taches[0]);
        printf("\n");
    }
    return tListePoste;
}
