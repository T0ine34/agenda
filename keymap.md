# Utilisation d'un fichier en entrée

## Utilisation

pour démarrer le programme avec le jeu de touche, il suffit de passer le fichier en paramètre de la commande ```main```, ou rediriger l'entrée standard à partir du fichier.

Exemple avec le fichier ```jeu_de_touche.txt``` sous linux:
```bash
main.out jeu_de_touche.txt
```
ou
```bash
main.out < jeu_de_touche.txt
```

Une fois le programme arrivée à la fin du fichier, si il se se trouve sur un menu, l'utilisateur reprend le contrôle du programme, si le fichier amène le programme jusqu'à sa fermeture, le programme se ferme.

## Format du fichier
Le fichier doit être un fichier texte. Il doit contenir une touche par ligne. Les lignes vides sont ignorées. Les lignes commençant par un ```#``` sont ignorées.

L'extension du fichier n'a pas d'importance.

## Liste des touches
Voici la liste des touches supportées par le programme:

- les lettres majuscules et minuscules, sans accent
- les chiffres
- les chiffres du pavé numérique
- les touches de fonction
- les flèches du clavier
    - haut : ```ARROW_UP```
    - bas : ```ARROW_DOWN```
    - gauche : ```ARROW_LEFT```
    - droite : ```ARROW_RIGHT```
- les touches de contrôle
    - entrée : ```ENTER```
    - espace : ```SPACE```
    - tabulation : ```TAB```
    - retour arrière : ```BACKSPACE```
    - suppression : ```DELETE```
    - fin : ```END```
    - début : ```HOME```
    - page précédente : ```PAGE_UP```
    - page suivante : ```PAGE_DOWN```
    - insertion : ```INSERT```
    - échap : ```ESCAPE```
- les touches calcul du pavé numérique
    - addition : ```NUMPAD_PLUS```
    - soustraction : ```NUMPAD_MINUS```
    - multiplication : ```NUMPAD_MULTIPLY```
    - division : ```NUMPAD_DIVIDE```
    - virgule : ```NUMPAD_DOT```
    - entrée : ```NUMPAD_ENTER```

#### (des touches seront ajoutées au fur et à mesure du développement du projet)

## Exemple de fichier
Voici un exemple de fichier:
```txt
# Ceci est un exemple de fichier
# Il contient les touches du clavier
# Il est possible d'ajouter des commentaires
# Les lignes vides sont ignorées
# Les lignes commençant par un # sont ignorées

DOWN_ARROW
UP_ARROW
DOWN_ARROW
ENTER
ENTER
e
x
p
o
r
t
ENTER
SPACE
q
q
```	
> **A noter**: le fichier ne contient pas des caractères, mais des touches. lors d'une saisie de texte, il faut donc entrer un caractère par ligne.