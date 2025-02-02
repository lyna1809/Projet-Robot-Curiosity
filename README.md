# Projet Robot Curiosity

Ce projet implémente un système permettant de contrôler un robot sur un terrain donné à l'aide de commandes définies dans un programme-robot. L'interpréteur lit un programme et l'exécute sur un terrain, permettant au robot de se déplacer, rencontrer des obstacles, ou sortir du terrain. Plusieurs fonctionnalités sont implémentées pour tester et valider l'interprétation, la génération de terrains, ainsi que des tests de performance.

## Contenu du Projet

### 1. **Interpréteur de Programme-robot**
L'interpréteur est conçu pour prendre un fichier terrain et un fichier programme comme entrée, et effectuer les actions de manière simulée. Le programme-robot peut être testé sur plusieurs terrains et peut rencontrer différents événements (sortir du terrain, rencontrer un obstacle, etc.).

### 2. **Test de Fonctionnalité**
Un ensemble d'exercices permet de tester de manière intensive le paquetage `interprete` avec différents terrains et programmes-robots. Le but est de vérifier que l'interprète fonctionne correctement, notamment en prenant en compte divers événements qui peuvent survenir lors de l'exécution du programme-robot.

### 3. **Tests de Robustesse**
Des tests ont été ajoutés pour gérer les erreurs liées à la lecture et à l'exécution des programmes-robots. Ces tests permettent de vérifier si le système réagit correctement aux programmes erronés.

### 4. **Génération de Terrains**
Un générateur aléatoire de terrains a été ajouté pour créer des terrains avec des obstacles de densité spécifiée. Ce terrain est ensuite utilisé pour tester l'exécution du programme-robot.

### 5. **Test de Performance**
Le programme `curiosity-perf` permet de tester les performances du système en exécutant le programme-robot sur plusieurs terrains générés aléatoirement et en mesurant les résultats.

### 6. **Observateur**
Une fonctionnalité d'observateur a été ajoutée pour vérifier que le robot mesure correctement la case devant lui avant d'avancer.

---

Fonctionnement :

compilation : make
1. Lancer l'Interpréteur:   ./curiosity terrain.txt programme.txt
Où :
terrain.txt est un fichier décrivant la configuration du terrain.
programme.txt est un fichier contenant les instructions du programme-robot.

2. Exécuter les Tests:  ./curiosity-test test.txt
Le programme de test curiosity-test.c vous permet de tester des scénarios et vérifier si le comportement du robot est conforme à ce qui est attendu.

Le fichier test.txt doit être formaté de la manière suivante :

nom_terrain.txt
nom_programme.txt
pas_maximaux
événement_espéré
position_attendue
orientation_attendue

3. Générer des Terrains:  ./generation_aleatoire L H dObst
Où :
L et H sont la largeur et la hauteur du terrain.
dObst est la densité des obstacles (entre 0 et 1).


4. Tester la Performance: ./curiosity-perf programme.txt N L H d graine nb_step_max fichier_res
Où :
programme.txt est le fichier contenant le programme-robot à tester.
N est le nombre de terrains.
L et H sont les dimensions du terrain.
d est la densité des obstacles.
graine est la graine du générateur aléatoire.
nb_step_max est le nombre de pas maximum avant de stopper l'exécution.
fichier_res est le fichier où seront écrits les résultats.

Utilisez le programme curiosity-perf pour tester la performance de l'interpréteur sur plusieurs terrains générés aléatoirement.


5. Observateur : ./curiosity-obs terrain.txt programme.txt 
Si vous souhaitez vérifier que le robot mesure correctement la case devant lui avant de se déplacer, utilisez l'observateur.


