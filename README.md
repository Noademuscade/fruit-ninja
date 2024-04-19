# Mini-Projet LIFAMI

## VERNAY Noa 12300803

# Fruit Ninja
### Fruit Ninja est un jeu ou des fruits sont lancés et ou le joueur doit les couper pour augmenter son score. Si un fruit tombe mais n'est pas coupé, le joueur perd une vie . Au bout de 3 vies il a perdu.

###### A préciser que j'ai mis les images dans un dossier data/fruitninja pour corréler avec mon code.

# Explication du code

### Mon programme fonctionne autour de 3 structures principales: Vec2 qui implémente des vecteurs que les opérations entre eux, Fruit qui implémente les fruits avec leurs caractéristiques , leur position, leur vitesse et leur état et enfin World qui regroupe tous les fruits du jeu et les paramètres de mon jeu qui varie en fonction de l'évolution de celui-ci.
### J'ai implémenté la structure Fruit avec une procédure pour l'initialiser, l'afficher, le couper, l'ajouter au monde etc. J'ai aussi créer la procédure createFruitWave() qui permet de lancer les fruits par vague dans le World. 
### C'est avec la structure World que mon jeu sera affiché et mis à jour à chaque tour de boucle dans le main.La procédure drawWorld() affiche tous les fruits du monde sur la fenêtre avec le score et le nombre de vies restants. La procédure updateWorld() met à jour la position et la vitesse de chacun des fruits du monde. Si la souris passe sur un fruit entier, il est coupé et transformé en 2 moitiés de fruit qui seront supprimés après être sorti de la fenêtre.D'autres procédures comme startingMenu() et endWorld() affiche un menu de début et de fin de jeu.


### Compte-rendu par semaine

* Première semaine : Importation du TP Particule comme base . Création des premières procèdures pour la structure Fruit. J'ai aussi édité les images des fruits avec les fruits entiers et les fruits coupés.
* Deuxième semaine : J'ai implanté quasiment toutes les fonctions principales nécessaires au fonctionnement du jeu
Le jeu s'affiche , a un menu et on peut jouer (quelques détails à paufiner sur les trajectoires des fruits et leur vitesse)
La semaine prochaine, je compte finaliser toutes les fonctions principales et entamer l'ajout de mécanique en plus comme  de nouveaux fruits spéciaux etc
Je vous mets ci-joint un lien Github pour accéder au zip avec les images nécessaires (je n'utilise pas souvent github mais j'ai essayé pour prendre l'habitude)
https://github.com/Noademuscade/fruit-ninja*/

* Dernière semaine : J'ai fini le jeu en rajoutant un menu de début et de fin, j'ai aussi la grenade qui se transforme en 3 autres fruits quand on la coupe et le fruit "Lune" qui permet d'arrêter le temps pendant 2 secondes.J'ai aussi fixé de nombreux bugs comme en réglant la précision de découpe des fruits.




## Liens et documentations

Vous pouvez trouvez le GitHub du projet [ici](https://github.com/Noademuscade/fruit-ninja*/).
* [Wikipédia de Fruit-Ninja](https://fr.wikipedia.org/wiki/Fruit_Ninja)
* [Cours de LIFAMI pour TP Particule](http://alexandre.meyer.pages.univ-lyon1.fr/lifami/cours/)
