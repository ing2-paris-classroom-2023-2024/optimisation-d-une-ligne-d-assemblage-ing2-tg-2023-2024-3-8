#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Exclusion_et_Exclusion_TempsDeCycles.h"
#include "Les3.h"



// fonction qui change les couleurs de la console source: openclassroom
void couleur(int t, int f){
    HANDLE couleur = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(couleur,f*16+t);
}

// fonction qui permet d'effacer la console
void effaceScreen(){
    system("cls");
}

// Ascii art du menu et affichage des options
void acceuil(){
    couleur(3,0);
    printf("            ////////////////////////////////////////////////////////\n");
    couleur(14,0);
    printf("                _____ ______   _______   ________   ___  ___     \n"
           "               |\\   _ \\  _   \\|\\  ___ \\ |\\   ___  \\|\\  \\|\\  \\    \n"
           "               \\ \\  \\\\\\__\\ \\  \\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\\\\\  \\   \n"
           "                \\ \\  \\\\|__| \\  \\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\\\\\  \\  \n"
           "                 \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \n"
           "                  \\ \\__\\    \\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\\n"
           "                   \\|__|     \\|__|\\|_______|\\|__| \\|__|\\|_______|\n\n");
    couleur(3,0);
    printf("            ////////////////////////////////////////////////////////\n\n");
    couleur(14,0);
    printf("                              1: Contraintes D exclusion\n\n");
    printf("                              2: Contraintes de Precedence et Temps de Cycle\n\n");
    printf("                              3: Contraintes D exclusion et Temps de Cycle\n\n");
    printf("                              4: Les 3\n\n");
    printf("                              5: Quitter\n\n");
}

// Ascii art de la contrainte d'exclusion
void AfficheEsclusion(){
    couleur(3,0);
    printf("            /////////////////////////////////////////////////////////////////////////////////////////\n");
    couleur(14,0);
    printf("               _______      ___    ___ ________  ___       ___  ___  ________  ___  ________  ________      \n"
           "               |\\  ___ \\    |\\  \\  /  /|\\   ____\\|\\  \\     |\\  \\|\\  \\|\\   ____\\|\\  \\|\\   __  \\|\\   ___  \\    \n"
           "               \\ \\   __/|   \\ \\  \\/  / | \\  \\___|\\ \\  \\    \\ \\  \\\\\\  \\ \\  \\___|\\ \\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\   \n"
           "                \\ \\  \\_|/__  \\ \\    / / \\ \\  \\    \\ \\  \\    \\ \\  \\\\\\  \\ \\_____  \\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\  \n"
           "                 \\ \\  \\_|\\ \\  /     \\/   \\ \\  \\____\\ \\  \\____\\ \\  \\\\\\  \\|____|\\  \\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \n"
           "                  \\ \\_______\\/  /\\   \\    \\ \\_______\\ \\_______\\ \\_______\\____\\_\\  \\ \\__\\ \\_______\\ \\__\\\\ \\__\\\n"
           "                   \\|_______/__/ /\\ __\\    \\|_______|\\|_______|\\|_______|\\_________\\|__|\\|_______|\\|__| \\|__|\n"
           "                            |__|/ \\|__|                                 \\|_________|  \n\n");
    couleur(3,0);
    printf("            /////////////////////////////////////////////////////////////////////////////////////////\n\n");
}

// Ascii art de la contrainte de Precedence et de temps de cycle
void AffichePreceEtTpsC(){
    couleur(3,0);
    printf("            ////////////////////////////////////////////////////////////////////////////////////////\n");
    couleur(14,0);
    printf("                ________  ________  _______           _______  _________        _________  ________  ________      \n"
           "                |\\   __  \\|\\   __  \\|\\  ___ \\         |\\  ___ \\|\\___   ___\\     |\\___   ___\\\\   __  \\|\\   ____\\     \n"
           "                 \\ \\  \\|\\  \\ \\  \\|\\  \\ \\   __/|        \\ \\   __/\\|___ \\  \\_|     \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\___|_    \n"
           "                  \\ \\   ____\\ \\   _  _\\ \\  \\_|/__       \\ \\  \\_|/__  \\ \\  \\           \\ \\  \\ \\ \\   ____\\ \\_____  \\   \n"
           "                   \\ \\  \\___|\\ \\  \\\\  \\\\ \\  \\_|\\ \\       \\ \\  \\_|\\ \\  \\ \\  \\           \\ \\  \\ \\ \\  \\___|\\|____|\\  \\  \n"
           "                    \\ \\__\\    \\ \\__\\\\ _\\\\ \\_______\\       \\ \\_______\\  \\ \\__\\           \\ \\__\\ \\ \\__\\     ____\\_\\  \\ \n"
           "                     \\|__|     \\|__|\\|__|\\|_______|        \\|_______|   \\|__|            \\|__|  \\|__|    |\\_________\\\n"
           "                                                                                                         \\|_________|");
    couleur(3,0);
    printf("                ///////////////////////////////////////////////////////////////////////////////////////////////////\n\n");
}

// Ascii art de la contrainte d'exclusion et de temps de cycle
void AfficheExclusionEtTpsC(){
    couleur(3,0);
    printf("             ///////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
    couleur(14,0);
    printf("              _______      ___    ___ ________          _______  _________        _________  ________  ________      \n"
           "              |\\  ___ \\    |\\  \\  /  /|\\   ____\\        |\\  ___ \\|\\___   ___\\     |\\___   ___\\\\   __  \\|\\   ____\\     \n"
           "              \\ \\   __/|   \\ \\  \\/  / | \\  \\___|        \\ \\   __/\\|___ \\  \\_|     \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\___|_    \n"
           "               \\ \\  \\_|/__  \\ \\    / / \\ \\  \\            \\ \\  \\_|/__  \\ \\  \\           \\ \\  \\ \\ \\   ____\\ \\_____  \\   \n"
           "                \\ \\  \\_|\\ \\  /     \\/   \\ \\  \\____        \\ \\  \\_|\\ \\  \\ \\  \\           \\ \\  \\ \\ \\  \\___|\\|____|\\  \\  \n"
           "                 \\ \\_______\\/  /\\   \\    \\ \\_______\\       \\ \\_______\\  \\ \\__\\           \\ \\__\\ \\ \\__\\     ____\\_\\  \\ \n"
           "                  \\|_______/__/ /\\ __\\    \\|_______|        \\|_______|   \\|__|            \\|__|  \\|__|    |\\_________\\\n"
           "                           |__|/ \\|__|                                                                    \\|_________|");
    couleur(3,0);
    printf("                /////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n");
}

// Ascii art de l'heuristique
void AfficheLes3(){
    couleur(3,0);
    printf("                     ///////////////////////////////////////////////////////////////////////////////////\n");
    couleur(14,0);
    printf("                                    ___       _______   ________           ________     \n"
           "                                    |\\  \\     |\\  ___ \\ |\\   ____\\         |\\_____  \\    \n"
           "                                     \\ \\  \\    \\ \\   __/|\\ \\  \\___|_        \\|____|\\ /_   \n"
           "                                      \\ \\  \\    \\ \\  \\_|/_\\ \\_____  \\             \\|\\  \\  \n"
           "                                       \\ \\  \\____\\ \\  \\_|\\ \\|____|\\  \\           __\\_\\  \\ \n"
           "                                        \\ \\_______\\ \\_______\\____\\_\\  \\         |\\_______\\\n"
           "                                         \\|_______|\\|_______|\\_________\\        \\|_______|\n"
           "                                                            \\|_________|                 \n");
    couleur(3,0);
    printf("                      /////////////////////////////////////////////////////////////////////////////////////\n\n");
}

// Ascii art du message de fin
void AfficheFin(){
    couleur(3,0);
    printf("            ////////////////////////////////////////////////////////////////////////////////////////\n");
    couleur(14,0);
    printf("                                                ________ ___  ________      \n"
           "                                                |\\  _____\\\\  \\|\\   ___  \\    \n"
           "                                                \\ \\  \\__/\\ \\  \\ \\  \\\\ \\  \\   \n"
           "                                                 \\ \\   __\\\\ \\  \\ \\  \\\\ \\  \\  \n"
           "                                                  \\ \\  \\_| \\ \\  \\ \\  \\\\ \\  \\ \n"
           "                                                   \\ \\__\\   \\ \\__\\ \\__\\\\ \\__\\\n"
           "                                                    \\|__|    \\|__|\\|__| \\|__|\n");
    couleur(3,0);
    printf("              ////////////////////////////////////////////////////////////////////////////////////////////\n\n");

}

// fonction principal
int main(){
    char choix;
    char RetourMenu;
    do {
        effaceScreen();
        acceuil();
        printf("Choisir l'option: \n\n");
        scanf(" %c",&choix);
        // choix des options parmi 6 options
        switch (choix) {
            case '1' :
                // Montre la contrainte d'exclusion
                AfficheEsclusion();
                // fonction exclusion
                affichageExclusion();
                getchar();
                fflush(stdin);
                break;
            case '2':
                // Montre la contrainte de precedence et de temps de cycle
                AffichePreceEtTpsC();
                // fonction precedence et temps de cycle
                getchar();
                fflush(stdin);
                break;
            case '3':
                // Montre la contrainte d'exclusion et de temps de cycle
                AfficheExclusionEtTpsC();
                // fonction Exclusion et temps de cycle
                exclusionEtTempsCycle();
                getchar();
                fflush(stdin);
                break;
            case '4':
                // Montre l'heuristique
                AfficheLes3();
                // fonction qui possède toute les contraintes
                Les3();
                getchar();
                fflush(stdin);
                break;
            case '5':
                // Fin du programme
                AfficheFin();
                // pause de 3 secondes pour laisser l'affichage de la fin
                Sleep(3000);
                exit(EXIT_FAILURE);
            default:
                printf("Touche non valide\n");
        }

        couleur(12,0);
        // Permet de retourner au menu avec 0 ou o et termine le programme sinon
        printf("Retour au Menu ? (O/N): ");
        scanf(" %c",&RetourMenu);
    } while (RetourMenu == 'O' || RetourMenu == 'o');

    return 0;
}
