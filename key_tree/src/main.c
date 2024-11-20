#include "ssh_key_tree.h"

int main() {
    // Création d'un arbre binaire pour stocker les clés SSH
    SSHKeyNode* root = createSSHKeyNode("ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEAr...");
    root->left = createSSHKeyNode("ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEAr...");
    root->right = createSSHKeyNode("ssh-dss AAAAB3NzaC1kc3MAAACBAP...");

    // Recherche d'une clé SSH dans l'arbre
    const char* keyToFind = "ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEAr...";
    SSHKeyNode* foundNode = searchSSHKey(root, keyToFind);

    // Affichage du résultat de la recherche
    if (foundNode != NULL) {
        printf("Clé SSH trouvée: %s\n", foundNode->key);
    } else {
        printf("Clé SSH '%s' non trouvée dans l'arbre.\n", keyToFind);
    }

    // Libération de la mémoire (non inclus pour simplifier)

    return 0;
}
