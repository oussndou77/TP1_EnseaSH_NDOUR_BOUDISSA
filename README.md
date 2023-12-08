# TP1_EnseaSH_NDOUR_BOUDISSA
 Réaliser un micro shell, affichant les codes de sortie et les temps d’exécution des programmes lancés.

1/ Affichage d'un message d'accueil :

L'objectif de la première question est d'afficher un message d'accueil simple

2/ Exécution de la commande saisie

Pour toute cette partie et le suite la lecture et l'exécution des commandes se fait dans une boucle infinie while(1){ }.
Pour lire la commande saisie on utilise la ligne de commande suivante : 
read(0,buf, BUFSIZE); L’argument 0 correspond à STDIN_FILENO.
On veut exécuter les commandes de bases d’une console. 
En se basant sur le cours, on utilise execlp, il n’est donc pas nécessaire d’indiquer le path entier du fichier à exécuter.
Le caractère “enter” est pris en compte avec le read. Il faut donc le retirer pour ne pas fausser execlp.
Pour cela on remplace ce terme par “\0” qui se trouve à la fin de chaque chaîne de caractères.

3/Retour au prompt et sortie enseahh

Sortie avec exit : 
On compare le texte en entrée à la chaîne de caractères “exit” en utilisant la fonction strcmp qui renvoie 0 si les deux chaînes de caractères sont identiques
On ajoute l’exécution de la commande exit avant le pid = fork(), cela permet d'empêcher d’autre processus de se créer et d’être exécuté avant le “exit”.
Sortie avec <ctrl>+d 
<ctrl> + d envoie le message Bye Bye. Concrètement, il n’y a plus rien à lire et command_size est nul. Donc l’ajout de la condition “|| commande_size == 0” suffit à le faire fonctionner

4/ Affichage du code retour

5/Mesure du temps d'exécution de la commande

La différence entre le temps avant l'exécution et à la fin de l'exécution d’une commande nous donne le temps d'exécution (start et stop sont deux structures timespec).

6/ Exécution d’une commande complexe

On crée en premier une fonction qui va servir à séparer chacune des commandes dans le shell. L’objectif est de séparer une commande comme “ls -l” dans un tableau de char donc de récupérer “ls” et “-l” indépendamment en les séparant au niveau de l’espace.
Pour cela on utilise la fonction strtok.
Il ne faut pas oublier d’allouer la mémoire à notre tableau à chaque fois que l’on ajoute une valeur au tableau.
On modifie également la fonction exeCommande pour qu’elle puisse prendre en compte plusieurs commandes.
On commence par changer les arguments en entrée de la fonction pour permettre de récupérer un tableau de chaîne de caractère en entrée.
Dans la fonction main, on oublie pas de clear le buffer avant chaque exécution afin d’oublier les anciennes commandes. 
Puis on peut appliquer à notre commande la séparation avec separeCommande, puis l'exécution avec exeCommande. 

7/Gestion des redirections vers stdin et stdout avec ‘<’ et ‘>’

Pour gérer les redirections des commandes du shell vers un fichier ou d’un fichier vers le shell, il faut vérifier si les caractères ‘>’ ou ‘<’ se trouvent dans le tableau contenant tous les arguments de la commande. La vérification se fait juste avant l'exécution de la commande dans le processus fils. Pour cela on modifie notre fonction exeCommande 
