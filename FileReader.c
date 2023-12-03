//
// Created by Willyson on 02/12/2023.
//

#include "ToolBoxWilliam.h"

sTache * wReadFileTimeOperation(float* prTempsDeCycle,sParametre* prParametre) {

    //Declaration des variables
    FILE *fFile;
    int v;
    int vNombreLignes = 0;
    int v2 = '\0';



    //Ouverture du fichier
    fFile = fopen("../FichiersTxt/operations.txt", "r");

    //Vérification de l'ouverture du fichier
    if (fFile == NULL) {
        printf("Erreur dans l'ouverture d'operations.txt");
        exit(EXIT_FAILURE);
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
    //printf("Le nombre de lignes est de %d",vNombreLignes);
    prParametre->cNombreOperations=vNombreLignes;
    fseek(fFile, 0, SEEK_SET);

    sTache *tListeTache = (sTache *)malloc((vNombreLignes) * sizeof(sTache));
    for (int i=0;i<vNombreLignes;i++){
        fscanf(fFile,"%d %f",&tListeTache[i].id,&tListeTache[i].temps);
    }
    fclose(fFile);

    fFile= fopen("../FichiersTxt/temps_cycle.txt","r");
    if (fFile == NULL) {
        printf("Erreur dans l'ouverture de temps_cycle.txt");
        exit(EXIT_FAILURE);
    }
    fscanf(fFile,"%f",prTempsDeCycle);
    fclose(fFile);

    wReadFilePrecedentOperation(tListeTache,prParametre);
    return tListeTache;
}
//---------------------------------------------------------------------------------------------------------------------
void wReadFilePrecedentOperation(sTache *prListeTache,sParametre* prParametre) {
    FILE *fFile;
    int precedent, actuel;
    int vNombreOperations=prParametre->cNombreOperations;

    fFile = fopen("../FichiersTxt/precedences.txt", "r");
    if (fFile == NULL) {
        printf("Erreur dans l'ouverture du fichier precedence.txt");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vNombreOperations; i++) {
        prListeTache[i].tListeTachePrecedente = NULL;
        prListeTache[i].nbPredecesseur = 0;
    }

    while (fscanf(fFile, "%d %d", &precedent, &actuel) == 2) {
        for(int i=0;i<vNombreOperations;i++){
            if(prListeTache[i].id==actuel){
                prListeTache[i].nbPredecesseur++;
                int *temp = realloc(prListeTache[i].tListeTachePrecedente, prListeTache[i].nbPredecesseur * sizeof(int));
                if (temp == NULL) {
                    printf("Erreur d'allocation");
                    exit(EXIT_FAILURE);
                } else {
                    prListeTache[i].tListeTachePrecedente = temp;
                    prListeTache[i].tListeTachePrecedente[prListeTache[i].nbPredecesseur -1] = precedent;
                }
            }
        }
    }
    fclose(fFile);
}
