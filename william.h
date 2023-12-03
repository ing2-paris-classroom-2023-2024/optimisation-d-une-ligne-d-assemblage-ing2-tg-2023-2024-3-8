//
// Created by clement on 29/11/23.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_WILLIAM_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_WILLIAM_H
tache* test(){
    printf("oui");
    tache* tach;
    return (tach);
}

tache * wReadFileTimeOperation(int* nbtache) {


    //Declaration des variables
    FILE *fFile;
    int v;
    int vNombreLignes = 0;
    int v2 = '\0';



    //Ouverture du fichier
    fFile = fopen("operations.txt", "r");

    //Vérification de l'ouverture du fichier
    if (fFile == NULL) {
        printf("File reading error\n");
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
    //printf("Le nombre de lignes est de %d\n",vNombreLignes);
    *nbtache= vNombreLignes;
    fseek(fFile, 0, SEEK_SET);

    tache *tListeTache = malloc(vNombreLignes * sizeof(tache));

    /*tListeTache[0].id=vNombreLignes;*/
    for (int i=/*1*/0;i<vNombreLignes/*+1*/;i++){
        fscanf(fFile,"%d %f",&tListeTache[i].id,&tListeTache[i].temps);
    }

    return tListeTache;
}

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_TG_2023_2024_3_8_WILLIAM_H