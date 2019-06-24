# Documentation technique du projet Plante Connectée

## Descriptif du projet :

Nous sommes l’entreprise Connected Flowers qui avont développé un objet connecté permettant à une personne sans connaissance particulière en botanique de faire pousser des plantes chez soi ou en extérieur. Connected Flowers 
fournit une base de données, que l’utilisateur peut étendre, qui contient initialement les spécifications d’environ 30 plantes de la région. 
La base de donnée comprend : Le Nom de la plante, une Catégorisation de la plante, la Description, l’humidité optimale du sol, la température atmosphérique optimale, la luminosité optimale, la période de floraison.

## Arduino

Notre code Arduino permet de lire les differentes valeurs de nos différents capteurs connectés à l'Arduino Uno Wifi rev 2. Ensuite, notre programme affiche ces valeurs dans la commande de l'IDE Arduino et les
envoie sur Thinger.io

### Interface Thinger.io
![ouverturefichier](/img/thinger_img.PNG)

## Python

Notre code Python permet de creer une application en ligne de commande (CMD). De récuprer les valeurs que Thinger.io reçoit de l'Arduino et les affiche dans l'Application. Au sein de l'application, vous vous connectez avec votre
compte Thinger.io et ensuite vous sélectionnez votre appareil. Une liste de plante vous sera proposé, il faudra en choisir une parmit celles proposées et ensuite vous pourrez voir ses informations globales ainsi que les valeurs des capteurs
avec un indicateur qui vous indiquera si les valeurs sont trop haute ou trop basse.


