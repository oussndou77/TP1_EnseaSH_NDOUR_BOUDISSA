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
