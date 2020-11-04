int getButtonCode() {

char str[1]="";
//char got_button_code[11]="";

memset(got_button_code, 0 , sizeof(got_button_code));

   ds.reset_search();
   
// some checks
  if ( !ds.search(addr) ) {
//    Serial.printf("EmptyAddress\n"); 
    return 0;}
  if ( OneWire::crc8( addr, 7) != addr[7]) {
//    Serial.printf("CRC Invalid\n");
    return 0;}
  if ( addr[0] != 0x01) {
//    Serial.printf("Wrong chip\n");
    return 0;}

      for(int i = 6; i > 0; i--) {
        
//        Serial.printf("%02x ", addr[i]);

// convert hex array to string arduino
        sprintf(str,"%02x",addr[i]);
        strcat(got_button_code , str);

}

//Serial.printf("Read iButton code: %s\n", got_button_code);
return 1;
}
