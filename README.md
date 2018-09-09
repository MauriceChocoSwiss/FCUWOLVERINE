# FCUWOLVERINE
A FCU for Wolverine airsoft HPA system

Petite présentation des fonctionnalités de cette petite carte sur base arduino..

Je vais expliquer les menus dans l'ordre 1 par 1.

Les valeur 0 ou 1 signifient respectivement, Non et Oui.

Menu principal -> 
  -En haut à gauche: billes restantes dans le chargeur et nombre de billes théorique du chargeur.
  -En haut à droite: compteur total de billes tirés depuis la mise sous tension.
  -En bas à gauche: mode de tir. Pour le Burst, le nombre représente le nombre tiré pendant la rafale.
  -En bas à droit: Tension de la b atterie.

Les menus seront ensuite expliqué dans le cas ou vous actionnez le joystick vers le haut.

Menu Burst -> 
  -En haut à gauche: Rate of fire en mode full, valeur bloqué à 35 max (nbr de billes par secondes).
  -En bas à gauche: Rate of fire en mode Burst(rafale), valeur bloqué à 35 max (nbr de billes par secondes).
  -En bas à droite: Nombre de billes de la rafale.

Menu Sniper ->
  -En haut à gauche: Activation de la led verte pour signal "pret a tirer".
  -En bas à gauche: Délai en seconde pour la simulation de l'armement manuel.
  
Menu Chargeur -> 
  -En haut à gauche: Definition de la quantité de billes du chargeur.
  -En haut à droite: Activation du blocage de la réplique lorsque le compteur arrive à 0 ou en dessous.
  -En bas à gauche: Activation de la détection chargeur. Si oui, la réplique ne peut tirer si le switch ou bouton du chargeur n'est pas activé.
   Le cas échéant la réplique pourra tirer sans chargeur.
  -En bas à droite: Activation du buzzer pour l'alarme "capacité Low".

Menu Chargeur 2 -> 
  -En haut à gauche: Activation de l'alarme "Capacité Low" et "Plus de bille".
  -En haut à droite: Quantité de billes de l'alarme "Low".
  -En bas à gauche: Activation de la dectection de la charging handle. Lorsque le blocage de fin de chargeur est activé, si vous remettez un chargeur sans activer la charging handle alors que l'option est active, vous ne pourrez pas tirer.
  -En bas à droite: LED de la charging handle, indiquant que la réplique est prete a tirer.

MenuSettings -> 
  -En haut à gauche: Activation du verouillage d'écran.
  -En haut à droite: Delai d'extinction en secondes, avance de 3à sec en 30 sec.
  -En bas à gauche: Activation de l'alarme tension batterie et blocage des tirs.
  
Menu Settings 2 ->

Détails des valeurs pour la position du selecteur:
  1: Semi
  2: Burst
  3:Full
  4:Sniper
  
  -En haut à gauche: Sélection du mode de tir pour la position SEMI du sélecteur.
  -En bas à gauche: Sélection du mode de tir pour la position FULL du sélecteur.
  -En bas à droite: Réglage du dwel, valeur de 25 à 110, incrément de 1.
