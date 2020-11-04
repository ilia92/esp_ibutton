int chipCheck(char chip_read[12]) {

char got_db_chip[12];

//Serial.printf("Chip Read: %s\n", chip_read);

for (int i = 0; i < chips_count; i++) {

int tf = (int)db[i][2] - '0';

                for (int key_id = 0; key_id < 13; key_id++) { 
                  got_db_chip[key_id] = db[i][key_id+3];
//                  printf("%c",db[i][key_id+3]);
                  }
//                  printf (" ");

        if ( tf == 1 && strcasecmp(chip_read, got_db_chip) == 0 ){
//        printf("chip: %c%c %c is TRUE\n", db[i][0],db[i][1],db[i][2]);
return 1;
}
        if ( tf == 0 && strcasecmp(chip_read, got_db_chip) == 0 ){
        printf("Chip Found, but NOT allowed ");
return 1;
}
            }
            
printf("Chip NOT Found ");
return 0;
}
