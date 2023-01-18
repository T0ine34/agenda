# Le projet Agenda

### Auteur: [Antoine Buirey](https://github.com/T0ine34)

---

## Description

Ce projet est un agenda. Il à été réalisé dans le cadre de mon BUT Informatique. Il correspond à la SAE 1.01, dénommé 'Implémentation d'un besoin client'.

## Installation
il suffit de lancer la commande ```make``` pour compiler le projet. Ensuite, il suffit de lancer le programme avec la commande ```main```.

## Utilisation
Le programme se veut simple d'utilisation. Lors du démarrage, un menu s'affiche. il est alors possible naviguer avec les flèches du clavier. Pour valider une action, il suffit d'appuyer sur la touche entrée.

> **Attention**: Sous linux, il est nécessaire d'appuyer deux fois sur la touche échap pour quitter la fenêtre courante. Sous windows, il suffit d'appuyer une seule fois.

Il est également possible d'utiliser un fichier texte contenant les touches sur lesquelles appuyer. Pour plus d'informations, voir [keymap.md](keymap.md).
> **Attention**: rediriger le flux d'entrée à partir du fichier ne marchera pas et peut provoquer des actions inattendues.

## Fonctionnalités
Il permet de gérer plusieurs agenda, c'est à dire ajouter des événements, les supprimer, les afficher, les exporter sous forme d'une page HTML.
Il est également possible de créer des agenda ou les supprimer.


## possible améliorations
- permettre de créer des événements récurrents
- créer un système de rappel (par sms, notification, ...)
- ajouter un système de synchronisation avec google calendar
- permettre de transférer des événements d'un agenda à un autre
- modifier les évènements ainsi que les nom et description des agendas
- modifier l'export en HTML pour qu'il soit affiché sous forme de calendrier, et non plus sous forme de liste