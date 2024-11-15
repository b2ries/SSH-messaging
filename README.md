# SSH-messaging 📩 Système de Messagerie Sécurisée via SSH

## Description

Le **Système de Messagerie Sécurisée via SSH** est une application de messagerie qui utilise le chiffrement AES-256 pour garantir la confidentialité et la sécurité des messages échangés entre utilisateurs. Grâce à l'utilisation de SSH (Secure Shell), les messages sont chiffrés avant leur envoi, assurant ainsi une protection contre les interceptions et les écoutes.

### Fonctionnalités

- 🔒 **Chiffrement AES-256** : Tous les messages sont chiffrés avec l'algorithme AES-256, offrant un niveau de sécurité élevé.
- ⏳ **Autodestruction des Messages** : Les utilisateurs peuvent définir une durée après laquelle les messages s'auto-détruiront, garantissant qu'aucune trace ne reste après la lecture.
- 📁 **Envoi de Fichiers Chiffrés** : Possibilité d'envoyer des fichiers en toute sécurité, avec un chiffrement appliqué avant le transfert.
- 🖥️ **Interface Utilisateur Intuitive** : Une interface simple et conviviale pour faciliter l'envoi et la réception de messages.

## Technologies Utilisées

- 🐍 **Langage de Programmation** : Python
- 🔐 **Chiffrement** : AES-256 via la bibliothèque `openssl`
- 🌐 **Protocoles** : SSH pour la transmission sécurisée

## Installation

Pour installer l'application, suivez ces étapes :

1. Clonez le dépôt :
   ```bash
   git clone https://github.com/b2ries/SSH-messaging.git
   cd SSH-messaging
