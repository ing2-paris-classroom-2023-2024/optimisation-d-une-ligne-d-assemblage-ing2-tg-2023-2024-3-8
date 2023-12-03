#include "ExclusionPrecedences.h"



int** MatriceAdjacenceExPrece(int** matrice1,int** matrice2){

    int NombresSommets=0;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if(matrice1[i][j]==1 || matrice2[i][j]==1){
                NombresSommets++;
            }
        }
    }

    int** matriceExPrece=(int*) malloc(NombresSommets*sizeof (int ));
    for (int i = 0; i < NombresSommets; i++) {
        matriceExPrece[i]=(int *) calloc(NombresSommets,sizeof (int ));
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if(matrice1[i][j]==1){
                matriceExPrece[i][j]=1;
            }
            if(matrice2[i][j]==1){
                matriceExPrece[i][j]=1;
            }
        }
    }
    return matriceExPrece;
}

int main(){

    char nomFichierExclusion[]="exclusions.txt";
    char nomFichierPrecedences[]="precedences.txt";

    int** matrice1= ContrainteExclusion(nomFichierExclusion);
    int** matrice2= MatriceAdjacence(100);
    remplirMatrice(nomFichierPrecedences,matrice2);
    int** matriceExPrece= MatriceAdjacenceExPrece(matrice1,matrice2);
    int** couleurs=(int*) malloc(100* sizeof(int ));
    ColorationExPrece(matrice1,matrice2,couleurs);
    int nombrestations = NombreStations(couleurs);
    printf("Le nombres de stations est de : %d\n",nombrestations);
    AffichageExclusionPrecedences(couleurs);

    libereMatrice(matrice1,100);
    libereMatrice(matrice2,100);
    free(couleurs);

    return 0;
}


