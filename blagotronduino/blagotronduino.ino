//blagotron
//    Use Fnct T + E to disable echo


#include <SoftwareSerial.h>
#include "Minitel.h"

Minitel minitel;

//mode 0 = affichage, 1 saisie, 2 credits, 3 wait, 4 boobs
int mode=0;

String text="";




void setup() {
  
  Serial.begin(9600);
  
  minitel.clearScreen();
  minitel.textMode();
  minitel.cursor();
}

void logo()
{
  minitel.clearScreen();
  minitel.textMode();
  minitel.clearScreen();
  minitel.graphicMode();
  minitel.pixelate();
  minitel.graphic("000001", 1, 1);
  minitel.graphic("011000");
  minitel.graphic("110000");
  minitel.graphic("110000");
  minitel.graphic("101101");
  minitel.graphic("000010");
  minitel.graphic("100010", 1, 2);
  minitel.graphic("000000");
  minitel.graphic("000110");
  minitel.graphic("000110");
  minitel.graphic("000110");
  minitel.graphic("000110");
  minitel.graphic("000001", 1, 3);
  minitel.graphic("011001");
  minitel.graphic("011001");
  minitel.graphic("011001");
  minitel.graphic("011000");
  minitel.graphic("000001");

  minitel.graphic("100001", 1, 4);
  minitel.graphic("100010");
  minitel.graphic("100000");
  minitel.graphic("100000");
  minitel.graphic("000000");
  minitel.graphic("000110");

  minitel.graphic("000000", 1, 5);
  minitel.graphic("110100");
  minitel.graphic("001100");
  minitel.graphic("001100");
  minitel.graphic("011000");
  
  minitel.noPixelate();

  minitel.textMode();
  minitel.textColor(BLACK);
  minitel.bgColor(WHITE);
  minitel.text("      BLAGOTRON      ", 13, 1);
  minitel.textColor(WHITE);
  minitel.bgColor(BLACK);
  mode=2;
}

void credits()
{
  minitel.text("BLAGOTRON Brice Rouanet / AlbiLab 2019",1,7);
  minitel.text("Merci a LIONEL B pour les blagues.",1,9);

  minitel.text("Minitel library for Arduino",1,11);
  minitel.text("By Jerome Saint-Clair aka 01010101",1,12);

  minitel.text("Based on works by the Tetalab",1,14);
  minitel.text("http://tetalab.org",1,15);

  


}
void loop() {

  

  minitel.listen(); // Listen for info coming from the Minitel
  
  minitel.readKey(); // Try to read a key press

  if (mode==0 || mode == 1)
  {
    //saisie
    text="";
    logo();
    minitel.text("Choisissez un thème de blague",1,7);
    
    minitel.text("1.-.Allo................................",  1,11);
    minitel.text("2.-.Chuck Norris........................",  1,12);    
    minitel.text("3.-.Les combles.........................",  1,13);
    minitel.text("4.-.Monsieur et Madame..................",  1,14);
    minitel.text("5.-.On ne dit pas.......................",  1,15);

    minitel.text("Appuyez sur le numéro puis",1,18);
    minitel.textColor(BLACK);
    minitel.bgColor(WHITE);
    minitel.text(" ENVOI ", 30, 18);
    minitel.textColor(WHITE);
    minitel.bgColor(BLACK);
    minitel.text("Appuyez sur GUIDE pour voir les crédits",  1,20);
    
     
    minitel.moveCursorTo(1, 11);
    mode=3;
  }
  else if (mode==2)
  {
    //credits
    logo();
    credits();
    mode=3;
  }
  else if (mode == 4)
  {
    //credits
    logo();
    credits();
    mode=3;
  }
    
  //remplir buffer si buffer plein autoriser utilisation de la touche envoie sinon, pas aut
  if (minitel.isCharacterKey()) {
    if (text.length()<120)
    {
      char key = minitel.getCharacterKey();
      minitel.textChar(key);
      text=key;
      
      if (text == "1") {
        minitel.moveCursorTo(1, 11);
      }
      else if (text == "2") {
        minitel.moveCursorTo(1, 12);
      }
      else if (text == "3") {
        minitel.moveCursorTo(1, 13);
      }
      else if (text == "4") {
        minitel.moveCursorTo(1, 14);
      }
      else if (text == "5") {
        minitel.moveCursorTo(1, 15);
      }
      
    }
    
    
  }
  else if (minitel.isMenuKey()) {
    int key = minitel.getMenuKey();
    if (key == RETOUR) { // Return
      minitel.moveCursorTo(HOME);
      minitel.moveCursor(DOWN, 1);
    }
    else if (key == CORRECTION) {
      minitel.moveCursor(LEFT, 1);
      minitel.textChar(' ');
      minitel.moveCursor(LEFT, 1);     
      text.remove(text.length()-1);          
    }
    else if (key == GUIDE) {
      //afficher doc / credits
      mode=2;
    }
    else if (key == SUITE) {
      //afficher doc / credits
      mode=2;
    }
    

    
    else if (key == ENVOI) {
      if (text.length() > 0)
      {
        //envoi du tweet saisi
        Serial.println(text);
        text="";
        mode=0;
      }
    }    
    else if (key == ANNULATION || (key == SOMMAIRE) || (key == RETOUR)){
      //affiche tweets
      minitel.clearScreen();
      mode=0;
    }
  }

  //minitel.clearScreen();
  //minitel.pixelate();  
  
  //minitel.textMode();  

  //car spe 

  //SPE_CHAR_HASHTAG
  //SPE_CHAR_DOLLAR



  

}
