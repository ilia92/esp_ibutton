const char index_begin[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
<head>
<title>ESP8266 Web Form Demo</title>
</head>
<body>
<h1>Last Chip:</h1>

)=====";

const char form_end[] PROGMEM = R"=====(
<br>
<FORM action="/" method="post">
<P>
<INPUT type="submit" value="Add to Apt:">
<INPUT type="name" name="add_chip_apt" value="">
</P> 
</FORM>
<br><br>
)=====";

const char index_end[] PROGMEM = R"=====(

</body>
</html>
)=====";

void handleRoot() {
 
//int add_chip_apt_int,
int chip_num;
char chip_num_char[2], tmpc[2]="", tmp2c[2]="";


 Serial.println("You called root page");
 String s = index_begin ; //Read HTML contents
 s += last_button_code;
 s += form_end;

// Check if apartments are enabled
    int apt_en[apts];
    for (int j = 1; j < apts; j++) {
    for (int i = 1; i < chips_count; i++){


        chip_num_char[0]=db[i][0];
        chip_num_char[1]=db[i][1];
        chip_num = atoi(chip_num_char);

        if ( chip_num == j && db[i][2] == '1' ) {
          apt_en[j]=1;
//           Serial.printf("Apt ENABLE: %d - %d\n", j,apt_en[j]);
           break;
        }
        else
           {
          apt_en[j]=0;
//          Serial.printf("ELSE: %d - %d\n", j,apt_en[j]);
           }
    }
    }

//for (int j = 1; j < apts; j++) {
//             Serial.printf("ENABLED: %d\n",apt_en[j] );
//}

for (int j = 1; j < apts; j++) {
  
//        Serial.printf("Apartment: %d\n",j);

          sprintf(tmp2c,"%02d",j);
          s += "<FORM action=\"/\" method=\"get\"><input type=\"checkbox\" " ;
                   
          if ( apt_en[j] ) {
          s += "checked><input type=\"hidden\" name=\"endis\" value=\"";
          s +=  tmp2c ; 
          s += "0\"> Apartment: ";
          s +=  j ;
          s += "&emsp;<input type=\"submit\" value=\"Disable\"></FORM>";
          }
          else {
          s += "><input type=\"hidden\" name=\"endis\" value=\"";
          s +=  tmp2c ; 
          s += "1\"> Apartment: ";
          s +=  j ;
          s += "&emsp;<input type=\"submit\" value=\"Enable\"></FORM>";
          }
          
          s += "<br>";
          
    for (int i = 1; i < chips_count; i++){
        
        chip_num_char[0]=db[i][0];
        chip_num_char[1]=db[i][1];
        chip_num = atoi(chip_num_char);

      
        if ( chip_num == j ) {
          
        s += "<form action=\"/\" method=\"post\">";
for (int c_id = 3; c_id < 15; c_id++) { 
          s += db[i][c_id];
          }
        s += "&emsp;&emsp;&emsp;<button type=\"submit\" name=\"del\" value=\"" ;
        s += db[i];
        s += "\">Delete</button></form><br>\n";
        }
        }
        s += "<form action=\"/\" method=\"post\"><INPUT type=\"hidden\" name=\"addnew_pre\" value=\'";
        s += tmp2c;
        s += "\'><INPUT type=\"name\" name=\"addnew_suff\" value=\'\'><INPUT type=\"submit\" value=\"Add chip\"></form><br>\n";
        s += "<br><br>\n";
        }



  server.send(200, "text/html", s); //Send web page

if ( server.hasArg("del") ) {

      String chip_id_s = server.arg("del");
      char chip_id[16] ;
      memset(chip_id, 0 , sizeof(chip_id));
      strcpy(chip_id, chip_id_s.c_str());
      
      if ( strlen(chip_id) != 15 ) {
      server.send(200, "text/html", "Incorrect chip ID");
      return;
      }

      chip_id[15] = '\0';
for (int i = 0; i < chips_count; i++) {

        if ( strcasecmp(db[i],chip_id) == 0 ){
db[i][0] = '0';db[i][1] = '0';db[i][2] = '0';
Serial.printf("Chip DELETED: %s\n", chip_id);
  
}
}
  EEPROM.begin(4096);
  EEPROM.put(0,db);
  EEPROM.commit();
  Serial.printf("Saved To EEPROM\n");
}

if ( server.hasArg("add") ) {

      String chip_id_s = server.arg("add");
      char chip_id[16] ;
      memset(chip_id, 0 , sizeof(chip_id));
      strcpy(chip_id, chip_id_s.c_str());
      
      if ( strlen(chip_id) != 15 ) {
      server.send(200, "text/html", "Incorrect chip ID");
      return;
      }

  for (int i = 0; i < chips_count; i++) {
        if (( db[i][0] == '\0' ) || ( db[i][0] == '0' && db[i][1] == '0' )) {
        chip_id[16] = '\0';
        strcpy(db[i],chip_id);
        break;
            }}
  Serial.printf("Chip ADDED: %s\n", chip_id);
  
  EEPROM.begin(4096);
  EEPROM.put(0,db);
  EEPROM.commit();
  Serial.printf("Saved To EEPROM\n");
    }

  if ( server.hasArg("endis") )
  {
          String chip_id_s = server.arg("endis");
      char chip_id[16] ;
      memset(chip_id, 0 , sizeof(chip_id));
      strcpy(chip_id, chip_id_s.c_str());
      
      if ( strlen(chip_id) != 3 ) {
      server.send(200, "text/html", "Incorrect input format!");
      return;
      }

for (int i = 1; i < chips_count; i++) {

// Very clever way to fast check only one char of the strings
        if ( db[i][0] == chip_id[0] && db[i][1] == chip_id[1] ) {

db[i][2] = chip_id[2];

Serial.printf("Chip EDITED: %s\n",db[i]);
}}
  EEPROM.begin(4096);
  EEPROM.put(0,db);
  EEPROM.commit();
  Serial.printf("Saved To EEPROM\n");
  }


  if ( server.hasArg("add_chip_apt") )
  {
    int add_chip_apt_int;
  String add_chip_apt_val = server.arg("add_chip_apt");
  add_chip_apt_int = atoi(add_chip_apt_val.c_str());
  
  if ( add_chip_apt_int <= 99 && add_chip_apt_int > 0)  {
int i;
 for (i = 1; i < chips_count; i++) {
        if (( db[i][0] == '\0' ) || ( db[i][0] == '0' && db[i][1] == '0' )) {
        sprintf(db[i], "%02d1%s", add_chip_apt_int, last_button_code);
        break;
            }}
  Serial.printf("New Chip ADDED: %s to Apt: %d at position: %d \n",last_button_code, add_chip_apt_int, i );            
            }
 
  EEPROM.begin(4096);
  EEPROM.put(0,db);
  EEPROM.commit();
  Serial.printf("Saved To EEPROM\n");
  }


  if ( server.hasArg("addnew_pre") &&  server.hasArg("addnew_suff") ) {
    int add_chip_apt_int;
  String addnew_pre = server.arg("addnew_pre");
  String addnew_suff = server.arg("addnew_suff");
  
  char button_code[13];
  sprintf(button_code, "%s" ,addnew_suff.c_str());
  add_chip_apt_int = atoi(addnew_pre.c_str());
  
  if ( add_chip_apt_int <= 99 && add_chip_apt_int > 0)  {
int i;
 for (i = 1; i < chips_count; i++) {
        if (( db[i][0] == '\0' ) || ( db[i][0] == '0' && db[i][1] == '0' )) {
        sprintf(db[i], "%02d1%s", add_chip_apt_int, button_code);
        break;
            }}
  Serial.printf("New Chip ADDED: %s to Apt: %d at position: %d \n",button_code, add_chip_apt_int, i );            

    
  }   
  }
  
}
