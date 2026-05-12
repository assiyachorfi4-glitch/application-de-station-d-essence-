# Gestion Station Essence

Application Windows (Win32 API) écrite en C++ pour gérer la consommation de carburant de clients.  
Elle permet d’enregistrer un client (nom, prénom, kilométrage initial, volume d’essence) puis de calculer sa consommation moyenne après un nouveau passage à la station.
##  Fonctionnalités

- Saisie des informations client : **nom**, **prénom**, **kilométrage initial**, **essence prise (litres)**
- Enregistrement du client (stockage en mémoire)
- Saisie d’un nouveau passage : **nouveau kilométrage**, **nouvelle essence** (champs activés après enregistrement)
- Calcul automatique de la consommation moyenne depuis le dernier passage
- Affichage des informations client et du résultat dans la même fenêtre
- Interface simple avec champs et boutons
## Exécution
./StationEssence.exe
## Mode d’emploi
Enregistrer un client

Remplissez tous les champs : Nom, Prénom, KM Initial, Essence Initiale (L)

Cliquez sur Enregistrer Client

Ajouter un passage (après avoir roulé)

Entrez le Nouveau KM (ex: 12500)

Entrez la Nouvelle Essence (L) (ex: 38.5)

Cliquez sur Calculer Consommation

Résultat

La consommation s’affiche sous forme : Consommation: 7.23 L/100km
## Structure du projet
D:\station app\
│
├── main.cpp                # Code source complet
├── StationEssence.exe      # Exécutable (après compilation)
└── README.md               # Ce fichier
## Auteur
Assiya Chorfi
Étudiante en développement informatique
GitHub : assiyachorfi4-glitch
## 🔗 Lien du dépôt GitHub
https://github.com/assiyachorfi4-glitch/application-de-station-d-essence-

