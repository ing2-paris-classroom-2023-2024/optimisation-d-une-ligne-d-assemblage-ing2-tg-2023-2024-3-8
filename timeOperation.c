#define DEB

#include "ToolBoxWilliam.h"

/**************************************************/
// Construit le liste des tâches de 1 à N
// stocke dans l'id de la tâche 0 qui n'existe pas le nombre de tâches
//
///////////////////////////////////////////////////
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
#ifdef DEBUG
    printf("[DEBUG]:Le nombre de lignes lues est de %d\n",vNombreLignes);
#endif
    fseek(fFile, 0, SEEK_SET);

    sTache *tListeTache = (sTache *)malloc((vNombreLignes+1) * sizeof(sTache));
    tListeTache[0].id=vNombreLignes;
    for (int i=1;i<vNombreLignes+1;i++){
        fscanf(fFile,"%d %f",&tListeTache[i].id,&tListeTache[i].temps);
    }

    return tListeTache;
}


sPoste* wRepartitionStationTempsCol(sTache* tabTache, int col, float Tc, int* nbSsStations) {
    // Déclaration des variables
    int vNombreTaches = tabTache[0].id;
    sTache sTacheTemp;

    // copie liste des taches
    sTache* prTabTache = (sTache*) malloc((vNombreTaches+1)*sizeof(sTache));
    for(int k=0; k <= vNombreTaches; k++){
        prTabTache[k].col = tabTache[k].col;
        prTabTache[k].id  = tabTache[k].id;
        prTabTache[k].temps = tabTache[k].temps;
    }

    // Création de la liste des postes que l'on modifiera dynamiquement
    sPoste *tListePoste = (sPoste *) malloc((vNombreTaches + 1) * sizeof(sPoste));

    for (int j = 0; j < vNombreTaches + 1; j++) {
        tListePoste[j].taches = (int *) malloc(sizeof(int));
        tListePoste[j].taches[0] = 0; // Initialisez la taille du tableau de tâches à 0
    }
    int vNombreStations = 1; // Nombre de stations actuelles
    float vTempsTotalStation = 0; // Temps total dans la station actuelle

    // Tri à bulles
    for (int i = 1; i <= vNombreTaches - 1; i++) {
        for (int j = 0; j <= vNombreTaches - i; j++) {
            if (prTabTache[j].temps < prTabTache[j+1].temps && prTabTache[j].col == col) {
                sTacheTemp = prTabTache[j];
                prTabTache[j] = prTabTache[j+1];
                prTabTache[j+1] = sTacheTemp;
            }
        }
    }

#ifdef DEBUG
    printf("\n[DEBUG]: station [%d] :",col);
    for(int i=1; i<= vNombreTaches ; i++)
        if (prTabTache[i].col == col)   
            printf("%d ",prTabTache[i].id);
        //else
            //printf("//%d ",prTabTache[i].id); 
    printf("\n");
#endif

    for (int i = 1; i <= vNombreTaches; i++) {
        sTache tacheCourante = prTabTache[i];
        while (tacheCourante.col != col){
            i++;
            if (i>vNombreTaches)
                break;
            tacheCourante = prTabTache[i];
        }
#ifdef DEBUG
        //printf("[DEBUG]:tacheCourante= %d,  \n",tacheCourante.id);
#endif

        if (i>vNombreTaches)
            break;

        if (vTempsTotalStation + tacheCourante.temps <= Tc) {
            // Ajoute l'ID de la tâche à la station actuelle
            int stationIndex = vNombreStations;
            int index = tListePoste[stationIndex].taches[0]; // Obtenir la taille actuelle
            tListePoste[stationIndex].taches[index + 1] = tacheCourante.id;
            //printf("////tacheCourante.id == %d\n", tacheCourante.id);
            tListePoste[stationIndex].taches[0] = index + 1; // Mettre à jour la taille
            vTempsTotalStation += tacheCourante.temps;
            tListePoste[stationIndex].tpsTot = vTempsTotalStation; // Mettre à jour le temps total

        } else {
            // Crée une nouvelle station
            vNombreStations++;
            tListePoste[vNombreStations].id = vNombreStations;
            // Alloue de l'espace pour le tableau des tâches de la nouvelle station
            tListePoste[vNombreStations].taches = (int*) malloc(sizeof(int));
            tListePoste[vNombreStations].taches[0] = 1; // La nouvelle station a 1 tâche
            tListePoste[vNombreStations].taches[1] = tacheCourante.id;
            vTempsTotalStation = tacheCourante.temps;
            tListePoste[vNombreStations].tpsTot = vTempsTotalStation; // Mettre à jour le temps total
        }
    }

    // Affichage du nombre de stations avec les tâches réalisées à l'intérieur
    printf("\nStation[%d] - Nombre de sous-stations : %d\n", col, vNombreStations);
    for (int i = 1; i <= vNombreStations; i++) {
        printf("Station %d-%d : Ts=%.2f : ", col, i, tListePoste[i].tpsTot);
        for (int j = 1; j <= tListePoste[i].taches[0]; j++) {
            printf("%d ", tListePoste[i].taches[j]);
        }
        printf("\n");
    }
    *nbSsStations = vNombreStations;
    free(prTabTache);

    return tListePoste;
}
