#include "ssh_key_tree.h"

/**
 * Fonction qui recherche un nœud avec une clé SSH donnée dans un arbre binaire.
 *
 * @param root Pointeur vers le nœud racine de l'arbre.
 * @param key La clé SSH à rechercher dans l'arbre.
 * @return Pointeur vers le nœud correspondant à la clé, ou NULL si la clé n'existe pas.
 */
SSHKeyNode* searchSSHKey(SSHKeyNode* root, const char* key) {
    // Vérifie si le nœud actuel est NULL
    if (root == NULL) {
        return NULL; // La clé n'existe pas
    }

    // Vérifie si la clé actuelle correspond à la clé recherchée
    if (strcmp(root->key, key) == 0) {
        return root; // Retourne le nœud correspondant
    }

    // Recherche récursive dans le sous-arbre gauche
    SSHKeyNode* leftResult = searchSSHKey(root->left, key);
    if (leftResult != NULL) {
        return leftResult; // Retourne le résultat trouvé dans le sous-arbre gauche
    }

    // Recherche récursive dans le sous-arbre droit
    return searchSSHKey(root->right, key); // Retourne le résultat trouvé dans le sous-arbre droit
}

/**
 * Fonction utilitaire pour créer un nouveau nœud avec une clé SSH.
 *
 * @param key La clé SSH à attribuer au nouveau nœud.
 * @return Pointeur vers le nouveau nœud créé.
 */
SSHKeyNode* createSSHKeyNode(const char* key) {
    SSHKeyNode* newNode = (SSHKeyNode*)malloc(sizeof(SSHKeyNode)); // Alloue de la mémoire pour le nouveau nœud
    newNode->key = strdup(key); // Copie la chaîne de caractères de la clé
    newNode->left = NULL;       // Initialise le pointeur gauche à NULL
    newNode->right = NULL;      // Initialise le pointeur droit à NULL
    return newNode; // Retourne le nouveau nœud
}
