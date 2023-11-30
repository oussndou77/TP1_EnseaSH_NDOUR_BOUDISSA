#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1096

//Question 1 : Affichage d’un message d’accueil, suivi d’un prompt simple

int main(){
    char buf [BUFSIZE]="Bienvenue dans le shell ENSEA .\n Pour quitter, taper 'exit' .\n enseash % \n"; // Création d'un tableau de caractère , on rentre dedans le message qu'on veut afficher
    write(STDOUT_FILENO, buf, strlen(buf)); // On utilise la fonction write pour écrire le contenu du buffer sur la sortie standard (stdout) liée à l affichage de la console
    return 0; // Renvoie 0 en cas de résussite

}
