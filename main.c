//
// Created by William on 12/11/2023.
//

#include "ToolBoxWilliam.h"

sTache* wReadFileTimeOperation();

int main(){
    sTache *tListeTache;
    tListeTache=wReadFileTimeOperation();


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

    sTache *tListeTache = (sTache *)malloc(vNombreLignes * sizeof(sTache));
    for (int i=0;i<vNombreLignes;i++){
        fscanf(fFile,"%d %f",&tListeTache[i].id,&tListeTache[i].temps);
    }

    return tListeTache;
}