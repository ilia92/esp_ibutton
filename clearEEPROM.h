 void clearEEPROM() {

String s = "EEPROM Cleared";
 EEPROM.begin(4096);
 
  // write 0 to all bytes of the EEPROM
  for (int i = 0; i < 4096; i++) {
    
    EEPROM.put(i,0);

  }
  EEPROM.commit();
  Serial.println("EEPROM Cleared, empty DB loaded!");

EEPROM.begin(4096);
EEPROM.get(0,db);

server.send(200, "text/html",s );

}
