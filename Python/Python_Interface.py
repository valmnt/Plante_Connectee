import requests
import json
import getpass
import time

url_api = "https://api.thinger.io/"
parametre = "oauth/token"

body = "grant_type=password&username=valmnt&password=valentin13"
header = "Content-Type:application/x-www-form-urlencoded"
main_api = url_api + parametre

monjson = json.dumps([])


sortieduprogramme = 0
i = 0
   
userExist = False
while userExist == False:

    login = input ("Login : ")
    psw = getpass.getpass("Password : ")
    mydata = {
    "Content-Type": "application/x-www-form-urlencoded",
    "grant_type": "password",
    "username": login,
    "password": psw
    }

        
    validtoken = requests.post(main_api, data= mydata).json()
    userExist = "access_token" in validtoken
    
parametre ="v1/users/valmnt/devices?authorization="+ validtoken["access_token"]
main_api =url_api + parametre
object_api = requests.get(main_api, params = mydata)
    
while (sortieduprogramme == 0):

    print("Actualisation des devices...")
            
    devices = object_api.json()

    print ("Voici la liste des devices disponibles : ")
    for device in devices:
        print(device["device"])
    print("")
    choice = input ("Quel appareil voulez-vous sélectionner ? ")

    for device in devices:
        if choice == device["device"]:
            app = device["device"]
    print("")
    sortieduprogramme = 1

tableauPlante = []
tableau = []
tableauNomPlante = []
indePlante = 0
dico = {}
x=0
y=0
exit=0
compteurDico=0
nomPlanteValide=0
numeroPlant = 0
choixInformationsValide = "oui"
verifExit = 0

parametres ="v2/users/valmnt/devices/arduino/LuxValue?authorization="+ validtoken["access_token"]
main_api =url_api + parametres
object_api = requests.get(main_api, params=mydata)
lux = object_api.json()

parametres ="v2/users/valmnt/devices/arduino/AtmosphericHumidity?authorization="+ validtoken["access_token"]
main_api =url_api + parametres
object_api = requests.get(main_api, params=mydata)
ha = object_api.json()

parametres ="v2/users/valmnt/devices/arduino/Celsius?authorization="+ validtoken["access_token"]
main_api =url_api + parametres
object_api = requests.get(main_api, params=mydata)
t = object_api.json()

parametres ="v2/users/valmnt/devices/arduino/SoilMoisture?authorization="+ validtoken["access_token"]
main_api =url_api + parametres
object_api = requests.get(main_api, params=mydata)
ht = object_api.json()

dicoCapteur = {
    "La luminosite": lux['out'],
    "La temperature":t['out'],
    "L'humidite de la terre":ht['out'],
    "L'humidite de l'air":ha['out'],
}

def AnalyseCapteur(valeurCapteur,valeurRequise):
    print(valeurCapteur,": ",end="")
    if dicoCapteur[valeurCapteur] > (valeurRequise*1.2):
        print(dicoCapteur[valeurCapteur],"est supérieur de plus de 20% par rapport à la valeur requise",valeurRequise)
        print(valeurCapteur,"est trop haute")
        
    elif dicoCapteur[valeurCapteur] > (valeurRequise*1.4):
        print(dicoCapteur[valeurCapteur],"est supérieur de plus de 40% par rapport à la valeur requise",valeurRequise)
        print(valeurCapteur,"est beaucoup trop haute")
        
    elif (dicoCapteur[valeurCapteur]*1.2) < valeurRequise:
        print(dicoCapteur[valeurCapteur],"est inférieur d'au moins 20% par rapport à la valeur requise",valeurRequise)
        print(valeurCapteur,"est trop haute")
        
    elif (dicoCapteur[valeurCapteur]*1.4) < valeurRequise:
        print(dicoCapteur[valeurCapteur],"est inférieur d'au moins 40% par rapport à la valeur requise",valeurRequise)
        print(valeurCapteur,"est beaucoup trop haute")

fichier = open("plantesDonnees.csv",'r')

for line in fichier:
    tableau = [line.split(";")]
    tableauPlante += tableau

while nomPlanteValide == 0:
    nomPlanteValide=0
    while y < len(tableauPlante)-1:
        x=0
        while x < len(tableauPlante[y]):
            if tableauPlante[y][x] == "nom":
                print(tableauPlante[y][x+1])
                tableauNomPlante.append(tableauPlante[y][x+1])
            x=x+1
        y=y+1
    x=0
    y=0
    numeroPlant = input("Quelle est le nom de la plante que vous voulez chouchouter ? ")
    for x in range(0,len(tableauNomPlante)):
        if numeroPlant == tableauNomPlante[x]:
            print("Vous avez choisis : ",numeroPlant)
            nomPlanteValide=1
            break;
    if nomPlanteValide == 0:
        print("Cette plante n'existe pas.")

while compteurDico <= len(tableauPlante[x])-2:
    dico[tableauPlante[x][compteurDico]]=tableauPlante[x][compteurDico+1]
    compteurDico=compteurDico+2

while exit == 0:
    while choixInformationsValide == "oui":
        choixInformations = input("Voulez vous voir les besoins de la plante(0), son état actuel(1) ou une description de la plante(2) ?")
        if choixInformations == "0":
            print(dico["nom"]," : ")
            print("Cette plante à besoin d'une humidité ambiante de",dico["humidité de l'air"])
            print("Cette plante à besoin d'une humidité de sol de",dico["humidité du sol"])
            print("Cette plante à besoin d'une température minimale de",dico["température min"])
            print("Cette plante à besoin d'une luminosité de",dico["luminosité"])
            
        elif choixInformations == "1":
            print(dico["nom"]," : ")
            AnalyseCapteur("La luminosite",float(dico['luminosité']))
            AnalyseCapteur("La temperature",float(dico["température min"]))
            AnalyseCapteur("L'humidite de la terre",float(dico["humidité du sol"]))
            AnalyseCapteur("L'humidite de l'air",float(dico["humidité de l'air"]))
            
        elif choixInformations == "2":
            print(dico["nom"]," : ")
            print("Cette plante fait partie de la famille des",dico["Famille"])
            print("Elle vient majoritairement de",dico["Origine"])
            print("Sa période de fleuraison est",dico["Période de floraison"])
            print("La couleur des fleurs est",dico["Couleur des fleurs"])
            print("C'est une",dico["Type de plante"])
            print("Sa hauteur à maturité est ",dico["Hauteur moyenne"])
        else:
            print("Cela ne fait pas partie des choix possibles.")

        verifExit=0
        while verifExit == 0:
            choixInformationsValide = str(input("Voulez vous continuer à utiliser l'appli ?(oui ou non)"))
            print(choixInformationsValide)
            if (choixInformationsValide != "oui" and choixInformationsValide != "non"):
                print("Je ne comprends pas.")
                verifExit = 0
            elif choixInformationsValide == "oui":
                verifExit = 1
            else:
                verifExit = 1
                exit = 1

fichier.close()


    


    
    











    
