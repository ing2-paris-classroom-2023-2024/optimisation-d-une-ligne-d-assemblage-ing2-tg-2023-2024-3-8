//
// Created by William on 12/11/2023.
//
#define ignorerPrecedence 0
#define ignorerTemps 0
#define ignorerCouleur 0

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "structs.h"
#include "ContraintePrecedence.h"
#include "Exclusionalexandre.h"
#include "ContrainteTemps.h"
#include "william.h"


/*int main(){
    int nbTaches;
    poste* postes;
    int idMaxPrec;
    int ** matricePrec;
    int temps;
    FILE *tempsExec = fopen("temps_cycle.txt", "r");

    if (tempsExec == NULL) {
        printf("Erreur lors de l'ouverture du fichier temps_cycle.txt\n");
        return 0;
    }
    fscanf(tempsExec,"%d",&temps);
    fclose(tempsExec);
    nbTaches=0;
    tache* taches= NULL;
    taches=wReadFileTimeOperation(&nbTaches);

    //printf("oui ?");
    matricePrec=creerPrec(&idMaxPrec);
    postes= exclusion(taches,nbTaches,temps,matricePrec,idMaxPrec,ignorerCouleur,ignorerTemps,ignorerPrecedence);
    //affichageExclusion();*
    printf("\033c");
    printf("normalement il n'y a plus rien");
    scanf("%d",&nbTaches);
    return 0;
}
*/
void acceuil(){
    printf("            ////////////////////////////////////////////////////////\n");
    printf("                _____ ______   _______   ________   ___  ___     \n"
           "               |\\   _ \\  _   \\|\\  ___ \\ |\\   ___  \\|\\  \\|\\  \\    \n"
           "               \\ \\  \\\\\\__\\ \\  \\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\\\\\  \\   \n"
           "                \\ \\  \\\\|__| \\  \\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\\\\\  \\  \n"
           "                 \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \n"
           "                  \\ \\__\\    \\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\\n"
           "                   \\|__|     \\|__|\\|_______|\\|__| \\|__|\\|_______|\n\n");
    printf("            ////////////////////////////////////////////////////////\n\n");
    printf("                              1: Contraintes D exclusion\n\n");
    printf("                              2: Contraintes de Precedence et Temps de Cycle\n\n");
    printf("                              3: Contraintes D exclusion et Temps de Cycle\n\n");
    printf("                              4: Les 3\n\n");
    printf("                              5: Autre\n\n");
    printf("                              6: Quitter\n\n");
}

// Ascii art de la contrainte d'exclusion
void AfficheEsclusion(){
    printf("            /////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("               _______      ___    ___ ________  ___       ___  ___  ________  ___  ________  ________      \n"
           "               |\\  ___ \\    |\\  \\  /  /|\\   ____\\|\\  \\     |\\  \\|\\  \\|\\   ____\\|\\  \\|\\   __  \\|\\   ___  \\    \n"
           "               \\ \\   __/|   \\ \\  \\/  / | \\  \\___|\\ \\  \\    \\ \\  \\\\\\  \\ \\  \\___|\\ \\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\   \n"
           "                \\ \\  \\_|/__  \\ \\    / / \\ \\  \\    \\ \\  \\    \\ \\  \\\\\\  \\ \\_____  \\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\  \n"
           "                 \\ \\  \\_|\\ \\  /     \\/   \\ \\  \\____\\ \\  \\____\\ \\  \\\\\\  \\|____|\\  \\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \n"
           "                  \\ \\_______\\/  /\\   \\    \\ \\_______\\ \\_______\\ \\_______\\____\\_\\  \\ \\__\\ \\_______\\ \\__\\\\ \\__\\\n"
           "                   \\|_______/__/ /\\ __\\    \\|_______|\\|_______|\\|_______|\\_________\\|__|\\|_______|\\|__| \\|__|\n"
           "                            |__|/ \\|__|                                 \\|_________|  \n\n");
    printf("            /////////////////////////////////////////////////////////////////////////////////////////\n\n");
}

// Ascii art de la contrainte de Precedence et de temps de cycle
void AffichePreceEtTpsC(){
    printf("            ////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("                ________  ________  _______           _______  _________        _________  ________  ________      \n"
           "                |\\   __  \\|\\   __  \\|\\  ___ \\         |\\  ___ \\|\\___   ___\\     |\\___   ___\\\\   __  \\|\\   ____\\     \n"
           "                 \\ \\  \\|\\  \\ \\  \\|\\  \\ \\   __/|        \\ \\   __/\\|___ \\  \\_|     \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\___|_    \n"
           "                  \\ \\   ____\\ \\   _  _\\ \\  \\_|/__       \\ \\  \\_|/__  \\ \\  \\           \\ \\  \\ \\ \\   ____\\ \\_____  \\   \n"
           "                   \\ \\  \\___|\\ \\  \\\\  \\\\ \\  \\_|\\ \\       \\ \\  \\_|\\ \\  \\ \\  \\           \\ \\  \\ \\ \\  \\___|\\|____|\\  \\  \n"
           "                    \\ \\__\\    \\ \\__\\\\ _\\\\ \\_______\\       \\ \\_______\\  \\ \\__\\           \\ \\__\\ \\ \\__\\     ____\\_\\  \\ \n"
           "                     \\|__|     \\|__|\\|__|\\|_______|        \\|_______|   \\|__|            \\|__|  \\|__|    |\\_________\\\n"
           "                                                                                                         \\|_________|");
    printf("                   ///////////////////////////////////////////////////////////////////////////////////////////////////\n\n");
}

// Ascii art de la contrainte d'exclusion et de temps de cycle
void AfficheExclusionEtTpsC(){
    printf("             ///////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("              _______      ___    ___ ________          _______  _________        _________  ________  ________      \n"
           "              |\\  ___ \\    |\\  \\  /  /|\\   ____\\        |\\  ___ \\|\\___   ___\\     |\\___   ___\\\\   __  \\|\\   ____\\     \n"
           "              \\ \\   __/|   \\ \\  \\/  / | \\  \\___|        \\ \\   __/\\|___ \\  \\_|     \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\___|_    \n"
           "               \\ \\  \\_|/__  \\ \\    / / \\ \\  \\            \\ \\  \\_|/__  \\ \\  \\           \\ \\  \\ \\ \\   ____\\ \\_____  \\   \n"
           "                \\ \\  \\_|\\ \\  /     \\/   \\ \\  \\____        \\ \\  \\_|\\ \\  \\ \\  \\           \\ \\  \\ \\ \\  \\___|\\|____|\\  \\  \n"
           "                 \\ \\_______\\/  /\\   \\    \\ \\_______\\       \\ \\_______\\  \\ \\__\\           \\ \\__\\ \\ \\__\\     ____\\_\\  \\ \n"
           "                  \\|_______/__/ /\\ __\\    \\|_______|        \\|_______|   \\|__|            \\|__|  \\|__|    |\\_________\\\n"
           "                           |__|/ \\|__|                                                                    \\|_________|");
    printf("                /////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n");
}

// Ascii art de l'heuristique
void AfficheLes3(){
    printf("                     ///////////////////////////////////////////////////////////////////////////////////\n");
    printf("                                    ___       _______   ________           ________     \n"
           "                                    |\\  \\     |\\  ___ \\ |\\   ____\\         |\\_____  \\    \n"
           "                                     \\ \\  \\    \\ \\   __/|\\ \\  \\___|_        \\|____|\\ /_   \n"
           "                                      \\ \\  \\    \\ \\  \\_|/_\\ \\_____  \\             \\|\\  \\  \n"
           "                                       \\ \\  \\____\\ \\  \\_|\\ \\|____|\\  \\           __\\_\\  \\ \n"
           "                                        \\ \\_______\\ \\_______\\____\\_\\  \\         |\\_______\\\n"
           "                                         \\|_______|\\|_______|\\_________\\        \\|_______|\n"
           "                                                            \\|_________|                 \n");
    printf("                      /////////////////////////////////////////////////////////////////////////////////////\n\n");
}

// Ascii art du message de fin
void AfficheFin(){
    printf("            ////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("                                                ________ ___  ________      \n"
           "                                                |\\  _____\\\\  \\|\\   ___  \\    \n"
           "                                                \\ \\  \\__/\\ \\  \\ \\  \\\\ \\  \\   \n"
           "                                                 \\ \\   __\\\\ \\  \\ \\  \\\\ \\  \\  \n"
           "                                                  \\ \\  \\_| \\ \\  \\ \\  \\\\ \\  \\ \n"
           "                                                   \\ \\__\\   \\ \\__\\ \\__\\\\ \\__\\\n"
           "                                                    \\|__|    \\|__|\\|__| \\|__|\n");
    printf("              ////////////////////////////////////////////////////////////////////////////////////////////\n\n");

}

// fonction principal
int main(){
    int nbTaches;
    poste* postes;
    int idMaxPrec;
    int ** matricePrec;
    int temps;
    FILE *tempsExec = fopen("temps_cycle.txt", "r");

    if (tempsExec == NULL) {
        printf("Erreur lors de l'ouverture du fichier temps_cycle.txt\n");
        return 0;
    }
    fscanf(tempsExec,"%d",&temps);
    fclose(tempsExec);
    nbTaches=0;
    tache* taches= NULL;
    taches=wReadFileTimeOperation(&nbTaches);

    //printf("oui ?");
    matricePrec=creerPrec(&idMaxPrec);

    char choix;
    char RetourMenu;
    do {
        //effaceScreen();
        acceuil();
        printf("Choisir l'option: \n\n");
        scanf(" %c",&choix);
        // choix des options parmi 6 options
        switch (choix) {
            case '1' :
                // Montre la contrainte d'exclusion
                AfficheEsclusion();
                // fonction exclusion
                postes= exclusion(taches,nbTaches,temps,matricePrec,idMaxPrec,0,1,13);
                getchar();
                fflush(stdin);
                break;
            case '2':
                // Montre la contrainte de precedence et de temps de cycle
                AffichePreceEtTpsC();
                // fonction precedence et temps de cycle
                postes= exclusion(taches,nbTaches,temps,matricePrec,idMaxPrec,1,0,0);
                getchar();
                fflush(stdin);
                break;
            case '3':
                // Montre la contrainte d'exclusion et de temps de cycle
                AfficheExclusionEtTpsC();
                // fonction Exclusion et temps de cycle
                postes= exclusion(taches,nbTaches,temps,matricePrec,idMaxPrec,0,0,1);
                //printf("\nNombre de stations final : %d\n\n",nbInFine);
                getchar();
                fflush(stdin);
                break;
            case '4':
                // Montre l'heuristique
                AfficheLes3();
                // fonction qui possède toute les contraintes
                postes= exclusion(taches,nbTaches,temps,matricePrec,idMaxPrec,0,0,0);
                getchar();
                fflush(stdin);
                break;
            case '5':
                postes= exclusion(taches,nbTaches,temps,matricePrec,idMaxPrec,ignorerCouleur,ignorerTemps,ignorerPrecedence);
                getchar();
                fflush(stdin);
            case '6':
                // Fin du programme
                AfficheFin();
                exit(EXIT_FAILURE);
            default:
                printf("Touche non valide\n");
                fflush(stdin);
        }

        // Permet de retourner au menu avec 0 ou o et termine le programme sinon
        printf("Retour au Menu ? (O/N): ");
        scanf(" %c",&RetourMenu);
        getchar();
        fflush(stdin);
    } while (RetourMenu == 'O' || RetourMenu == 'o');

    return 0;
}
