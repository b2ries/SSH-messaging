#ifndef SSH_KEY_TREE_H
#define SSH_KEY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Définition de la structure d'un nœud d'arbre pour les clés SSH.
 * Chaque nœud contient une chaîne de caractères pour la clé SSH
 * et des pointeurs vers les nœuds gauche et droit.
 */
typedef struct SSHKeyNode {
    char* key;                // La clé SSH stockée dans le nœud
    struct SSHKeyNode* left;  // Pointeur vers le nœud gauche
    struct SSHKeyNode* right; // Pointeur vers le nœud droit
} SSHKeyNode;

/**
 * Fonction qui recherche un nœud avec une clé SSH donnée dans un arbre binaire.
 *
 * @param root Pointeur vers le nœud racine de l'arbre.
 * @param key La clé SSH à rechercher dans l'arbre.
 * @return Pointeur vers le nœud correspondant à la clé, ou NULL si la clé n'existe pas.
 */
SSHKeyNode* searchSSHKey(SSHKeyNode* root, const char* key);

/**
 * Fonction utilitaire pour créer un nouveau nœud avec une clé SSH.
 *
 * @param key La clé SSH à attribuer au nouveau nœud.
 * @return Pointeur vers le nouveau nœud créé.
 */
SSHKeyNode* createSSHKeyNode(const char* key);

#endif // SSH_KEY_TREE_H
