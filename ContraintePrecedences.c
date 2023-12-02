#include <stdlib.h>
#include <stdio.h>

// Fonction qui créer la matrice d'adjacence
int** MatriceAdjacence(int nb_operations){
    int** matrice=(int**) malloc(nb_operations*sizeof (int*));
    // Allocation de la mémoire pour les lignes de la matrice d'adjacence
    for (int i = 0; i < nb_operations; i++) {
        matrice[i]=(int*) calloc(nb_operations, sizeof (int));
    }
    return matrice;
}

// Fonction qui libère la mémoire de la matrice
void libereMatrice(int** matrice, int nb_op){
    // libère les lignes
    for (int i = 0; i < nb_op; i++) {
        free(matrice[i]);
    }
    // libération de la mémoire du tableau de pointeur
    free(matrice);
}

// Fonction qui permet de Remplir notre matrice d'adjacence a partir d'un fichier
void remplirMatrice(const char* nomfichier,int** matrice){
    FILE* fichier= fopen(nomfichier,"r");
    if(fichier == NULL){
        printf("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    int source, final;

    // Remplissage de la matrice
    while (fscanf(fichier, "%d %d", &source, &final)==2){
        matrice[source-1][final-1]=1;
    }
    fclose(fichier);
}

// Fonction principal
int caPrecedence(){
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
    // Libère la mémoire de la matrice
    libereMatrice(matriceAdjacence,nb_operations);
    return 0;
}
