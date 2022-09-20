# AccordinaMIDI

## Création d’un accordéon électronique.

## Introduction

Musicien pratiquant les musiques traditionnelles du centre France et d’Irlande, Je pratique le concertina depuis dix ans dans diverses formations ; Esling, Berny Trad School, Full4.
Ayant étudié dans le domaine de l’informatique je profite de ma dernière année d’étude pour jeter les bases d’un nouveau projet. Concevoir un concertina électronique me permettant de jouer au casque et d’explorer de nouvelles sonorités.

## Le concertina
<img src="https://user-images.githubusercontent.com/7162775/191326556-f5f79142-1c78-4a50-a57f-302a2880c0e2.jpg"  width="300">

Le concertina est un instrument de musique à vent et à anches libres, comme l’accordéon. Il à été inventé en 1829 par Sir Charles Wheatstone.
Souvent associé aux clowns et aux pirates. Il est pratiqué principalement en musique irlandaise et en musique folk anglaise.
Cet instrument fonctionne comme un accordéon. Nous parlerons ici principalement du concertina dit « Anglo ». Sur cet instrument Les notes sont réparties des deux côtés de l’instrument. Notes graves à gauche et notes aiguës à droite.
L’instrument est Bi-sonore : Appuyer ou tirer sur le soufflet ne produit généralement pas la même note
Voici un exemple d’un clavier classique a 30 touches.

## A Propos des Arduino.
Les boutons : le principe du bouton en électronique est de laisser passer le courant lorsque la touche est appuyée.
Pour lire un bouton avec un Arduino la première possibilité est de brancher une des bornes du bouton sur une Entrée de l’Arduino et l’autre à la masse.
Une lecture de l’état de l’entrée et on consulte l’état du bouton.

## Matrices de boutons
 Une technique communément utilisée notamment dans les claviers consiste à fabriquer une matrice.
Cette technique permet avec 8 entrées (ligne 1 à 4 et colonne 1 à 4) d’utiliser 16 boutons.
Si le courant passe entre ligne 1 et colonne 2 alors c’est le bouton 2 qui est appuyé.
Cette technique nous permettrait d’utiliser peu d’entrée/sortie sur l’Arduino.

Cependant essayez d’appuyer sur AZERTY en même temps sur votre clavier.
J’obtiens : Azerererererererererererererer


Les matrices ne permettent donc pas de faire des accords a 3, 4 sons. L’objectif est de rendre l’instrument aussi proche d’un véritable concertina cette méthode n’est donc pas envisageable.
Maintenant que nous avons évoqué les matrices et que nous avons vu pourquoi nous ne pourrons pas nous en servir nous allons consacrer une entrée/sortie par bouton.
Ce point peut paraitre anecdotique mais il dictera plusieurs choix de conceptions plus tard.

# Premier prototype V0.
<img src="https://user-images.githubusercontent.com/7162775/191326176-e2973c29-57a8-48b5-a389-e7ffbf34c2ea.jpg"  width="300">


Rapidement il m’est venu à l’idée de fabriquer deux claviers de 15 touches correspondant a chacun des côtés de l’instrument. Les Arduino classiques ont en général plus de 15 entrées (mais pas beaucoup plus)

Ce premier projet exploratoire à été réalisé avec des boutons trouvés dans un magasin d’électronique.
Un Arduino est placé dans chaque boitier. Le code a l’intérieur est globalement le même. Seul le tableau contenant les notes jouer va changer de l’un a l’autre.

## Gestion du soufflet :
Le soufflet n’est pas présent sur cet instrument la question est donc comment rendre le pousser/tirer fondement du son de l’instrument et de ces mécaniques de jeu ?
Ce premier prototype n’ayant pas de soufflet j’ai décidé d’utiliser un bouton (le bouton de pédale d’effet sur la photo)
L’instrument est considéré dans l’état tiré quand on le bouton n’est pas appuyé et comme poussé quand le bouton est pressé.
Bien que contre intuitive dans un premier temps cette méthode permet de simuler à peu près le fonctionnement de l’instrument. Manque encore l’intensité de pression exercer qui fait varier le volume, élément faisant partie intégrante du jeu de l’instrument.
Encore un peu d’électronique et d’informatique.

Maintenant que nous avons notre clavier et notre mécanique de soufflet deux problèmes se posent.
 - Comment mutualiser le soufflet pour les deux mains ?
 - Comment sortir du son ?
La première est plutôt vite vue : on branche un seul bouton aux deux Arduino. Cependant ce n’est pas sans conséquences on aura forcément un fil entre les deux boitiers. Et nous verrons que le même problème se reposera plus loin.

# Le son !

Toute une affaire. Deux options s’offrent à chaque bidouilleur débutant qui souhaite faire de la musique avec un Arduino ou tout autre projet d’électronique.
On peut faire de la synthèse sonore ou utiliser le protocole MIDI.

## Le MIDI :
Musical Instrument Digital Interface est un protocole permettant à n’importe quel objet l’implémentant de communiquer avec un logiciel de Musique assistée par ordinateur. C’est un exemple un peu restrictif du protocole mais c’est celui que nous explorerons
Chaque note d’un clavier de piano à un numéro attribué. On peut envoyer des messages comme noteOn(x), noteOff(x)
	L’avantage de cette méthode c’est que même sans être expert en musique électronique elle permet d’utiliser des sons amusants et d’explorer un petit peu Abletone et autre...
En pratique sur les Arduino (sauf certains modèles) l’affaire est un peu compliquée en termes d’informatique et nécessite l’utilisation de logiciels tiers.
En général un Arduino communique avec l’ordinateur via le port Série. Pour cette première version voici le schéma logiciel utilisé.
Le logiciel Hairless MIDI Serial permet de transformer le port série en port MIDI
LOOP MIDI est permet de simuler un port MIDI physique et renvoie les infos au logiciel de MAO

# La synthèse sonore :

Le son est une onde, l’idée de la synthèse sonore est de générer un signal via une sortie analogique de l’Arduino (Les sorties Analogiques peuvent prendre des valeurs autre que 0 et 1)
Cette solution a été la première retenue par sa simplicité (apparente).
L’utilisation de Tone une librairie fournie avec Arduino est relativement simple.
Tone(pinSortie, fréquence, durée);


Cependant le rendu sonore de la librairie Tone n’était convaincant et cette solution a été abandonné au profit du MIDI (du moins jusqu’à la version 3 ou 4 de l’instrument)

Retour d’expérience sur le premier prototype :
 - Les boutons achetés dans ma boutique du coin sont nuls, réagissent mal quand ils le font.
 - On valide le bouton pour le pousser dans un premier temps.
 - Le MIDI fonctionne bien et permet de débugger grâce à Hairless MIDI serial.
Les boutons sont le principal problème après quelque recherche je pense avoir trouvé la solution idéale.

# Clavier mécanique
Depuis le début de mes recherches je compare ce que je fais à un clavier d’ordinateur.
Tant dans le fonctionnement que dans la disposition des touches il y a beaucoup de similitudes.
Je me souviens d’un projet réalisé par Emmanuel Delahaye un bricoleur d’accordéons en tout genre. Il avait fait une sorte d’accordéon avec deux claviers une glissière de tiroir et une souris. Ce projet m’avait fasciné quand je l’avais découvert dans un magazine. C’est surement de la que me viens cette envie de créer ma propre version de l’accordéon MIDI.

Pour revenir à nos claviers j’ai découvert assez rapidement les switch Cherry MX. Présent dans la plupart des claviers mécanique de Gamer et de passionnées de clavier.

Ces switch ont de nombreux avantages en plus d’être qualitatifs, il en existe de nombreuses versions correspondant à tous les types de frappes. Mais par-dessus tout il possède une communauté immense de passionnés. Il existe de nombreuses ressources en ligne pour créer sa propre disposition de touche, des tutoriaux pour créer des circuits imprimés de clavier etc...

# Prototype V1
<img src="https://user-images.githubusercontent.com/7162775/191326235-0a6767f2-51fe-467a-820e-90c038d8644c.jpg"  width="300">
<img src="https://user-images.githubusercontent.com/7162775/191326318-fad7a10e-a8c3-42e2-91ae-e60414544b5b.jpg"  width="300">

 J’ai donc créé une nouvelle version avec des switch mécanique (en gardant la structure de V0). Grace a ce site http://www.keyboard-layout-editor.com/#/ j’ai pu créer la disposition de clavier voulu. Un ami m’a gentiment découpé des plaques en inox de la bonne épaisseur et le tour était joué. Enfin pas exactement, un collègue électronicien a fait les circuits tandis qu’un autre collègue imprimais les boutons orange qu’on voit sur la photo.




## Retour d’expérience sur le deuxième prototype :
⦁ Les boutons sont un succès, bien mieux que les anciens.
⦁ Le MIDI toujours cool et bien plus, le jeu devient presque agréable.
⦁ Quelque latence (pas encore de carte son, et la couche logiciel doit ajouter un peu de latence)
⦁ Pas d’intensité de jeu.

# Prototype V2

<img src="https://user-images.githubusercontent.com/7162775/191325755-bde881e0-9758-4600-a013-dbf99e0f6cee.JPG"  width="300">
<img src="https://user-images.githubusercontent.com/7162775/191325871-94bc2cf5-047f-44cb-ab51-c4f78cc396f5.jpg"  width="300">


En arrivant à Rennes en 2017, j’avais fait l’acquisition d’un nouveau concertina.
L’idée de trafiquer l’ancien pour en faire une version MIDI m’a alors traversé l’esprit.
J’ai également découvert l’impression et la modélisation 3D. J’ai vite compris l’intérêt de cette technologie concernant mon projet.
En découvrant les touches de clavier mécanique je suis tombé sur des tutoriaux permettant de réaliser soit même un circuit imprimé de clavier mécanique avec KiCad. Cette solution permet d’avoir beaucoup moins de soudure s, de câblage et rend le montage bien plus simple et la structure plus solide. https://github.com/ruiqimao/keyboard-pcb-guide

Dans ce contexte j’ai décidé de réaliser une nouvelle version utilisant le soufflet de mon ancien concertina. Ne me reste plus qu’a ;
 - Modéliser en 3D les deux mains de l’instrument
 - Réaliser un circuit imprimé pour chacune des mains
 - Intégrer un capteur de pression dans chaque main de l’instrument.
 - Faire ajouter par un luthier une gestion de l’air via une soupape (présente sur les vrai concertina) la soupape permet de gérer l’air dans l’instrument quand il y’en a trop ou pas assez.
Hormis ces quelques détails le code de l’instrument sera à peu près le même.

## Réalisation :
Cette version du concertina MIDI a demandé beaucoup de réflexions et l’intervention de nombreuses personnes (luthier pour les sangles et la soupape, imprimeur 3D). Cette version m’a couté environ 300 euros contre environ 100 pour la version précédente.
Capteur de pression et gestion de l’air
La gestion de l’air est une question complexe au sein de l’instrument. La soupape permet de gérer la quantité d’air dans l’instrument.
Cependant lorsqu’en jeu on appuie sur un ou deux voir trois boutons la consommation d’air n’est pas la même.
Or il n’y a aucune anche dans l’instrument imprimé en 3D. Le choix a été fait de laisser une certaine quantité d’air passer (un peu au jugé).
Capteur de pression
Le capteur de pression fait très bien l’affaire il permet de retrouver une sensation de jeu via l’intensité d’appui. L’augmentation de la pression est exponentielle dans l’instrument. Il faut appliquer une fonction logarithmique aux valeurs obtenu pour faire varier la vélocité MIDI.

Sur la version 0 et 1 de l’instrument le soufflet était un bouton partagé entre les deux instruments.
Or la ma principale erreur a été de mettre un capteur de pression dans chaque main de l’instrument.
En effet une tare est effectuée au démarrage de chaque Arduino, les valeurs sont bonnes pendant un certain temps puis les deux Arduino semblent ne pas réagir de la même façon.
Alors qu’un capteur pense que l’on pousse l’autre pense que l’on tire. Ce qui empêche a terme de jouer sur l’instrument.

Fort de toutes les erreurs des deux premiers modèles voici cependant le retour d’expérience  

## Retour d’expérience sur le troisième prototype :
 - Soucis de capteur de pression : comme vu plus haut les deux capteurs se désynchronise ce qui empêche de jouer correctement.
 - Le trou au jugé est trop grand et un travail sur l’étanchéité est nécessaire.
 - On doit avoir un seul Arduino (ou autre controlleur) qui gère tout l’instrument
 - Reste le souci du cablage.
 - Autant d’impression 3D, j’ai décidé d’acheter la mienne pour pouvoir progresser sur la modélisation et faire plusieurs prototypes plutôt que de faire imprimer une seule version définitive.

# Prototype V3 : Arduino MEGA

<img src="https://user-images.githubusercontent.com/7162775/191317407-98825e51-9206-4724-9a6d-7cb4a8463623.jpg"  width="300">

Vu le retour d’expérience du Prototype V2. La solution envisagée à été de connecter tous les boutons du concertina sur le même Arduino. Les Arduino classiques n’ont pas plus de 20 entrées. J’ai donc opté pour un Arduino MEGA.
Ensuite n’ayant pas d’option pour l’instant permettant de relier 15 cables entre les deux mains de l’instrument précèdent, j’ai opté pour une sorte d’accordina.
Cette fois l’objectif est de valider une version avec tout les boutons branchés sur le même Arduino.

Un circuit imprimé dédié a été réalisé et la conception et l’impression du corps de l’instrument en 3D à été réalisé par mes soins.

J’ai d’abord réutilisé mon code MIDI, cependant j’ai également mis une sortie audio (jack 3.5) et une sortie MIDI. Le but était d’ajouter un maximum d’entrée sortie pour explorer les possibilités de la chose.
Le souffle sera simulé par un bouton de clavier mécanique placé sur le côté de l’instrument.


## Synthèse sonore et Mozzi :
<img src="https://user-images.githubusercontent.com/7162775/191325909-834b5312-a6d7-411f-a7e2-d3204c3f9bb8.JPG"  width="300">
<img src="https://user-images.githubusercontent.com/7162775/191325943-2f39d959-f9ad-4015-856d-64fcb9e27225.jpg"  width="300">
<img src="https://user-images.githubusercontent.com/7162775/191317473-b5d5cbe5-68b5-4e9c-a069-f2e92ddda12a.jpg"  width="300">
<img src="https://user-images.githubusercontent.com/7162775/191317493-8f808993-de02-49d5-971b-ad84e6c936e7.jpg"  width="300">


C’est avant un long voyage en train que j’ai eu l’envie de m’occuper de la sortie audio. J’ai d’abord utilisé Tone la fonction dont a déjà parlé plus haut. Cependant en prenant le temps d’effectuer des recherches. J’ai découvert une librairie du nom de MOZZI qui permet de faire de la synthèse sonore bien plus intéressante que la synthèse de base pour Arduino.

Mozzi permet de créer des enveloppes, d’additionner des sinusoïdes, de gérer l’attack, decay, release etc…
Le temps d’expérimenter les différentes options j’ai d’abord implémenté une version uni-sonore et ensuite avec deux voies (une pour les bourdons et une pour la mélodie). J’ai ensuite essayé d’ajouter plusieurs voies pour rendre l’instrument 100% polyphonique. Cependant l’Arduino est trop lent pour pouvoir gérer les calculs nécessaires.

## Nouveau Hardware… :
J’ai également en complément ajouté à la conception un écran oled et un encoder. A la base pour permettre le debug et connaitre l’état du système.
En complément de Mozzi cet ajout s’est avéré précieux. En effet j’ai réalisé un système de Menu permettant de modifier les caractéristiques des différentes ondes présentes dans le son.
Finalement le son généré par l’Arduino est composé de :
	2 Oscillateurs pour le thème
	2 Oscillateurs pour les bourdons
Pour chaque oscillateur on peut choisir son octave et d’autres paramètres.
La librairie MOZZI demande quelques circuits en plus afin de fonctionner à son plein potentiel j’ai donc réalisé les circuits de sorties avec un ami électronicien.

## Nouveau problème… :
	L’encoder et l’écran semblent faire des interférences avec la génération d’ondes MOZZI.
Il semble que ce souci vienne des interruptions I2C (le bus I2C est un connecteur du Controller qui permet de gérer certaines entrées/sorties comme l’écran).
Retour d’expérience sur le deuxième prototype :
 - Toujours fan des switches de clavier mécanique.
 - Découverte d’une nouvelle façon de générer du son
 - Encoder + écran = beaucoup d’options, de debug et clairement de classe.
 - Mozzy => l’arduino MEGA pas assez rapide.

# Prototype 4 Teensy 4.1 :
Toujours éloigné de la forme même du concertina j’ai décidé de pousser plus loin l’accordina MIDI. En effet agréable à jouer tant au bureau avec Abletone qu’en itinérance au casque. J’étais plutôt satisfait du prototype précédent. Cependant je restais curieux du Teensy qui a la réputation d’aller plus vite et d’être fait pour ça.
J’ai également été retenu pour un salon : Maker Music Festival à Rennes le 24 et 25 septembre 2022, j’ai donc décidé de réaliser une nouvelle version de l’accordina embarquant un Teensy pour le présenter à l’évènement.
Pour l’instant c’est plutôt un succès pour plusieurs raisons :
 - Par rapport à l’Arduino le Teensy peut être reconnu directement comme un instrument MIDI supprimant la couche logiciel vu plus haut (Hairless MIDI Serial et loopmidi usb)
 - La librairie MOZZI semble fonctionner (même si la version 3.6 semble plus adaptée pour la musique)
 - Le teensy 4.1 à beaucoup d’entrées sorties ce qui permet d’avoir les 36 touches plus l’ecran le clavier, la sortie son.
 - La gestion de nombreuses enveloppes semble fonctionner
Cette version est la dernière en date elle est encore en cours de développement/test.

# Réflexions sur le futur et conclusion

De l’idée à l’objet en lui-même le chemin est long et sinueux. Avant de trouver une version capable de fonctionner sur scène la route est encore longue.
	L’idée de commercialiser le produit est présente depuis un petit moment. A voir s’il est possible de faire une utilisation commerciale des différentes librairies utilisées.
Cependant la question se pose de quoi commercialiser. Pas un Concertina MIDI parce que le cœur de cible est bien trop petit pour dégager une activité rentable.

Pour l’instant il me semble qu’une version de l’Accordina MIDI qui permettrait de s’adapter à tous les claviers d’accordéons (Chromatique, Diatonique, Concertina) me semblerait plausible. Il faudrait sans doute réaliser d’abord les choses suivantes :
Tester le multiplexage pour avoir une cinquantaine de touches au lieu de 30. Sur cette affaire j’ai entendu parler des mutliplexeur (qui utilisent des entrées binaires 0/1) ou des extendeurs d’IO i2C qui utilisent les entrées I2C.
Tester les DAC externes (des modules améliorant le son des différentes contrôleurs)
Tester les étages de sorties que Tony Jego à réalisé afin de l’intégrer a un futur circuit.
Embarquer tout ça sur une carte PCB unique.
Modéliser un Boitier méga classe et un peu lourd mais fin de tout le matos intégrant la carte, les boutons de clavier mécanique etc..
Calculer un prix de vente, vendre peut-être uniquement les pièces séparés ?
Cependant je pourrais me réaliser un concertina MIDI des que j’aurais répondu a toutes ces questions plus celles-là :
 - Comment gérer rigoureusement l’étanchéité
 - La soupape
 - Un long câble qui traverserait le soufflet contenant une vingtaine D’IO.

Hors des considérations commerciales sur cet objet, l’objectif à terme est surtout de se former pour pouvoir jouer de ces instruments sur scène (formation synth + Abletone)
Et malgré les difficultés rencontrées le plus passionnant dans ce projet c’est d’apprendre et d’approfondir les notions une par une pour créer un objet final qui puisse être utilisé


Quelques remerciements pour leur aide direct ou leur soutien :
Camille MILLET, Tony JEGO, Yannick CHIRON, Nicolas HARRAND, Jean BANWARTH
