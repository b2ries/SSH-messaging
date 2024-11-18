#ifndef SSH_AUTH_H
#define SSH_AUTH_H

// Déclaration de la fonction pour masquer la saisie du mot de passe
void masquerSaisie(char *motDePasse, int taille);

// Déclaration de la fonction pour vérifier la connexion SSH
int verifierConnexionSSH(const char *nomUtilisateur, const char *motDePasse);

// Déclaration de la fonction pour gérer la connexion SSH
void connexionSSH(const char *nomUtilisateur, const char *motDePasse, int tentative, ...);

#endif // SSH_AUTH_H