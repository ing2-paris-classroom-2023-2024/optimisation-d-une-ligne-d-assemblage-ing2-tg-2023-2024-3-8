#define IgnorerCouleur 1

#include "ExclusionClem.h"
#include "stdio.h"
#include "stdlib.h"

int** ContrainteExclusions(char* nomFichier,int* ordremat){ //Algorithme qui lie le fichier de contrainte d'exclusions et crée un graphe associé
    FILE* fp= fopen(nomFichier,"r");
    if(!fp){
        printf("Probleme d ouverture du fichier\n");
    }
    int ordre=0,nb1,nb2;
    while(fscanf(fp,"%d %d\n",&nb1,&nb2)==2){ //Recherche du nombre de Taches Maximums et donc de l'ordre du graphe qu'on va créer
        //printf("op1 op2 : %d %d \n",nb1,nb2);
        if(nb2>ordre) {
            ordre = nb2;
        }
        if(nb1>ordre) {
            ordre = nb1;
        }
    }
    *ordremat=ordre+1;
    //printf("ordre: %d\n",ordre);

    ///Création d'une matrice d'adjacence selon l'ordre trouvé
    int** matrice;

    // Allocation dynamique pour les lignes
    matrice = (int**) malloc((ordre+1) * sizeof(int*));

    if (matrice == NULL) {
        printf("Erreur d'allocation pour les lignes de la matrice.\n");
        exit(EXIT_FAILURE);
    }

    // Allocation dynamique pour les colonnes de chaque ligne
    for (int i = 0; i < ordre+1; i++) {
        matrice[i] = (int*) calloc(ordre+1, sizeof(int));

        if (matrice[i] == NULL) {
            printf("Erreur d'allocation pour les colonnes de la matrice.\n");
            exit(EXIT_FAILURE);
        }
    }

    ///On rembobine le fichier au début pour remplir la matrice d'adjacence en fonction des contraintes d'exclusion
    rewind(fp);
    while(fscanf(fp,"%d %d\n",&nb1,&nb2)==2){
        matrice[nb1][nb2]=1;
        matrice[nb2][nb1]=1;
        //printf("op1 op2 : %d %d \n",nb1,nb2);

    }

    ///debug matrice
    int j,k;
    for(j=0;j<ordre+1;j++){
        for(k=0;k<ordre+1;k++){
            //printf("%d ",matrice[j][k]);
        }
        //printf("\n");
    }
    fclose(fp);

    return matrice;
}

////   COLORATION DU GRAPHE POUR TROUVER LE NOMBRE DE STATIONS DE TRAVAIL

// Fonction pour trouver la prochaine couleur disponible pour un sommet
int prochaineCouleurDisponibles(int sommet, int nombre_sommets,int* couleurs,int** matrice_adjacence) {
    int couleur_disponible = 0;

    // Parcourir les sommets adjacents et vérifier leurs couleurs
    for (int i = 0; i < nombre_sommets; ++i) {
        if (matrice_adjacence[sommet][i] && couleurs[i] != -1) {
            if (couleurs[i] == couleur_disponible) {
                // Cette couleur est déjà utilisée par un voisin, essayer la suivante
                couleur_disponible++;
                i = -1;  // Redémarrer la boucle pour revérifier avec la nouvelle couleur
            }
        }
    }

    return couleur_disponible;
}

// Algorithme de tri à bulle
void triBulles(int degres[], int sommets_ord[], int nombre_sommets) {
    for (int i = 0; i < nombre_sommets - 1; ++i) {
        for (int j = 0; j < nombre_sommets - i - 1; ++j) {
            if (degres[sommets_ord[j]] < degres[sommets_ord[j + 1]]) {
                // Échanger les positions
                int temp = sommets_ord[j];
                sommets_ord[j] = sommets_ord[j + 1];
                sommets_ord[j + 1] = temp;
            }
        }
    }
}

// Algorithme de coloration de Welsh-Powell
void welshPowells(int** matrice_adjacence, int nombre_sommets,int* couleurs,int ordre) {
    int degres[ordre];
    int sommets_ord[ordre];

    // Calculer les degrés des sommets
    for (int i = 0; i < nombre_sommets; ++i) {
        degres[i] = 0;
        couleurs[i] = -1;

        for (int j = 0; j < nombre_sommets; ++j) {
            degres[i] += matrice_adjacence[i][j];
        }

        sommets_ord[i] = i;  // Initialiser la liste des sommets
    }

    // Trier les sommets par degré décroissant (tri à bulle)
    triBulles(degres, sommets_ord, nombre_sommets);

    // Attribution des couleurs
    int sommet;
    for (int i = 0; i < nombre_sommets; ++i) {
        sommet = sommets_ord[i];
        if (couleurs[sommet] == -1) {
            couleurs[sommet] = 0;  // Utiliser la couleur 0 pour le premier sommet non coloré
            // Colorer les sommets non adjacents
            for (int j = 0; j < nombre_sommets; ++j) {
                if (!matrice_adjacence[sommet][j] && couleurs[j] == -1) {
                    couleurs[j] = prochaineCouleurDisponibles(j, nombre_sommets,couleurs,matrice_adjacence);
                }
            }
        }
    }
}



int* listeColl(int *j,int * couleur,int ignorerCol){
    int ordremat;
    int** matrice_adjacence;
    char nom_fichier[]="exclusions.txt";
    matrice_adjacence=ContrainteExclusions(nom_fichier,&ordremat);
    welshPowells(matrice_adjacence,ordremat,couleur,ordremat);
    ///Recherche du nombre de couleurs et donc du nombre de stations
    *j=couleur[0];
    for(int i=0;i<ordremat;++i){
        if(*j<couleur[i]){
            *j=couleur[i];
        }
    }
    *j=*j+1;
    //printf("%d %d\n",ordremat,*j);
    int a;
    for (int i = 0; i < ordremat; ++i) {
        if(ignorerCol) couleur[i]=0;
        else couleur[i]=(int)(couleur[i]);
        //printf("%d ",couleur[i]);
    }
    //printf("fin de fonction listeCol\n");
    return couleur;
}
///CREATION DES STATIONS
void affichageExclusions() {
    int ordremat;
    int** matrice_adjacence;
    char nom_fichier[100];
    printf("Saisissez le nom du fichier : \n");
    scanf("%s",nom_fichier);
    matrice_adjacence=ContrainteExclusions(nom_fichier,&ordremat);

    int couleur[ordremat];
    welshPowells(matrice_adjacence,ordremat,couleur,ordremat);

    ////Recherche du nombre de couleurs et donc du nombre de stations
    int i,j,k,l;
    j=couleur[0];
    for(i=0;i<ordremat;i++){
        if(j<couleur[i]){
            j=couleur[i];
        }
    }
    j++;
    for (i = 0; i < ordremat; ++i) {
        //printf("->%d ",couleur[i]);
    }
    /*printf("%d",j);
    ///Affichage liste de couleur
    for(i=0;i<ordremat;i++){
        printf("Couleur de %d : %d ",i,couleur[i]);
    }*/

    ///Creation de la solution
    t_ligne LigneAssemblage;
    LigneAssemblage.nombreDeStations=j;
    LigneAssemblage.WS= (t_station*) malloc(j*sizeof(t_station));
    for(i=0;i<j;i++){
        LigneAssemblage.WS[i].num=i;
        LigneAssemblage.WS[i].duree=0;
        LigneAssemblage.WS[i].nbTaches=0;
        for(k=1;k<ordremat;k++){
            if(couleur[k]==i){
                LigneAssemblage.WS[i].nbTaches++;
            }
        }
        LigneAssemblage.WS[i].taches= (int*)malloc((LigneAssemblage.WS[i].nbTaches)*sizeof(int));
        l=0;
        for(k=1;k<ordremat;k++){
            if(couleur[k]==i){
                LigneAssemblage.WS[i].taches[l]=k;
                l++;
            }
        }
    }
    ///////////////////AFFICHAGE DE LA SOLUTION
    printf("Le nombre de stations est : %d\n",j);
    for(i=0;i<j;i++){
        printf("Workstation %d : ",i);
        for(k=0;k<LigneAssemblage.WS[i].nbTaches;k++){
            printf("%d ",LigneAssemblage.WS[i].taches[k]);
        }
        printf("\n");
    }
}