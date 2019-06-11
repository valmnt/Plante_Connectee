import requests
import json
import getpass


url_api = "https://api.thinger.io/"
parametre = "oauth/token"

body = "grant_type=password&username=valmnt&password=valentin13"
header = "Content-Type:application/x-www-form-urlencoded"
main_api = url_api + parametre

monjson = json.dumps([])

mydata = {
    "Content-Type": "application/x-www-form-urlencoded",
    "grant_type": "password",
    "username": "valmnt",
    "password": "valentin13"

}

validtoken = requests.post(main_api, data= mydata).json()
connect = 0
sortieduprogramme = 0
#print(validtoken)
while(connect != 1):
    login = input ("Login : ")
    psw = getpass.getpass (prompt= "Password : ")

    if(requests.get('https://api.github.com/user', auth = (login, psw))):
        connect = 1
        while (sortieduprogramme == 0):
            print("Actualisation des devices...")
            parametre ="v1/users/valmnt/devices?authorization="+ validtoken["access_token"]
            main_api =url_api + parametre
            object_api = requests.get(main_api, params = mydata)

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
            print ("vous avez sélectionné : ", app)
            print(object_api.json())
            sortieduprogramme = 1

    else:
        print("")
        print("Login or password not good")
        print("")