//
// Created by Willyson on 02/12/2023.
//

#include "ToolBoxWilliam.h"

sTache * wReadFileTimeOperation(float* prTempsDeCycle) {

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

    fFile= fopen("../FichiersTxt/temps_cycle.txt","r");
    if (fFile == NULL) {
        printf("Erreur dans l'ouverture de temps_cycle.txt");
    }
    fscanf(fFile,"%f",prTempsDeCycle);
    fclose(fFile);
    return tListeTache;
}