#on affiche la liste des choix sur le minitel
#1 allo 2 chuck 3 comble 4 monsieurmadame 5 onneditpas
#quand on recoit un choix via le serial on lit une ligne tiree au sort du fichier demande

import serial
from random import *
import os 

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

def returnBlague(choix):
    if (choix == "1"):
        filepath = "blagues/allo";
    elif (choix == "2"):
        filepath = "blagues/chuck";
    elif (choix == "3"):
        filepath = "blagues/comble";
    elif (choix == "4"):
        filepath = "blagues/monsieurmadame";
    elif (choix == "5"):
        filepath = "blagues/onneditpas";
    #on ouvre le fichier demande
    fp = open(filepath)

    #on recuprer les lignes dans une liste
    lines = fp.readlines()
    fp.close()
    #on fait un random sur le nombre de lignes
    ranln = randint(1,len(lines))
    return lines[ranln-1].strip().replace("<br>","\n")



def main():
    while 1:
        choix = ser.readline()
        if len(choix) > 0:
            print(str(choix.strip()))
            fp2 = open("/tmp/print.txt",w)
            fp2.write(returnBlague(str(choix).strip()))
            fp2.close()
            os.system("lp -d thermal img/img.png")
            os.system("lp -d thermal /tmp/print.txt")
            os.system("rm /tmp/print.txt")
    #ecoute serial
    #envoi serial ?

    #envoi print

     
if __name__== "__main__":
  main()
