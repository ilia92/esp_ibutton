void handleRaw(){

Serial.println("You called RAW page");

String s;

//printf("char db[%d][17] = {\n", chips_count);
 for (int i = 0; i < chips_count; i++) {
        if ( db[i][0] != '\0' ) {
//        s += "\"";
        for (int c_id = 0; c_id < 15; c_id++) { 
          s += db[i][c_id];
          }
//          s += "\"<br>";
          s += "<br>";
            }
 }
 
 server.send(200, "text/html", s);

}
