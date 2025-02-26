//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {
  Serial.begin(9600);  // Configurar la velocidad de la comunicación serial
  // Otro código de inicialización, como configurar el LCD

  lcd.init();  // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("SpotView!");
}


int espacios = 0;





void loop() {
  if (Serial.available() > 0) {
    int largo = 0;
    String substring(unsigned int startIndex, unsigned int endIndex);

    String data = Serial.readStringUntil('\n');

    int firstComma = data.indexOf(',');
    int secondComma = data.indexOf(',', firstComma + 1);
    int thirdComma = data.indexOf(',', secondComma + 1);
    int fourthComma = data.indexOf(',', thirdComma + 1);


    //recibiendo multiples argumentos desde python
    String song = data.substring(0, firstComma);
    String artist = data.substring(firstComma + 1, secondComma);
    String songId = data.substring(secondComma + 1, thirdComma);
    int duration = data.substring(thirdComma + 1, fourthComma).toInt();  // Convierte a int

    //bool changeSong = changingSong(oldSongId, songId);
    int i = 0;
    int entro = 0;
    int cont = 0;
    lcd.clear();

    for (i = 0; i < 15; i++) {
      if (song.charAt(i) == ' ') {
        //int changeSong = data.substring(secondComma + 1, thirdComma).toInt();  // Convierte a número (0 = false, 1 = true)
        cont = i;
      }
    }

      if (song.length() >= 16 && artist.length() >= 16) {
        String primeros15 = song.substring(0, cont);
        String resto = song.substring(cont);
        entro = 1;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(primeros15);
        lcd.setCursor(0, 1);
        lcd.print(resto);
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(artist);


      } else if (song.length() >= 16 && song.length() < 30 && artist.length() < 16) {
        String primeros15 = song.substring(0, cont);
        String resto = song.substring(cont);
        entro = 1;
        lcd.setCursor(0, 0);
        lcd.print(primeros15);
        lcd.setCursor(0, 1);
        lcd.print(resto);
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(artist);
        delay(3000);
        lcd.clear();


      } else {
        if (entro == 0) {

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(song);
          lcd.setCursor(0, 1);
          lcd.print(artist);
        }
      }
    }
  } 