#include <OneWire.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>

// apartments*people_in_apt - MAX must be under 256!
const int apts = 67;
const int chips_count = 230;
char db[chips_count][16];

OneWire  ds(2);
byte addr[8];
char got_button_code[13] = "" , last_button_code[13] ;

#include "dbButtonCodes.h"
#include "chipCheck.h"
#include "getButtonCode.h"

#include "WiFiAP.h"

void setup(void) {
  Serial.begin(115200);
  delay(1000);
// erase EEPROM-use with caution!
  //clearEEPROM();
  dbButtonCodes();
  WiFiAP();
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

}


void loop(void) {
  getButtonCode();
  if ( got_button_code[0] != '\0' ) {
    
  if ( chipCheck( got_button_code ) ) { 
  Serial.printf("Chip: %s is ALLOWED\n", got_button_code);
  digitalWrite(3, HIGH);
  delay(5000);
  }
  else {
  Serial.printf("Chip: %s NOT allowed\n", got_button_code);
  }
  digitalWrite(3, LOW);

   strcpy(last_button_code, got_button_code);
//   printf("Set new last button: %s\n" , last_button_code );
  }
  

 
  server.handleClient();

    
  delay(500);
}
