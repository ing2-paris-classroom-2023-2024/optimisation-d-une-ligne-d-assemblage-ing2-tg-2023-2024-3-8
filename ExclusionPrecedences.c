#include <stdlib.h>
#include <stdio.h>
#include "Exclusionalexandre2.h"
#include "Contrainteprecedences.h"

void ExclusionPrecedence(int** matricPrecedence,int** matriceExclusion,int nbOperations){
    for (int i = 0; i < nbOperations; i++) {
        for (int j = 0; j < nbOperations; j++) {
            if(matricPrecedence[i][j]){
                for (int k = 0; k < nbOperations; k++) {
                    if(k!=i && k!=j){
                        matriceExclusion[j][k]=1;
                        matriceExclusion[k][j]=1;
                    }
                }
            }
        }
    }
}

void afficherExclusionPrecedence(int** matrice,int nbOperations){
    for (int i = 0; i < nbOperations; i++) {
        for (int j = 0; j < nbOperations; j++) {
            printf("%d",matrice[i][j]);
        }
        printf("\n");
    }
}

int main(){
    const char* nomfichier ="precedences.txt";
    FILE* fichier= fopen(nomfichier,"r");
    if(fichier == NULL){
        printf("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int nb_operations =0;
    int source, final;

    // compte le nombre d'opérations en lisant le fichier
    while (fscanf(fichier,"%d %d", &source, &final)==2){
        if(source > nb_operations){
            nb_operations=source;
        }
        if(final > nb_operations){
            nb_operations=final;
        }
    }
    fclose(fichier);

    // Initialisation de la Matrice d'adjacence
    int** matriceAdjacence= MatriceAdjacence(nb_operations);

    // Remplissage de la Matrice
    remplirMatrice(nomfichier,matriceAdjacence);

    // Affichage de la Matrice
    for (int i = 0; i < nb_operations; i++) {
        for (int j = 0; j < nb_operations; j++) {
            printf("%d ", matriceAdjacence[i][j]);
        }
        printf("\n");
    }

    int** matricePrecedence= MatriceAdjacence(nb_operations);
    remplirMatrice("precedences.txt",matricePrecedence);

    char nom_fichier[100];
    printf("Saisissez le nom du fichier : \n");
    scanf("%s",nom_fichier);
    int** matriceExclusion= ContrainteExclusion(nom_fichier,&nb_operations);

    ExclusionPrecedence(matricePrecedence,matriceExclusion,nb_operations);

    afficherExclusionPrecedence(matriceExclusion,nb_operations);
    int couleur[nb_operations];
    welshPowell(matriceExclusion,nb_operations,couleur,nb_operations);

    printf("la coloration : \n");
    for (int i = 0; i < nb_operations; i++) {
        printf("Tache %d : station %d\n",i+1,couleur[i]);
    }

    // Libère la mémoire de la matrice
    libereMatrice(matricePrecedence,nb_operations);
    libereMatrice(matriceExclusion,nb_operations);
    return 0;
}


