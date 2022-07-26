/* SD MOSI 11
 *    MISO 12
 *    CLK 13
 *    CSB 4
 *    
 */


#define SD_CSB 4
#define STATUS 13
#define TYPE_BUTTON 12
#define FILE_BUTTON 11

#include <SD.h>
#include <SPI.h>
#include <Keyboard.h>

File root;
File currFile;

void setup() {
  // init
  SD.begin(SD_CSB);
  Keyboard.begin();

  root = SD.open("/");

  root.openNextFile();

  currFile = root.openNextFile();

  // button setup
  pinMode(TYPE_BUTTON, INPUT_PULLUP);
  pinMode(FILE_BUTTON, INPUT_PULLUP);
  pinMode(STATUS, OUTPUT);

  // turn on when ready
  digitalWrite(STATUS, HIGH);
  
}

void loop() {
  // test for button press
  if (digitalRead(TYPE_BUTTON) == LOW) {
    // test for EOF
    if (currFile.available()) {  Keyboard.write(currFile.read()); delay(50);  }
    else {  currFile.close();  }
  }  

  // test for button press
  if (digitalRead(FILE_BUTTON) == LOW) {  
    // load next file
    blinkLED();
    delay(1000);
    Keyboard.println();
    currFile.close();
    currFile = root.openNextFile();  

    // test for end of dir
    if (!currFile) {  root.rewindDirectory(); root.openNextFile(); currFile = root.openNextFile();  }
  }
}

void blinkLED() {
  digitalWrite(13,LOW);
  delay(200);
  digitalWrite(13,HIGH);
  delay(200);
  digitalWrite(13,LOW);
  delay(200);
  digitalWrite(13,HIGH);
  delay(200);
  digitalWrite(13,LOW);
  delay(200);
  digitalWrite(13,HIGH);
}
