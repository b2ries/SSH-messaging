#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "ssh_auth.h" 

#ifdef _WIN32
#include <conio.h> // Pour _getch() sous Windows
#else
#include <termios.h>
#include <unistd.h> // Pour la gestion de l'entrée sous Unix/Linux
#endif

#define MAX_ATTEMPTS 3 // Nombre maximum de tentatives de connexion
#define PASSWORD "WQmva54U7w9H4Gu9j" // Mot de passe correct (simulé)

// Fonction pour masquer la saisie du mot de passe
void masquerSaisie(char *motDePasse, int taille) {
#ifdef _WIN32
    for (int i = 0; i < taille; i++) {
        motDePasse[i] = _getch(); // Lire un caractère sans l'afficher
        if (motDePasse[i] == '\r') { // Si touche Entrée
            motDePasse[i] = '\0'; // Terminer la chaîne
            break;
        }
        printf("*"); // Afficher un astérisque pour chaque caractère
    }
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // Sauvegarder les anciennes attributs
    newt = oldt; // Copier les attributs
    newt.c_lflag &= ~(ICANON | ECHO); // Désactiver l'écho et le mode canonique
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Appliquer les nouveaux attributs

    for (int i = 0; i < taille; i++) {
        motDePasse[i] = getchar(); // Lire un caractère sans l'afficher
        if (motDePasse[i] == '\n') {
            motDePasse[i] = '\0'; // Terminer la chaîne
            break;
        }
        printf("*"); // Afficher un astérisque pour chaque caractère
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restaurer les anciens attributs
#endif
}

// Fonction fictive pour vérifier la connexion SSH
int verifierConnexionSSH(const char *nomUtilisateur, const char *motDePasse) {
    // Ici, vous devriez intégrer la logique d'authentification SSH appropriée.
    // Par exemple, avec libssh ou libssh2 pour un vrai système de connexion.
    // Cette fonction simule simplement la vérification du mot de passe.
    return strcmp(motDePasse, PASSWORD) == 0; // Renvoie vrai si le mot de passe est correct
}

// Fonction pour vérifier le mot de passe et afficher des messages
void connexionSSH(const char *nomUtilisateur, const char *motDePasse, int tentative, ...) {
    va_list args; // Déclaration d'une variable pour les arguments
    va_start(args, tentative); // Initialisation de la liste des arguments

    // Vérification du mot de passe
    if (verifierConnexionSSH(nomUtilisateur, motDePasse)) {
        printf("\nConnexion réussie pour %s !\n", nomUtilisateur);
    } else {
        // Récupération et affichage des messages supplémentaires
        printf("\nMot de passe incorrect pour %s. Tentative %d : ", nomUtilisateur, tentative);
        char *msg;
        while ((msg = va_arg(args, char*)) != NULL) {
            printf("%s ", msg);
        }
        printf("\n");
    }

    va_end(args); // Nettoyage de la liste des arguments
}

int main() {
    char nomUtilisateur[50]; // Tableau pour stocker le nom d'utilisateur
    char motDePasse[50]; // Tableau pour stocker le mot de passe entré
    int tentatives = 0; // Compteur de tentatives

    printf("Bienvenue dans le système de connexion SSH.\n");

    // Demande de saisie du nom d'utilisateur
    printf("Entrez votre nom d'utilisateur: ");
    scanf("%49s", nomUtilisateur); // Lire le nom d'utilisateur

    // Boucle pour gérer les tentatives de connexion
    while (tentatives < MAX_ATTEMPTS) {
        printf("Entrez votre mot de passe: ");
        masquerSaisie(motDePasse, sizeof(motDePasse)); // Lire le mot de passe en masquant l'entrée
        printf("\n"); // Sauter à la ligne après la saisie du mot de passe

        // Appel de la fonction de connexion avec le nom d'utilisateur, mot de passe et le nombre de tentatives
        connexionSSH(nomUtilisateur, motDePasse, tentatives + 1, "Veuillez réessayer.", "Tentatives restantes:", MAX_ATTEMPTS - tentatives - 1, NULL);

        // Sortir de la boucle si la connexion est réussie
        if (verifierConnexionSSH(nomUtilisateur, motDePasse)) {
            break; 
        }
        tentatives++;
    }

    if (tentatives == MAX_ATTEMPTS) {
        printf("Nombre maximum de tentatives atteint. Accès refusé.\n");
    }

    return 0;
}