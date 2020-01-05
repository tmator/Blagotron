#on affiche la liste des choix sur le minitel
#1 allo 2 chuck 3 comble 4 monsieurmadame 5 onnedispas 6 onneditpas
#quand on recoit un choix via le serial on lit une ligne tiree au sort du fichier demande


def returnBlague(choix):

    filepath = "blagues/onneditpas"
    with open(filepath) as fp:  
        line = fp.readline()
        cnt = 1
        while line:
            #print(line.strip().replace("<br>","\n"))
            line = fp.readline()
            cnt += 1    

    return "la blague"


def main():
    #ecoute serial
    print(returnBlague("1"))
    #envoi serial

    #envoi print

     
if __name__== "__main__":
  main()
