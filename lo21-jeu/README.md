# LO21 jeu


# A faire pour init le git 

Créer le dossier dans lequel mettre le projet 'dossier_choisi' ici puis

```
cd dossier_choisi
git init
git remote add origin https://gitlab.utc.fr/lo21-projet2/lo21-jeu.git
cd lo21-jeu # si besoin
git fetch origin

```
Créer une clé ssh dans profil-preferences-clé ssh pour lier l'ordi local avec le gitlab.
Pour avoir la clé à copier coller dans gitlab faire : 

```
ssh-keygen -t rsa -b 4096 -C "ton_email@example.com"
```

Faire entrée à chaque fois.
Ensuite

```
git bash # si sous windows
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_rsa 
cat ~/.ssh/id_rsa.pub | clip
```

Tout ce qui vient de s'afficher est copié et il faut la coller dans la case clé ssh de gitlab.
Pour vérifier que ça marche fait

```
git remote set-url origin git@gitlab.utc.fr:lo21-projet2/lo21-jeu.git
ssh -T git@gitlab.utc.fr
```
Puis 

```
git branch -M main
git push -uf origin main
```
Le système demande une authentification normalement.


# Commandes de base git

```
git init                   # Initialise un nouveau dépôt Git
git clone <URL>            # Clone un dépôt distant
git status                 # Affiche l'état des fichiers dans le dépôt
git add <fichier>          # Ajoute un fichier au suivi
git add .                  # Ajoute tous les fichiers au suivi
git commit -m "Message"    # Enregistre les modifications avec un message
git log                    # Affiche l'historique des commits
git checkout -b <branche>  # Crée et change de branche
git checkout <branche>     # Change de branche
git merge <branche>        # Fusionne une branche dans la branche courante
git push origin <branche>  # Envoie les commits locaux vers le dépôt distant
git pull origin <branche>  # Récupère les mises à jour du dépôt distant
```

Je conseille d'installer git gui pour éditer des commits et gitk pour voir l'état des branches.
Avec vs code ça se fait aussi en ajoutant l'extension git.

# Etapes pour récupérer et modifier du code

```
git checkout <ta_branche>
git pull origin master
git status # verifier l'état des fichiers
git add <fichier> # tu peux utiliser git gui à la place
git commit -m "nom de la modif : explications" # tu peux utiliser git gui à la place
git checkout master
git merge <ta_branche>
git push origin master
```
