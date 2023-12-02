#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFSIZE 1096

//Question 2:

void exeCommande(char *buf, ssize_t commande_size);

int main(){
    char welcome[BUFSIZE]="enseah% fortune\n Today is what happened to yesterday.\n enseah" ; // création d'un tableau de caractère welcome avec le message de bienvenue
    char buf[BUFSIZE]; // déclaration d'un tableau de caractères pour stocker les commandes entrées par l'utilisateur.
    ssize_t commande_size; // variable pour stocker la taille de la commande lue par read

    write(STDOUT_FILENO,welcome,strlen(welcome));   // on utilise write pour afficher le message de bienvenue (welcome) sur la sortie standard

// on crée une boucle infinie pour simuler un prompt de shell continu.
    while(STDOUT_FILENO){   
        write(STDOUT_FILENO,"%",strlen("%")); // permet de retourner à la ligne suivante après l'exécution d’une commande.
        commande_size= read(STDIN_FILENO,buf,BUFSIZE); //on utilise la fonction read pour lire une commande depuis l'entrée standard
        exeCommande(buf,commande_size);// on excute la commande avec la foncton exeCommande
    }

    return 0;
}

void exeCommande(char *buf,ssize_t commande_size){ // fonction excution qui prend un tableau de caractères buf (la commande)et la taille de la commande commande_size comme paramètr

    int pid;
    int status;
    buf[commande_size - 1] = '\0'; // “enter” est pris en compte avec le read . Il faut donc le retirer pour ne pas fausser execlp.Pour cela n remplace ce terme par :\0


    pid=fork(); / On appelle la fonction système fork pour créer un nouveau processus. Le PID du processus fils est retourné dans le processus parent et 0 dans le processus fils.

        // condition pour le processus parent
    if (pid!= 0){  
        wait(&status); //on utilise la fonction wait pour attendre la fin du processus fils et récupérer son statut.
    }
    else{                                                                                      
        execlp(buf,buf,(char *)NULL); //On utilise la fonction execlp pour exécuter la commande spécifiée par buf. Si cela réussit, le processus fils se termine après l'exécution de la commande.
        exit(EXIT_FAILURE);

    }
}