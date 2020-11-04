void dbButtonCodes(){
  
EEPROM.begin(4096);
char i[16];
EEPROM.get(0,i);
Serial.printf("char read: \n");
Serial.printf(" %s\n", i);

if ( strcasecmp(i,"0FFFFFFFFFFFFFF") != 0) {
Serial.printf("There is NO data, 1st Run, Defaults loaded!\n");

char db_manual[5][16] = {
"0FFFFFFFFFFFFFF",
"011111111111111",
"021222222222222"
};

EEPROM.put(0,db_manual);
EEPROM.commit();
}

else {
Serial.printf("DB loaded from EEPROM\n");
}

EEPROM.begin(4096);
EEPROM.get(0,db);

}
