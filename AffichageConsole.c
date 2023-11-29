#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

void color(int t, int f){
    HANDLE couleur = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(couleur,f*16+t);
}

void effaceScreen(){
    system("cls");
}

void acceuil(){
    effaceScreen();
    color(3,0);
    printf("            ////////////////////////////////////////////////////////\n");
    color(14,0);
    printf("                _____ ______   _______   ________   ___  ___     \n"
           "               |\\   _ \\  _   \\|\\  ___ \\ |\\   ___  \\|\\  \\|\\  \\    \n"
           "               \\ \\  \\\\\\__\\ \\  \\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\\\\\  \\   \n"
           "                \\ \\  \\\\|__| \\  \\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\\\\\  \\  \n"
           "                 \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \n"
           "                  \\ \\__\\    \\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\\n"
           "                   \\|__|     \\|__|\\|_______|\\|__| \\|__|\\|_______|\n\n");
    color(3,0);
    printf("            ////////////////////////////////////////////////////////\n\n");
    color(14,0);
    printf("                              1: Contraintes D exclusion\n\n");
    printf("                              2: Contraintes de Precedence et Temps de Cycle\n\n");
    printf("                              3: Contraintes D exclusion et Temps de Cycle\n\n");
    printf("                              4: Contraintes D exclusion et de Precedence\n\n");
    printf("                              5: Heuristique\n\n");
    printf("                              6: Quitter\n\n");
}

void AfficheEsclusion(){
    effaceScreen();
    color(3,0);
    printf("            /////////////////////////////////////////////////////////////////////////////////////////\n");
    color(14,0);
    printf("               _______      ___    ___ ________  ___       ___  ___  ________  ___  ________  ________      \n"
           "               |\\  ___ \\    |\\  \\  /  /|\\   ____\\|\\  \\     |\\  \\|\\  \\|\\   ____\\|\\  \\|\\   __  \\|\\   ___  \\    \n"
           "               \\ \\   __/|   \\ \\  \\/  / | \\  \\___|\\ \\  \\    \\ \\  \\\\\\  \\ \\  \\___|\\ \\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\   \n"
           "                \\ \\  \\_|/__  \\ \\    / / \\ \\  \\    \\ \\  \\    \\ \\  \\\\\\  \\ \\_____  \\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\  \n"
           "                 \\ \\  \\_|\\ \\  /     \\/   \\ \\  \\____\\ \\  \\____\\ \\  \\\\\\  \\|____|\\  \\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \n"
           "                  \\ \\_______\\/  /\\   \\    \\ \\_______\\ \\_______\\ \\_______\\____\\_\\  \\ \\__\\ \\_______\\ \\__\\\\ \\__\\\n"
           "                   \\|_______/__/ /\\ __\\    \\|_______|\\|_______|\\|_______|\\_________\\|__|\\|_______|\\|__| \\|__|\n"
           "                            |__|/ \\|__|                                 \\|_________|  \n\n");
    color(3,0);
    printf("            /////////////////////////////////////////////////////////////////////////////////////////\n\n");
}

int main(){
    acceuil();
    int choix;
    printf("Choisir l'option: ");
    choix =getch();
    switch (choix) {
        case '1' :
            AfficheEsclusion();
            // fonction exclusion
            break;
        default:
            effaceScreen();
            printf("Touche non valide");
    }

}
