﻿# Guide de l'application Plante Connectée


## Matériels requis
* Arduino Uno Wifi Rev 2
* DHT11 (capteur Humidité de l'air et de température)
* APDS 9301 (capteur d'humidité du sol)
* SEN019 (capteur de luminosité)

## Pré-requis

* Disposer d'un compte Thinger.io utilisable
* D'une connexion internet
* Plugin de l'IDE web d'arduino

## Configuration

### *Creer un device dans votre panneau de configuration Thinger.io*

[Thinger](https://console.thinger.io/#/login)
![device_img](img/device.PNG)

### *Champs à remplir avec vos informations*

![connexion_img](img/connexion.PNG)

* Username -> username Thinger.io
* Device ID -> nom de l'appareil
* Device_credential -> Token thinger.io
* SSID / SSID_PASSWORD -> information relative à la connexion

##  Guide d'utilisation de l'application

* Téléverser le code arduino 
* Executer le fichier python_interfaces.py
* Se connecter avec ses identifiants Thinger.io
* Sélectionner l'appareil que vous souhaitez utiliser
* Selectionner la plante que vous désirez
* Selectionner une des propositions suggérées

### Fonctionnalités des propositions :

#### 1.Les besoins

Permet de voir les conditions idéales relatives à chaques plantes

#### 2.Les informations

Permet de voir en direct les informations que les capteurs envoyent et les comparent aux conditions idéales

#### 3.Biographie

Donne des indications / renseignements sur la plante (géocalisation, nom complet...)


#### Made by @MontValentin and @ChomentonMatthias