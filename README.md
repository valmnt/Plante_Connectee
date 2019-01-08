# Documentation technique du projet Plante Connectée

## Descriptif du projet :

Nous sommes l’entreprise Connected Flowers qui souhaite développer un objet connecté permettant à une personne sans connaissance particulière en botanique de faire pousser des plantes chez soi ou en extérieur. Nous allons fournir à nos clients une base de données, que l’utilisateur peut étendre, qui contient initialement les spécifications de plusieurs plantes de la région. Notre base de données doit comprendre plusieurs paramètres tel que : Le nom de la plante, une catégorisation de la plante, la description, une ou plusieurs photos, L’humidité optimale du sol, la température atmosphérique optimale, La luminosité optimale et la période de floraison. Notre entreprise va devoir également fournir un objet connecté qui permet de capter l’humidité du sol, la luminosité et la température atmosphérique. Par ailleurs, l’utilisateur peut aussi planifier de planter une plante spécifique, et notre logiciel l’assistera en lui indiquant quand et comment la planter. Mais pour que tout cela fonctionne nous avons commencé par développer des algorithmes sur papier qui permettent de récupérer les valeurs du capteur et permettre leur traitement par le Raspberry. Mais nous avons également pris connaissance du fait qu’il pouvait y avoir des pertes d’information. C’est pour cela que nous avons mis en place une mémoire tampon, et afin de la réaliser nous avons utilisé la méthode du FIFO. Cette méthode est pratique car elle va permettre de traiter les données dans l’ordre sans avoir de pertes d’information.

## Les Algorithmes :

![algo](valmnt/Plante_Connectee/img/algo1)



