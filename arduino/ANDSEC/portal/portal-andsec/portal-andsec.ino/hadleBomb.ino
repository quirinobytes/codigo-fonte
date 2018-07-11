//funcao de test
void handleGet() {
  Serial.println("#GET: /get");
//  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
//  server.sendHeader("Pragma", "no-cache");
//  server.sendHeader("Expires", "-1");
//  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.setContentLength(4);
//server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
//server.sendContent(String("<html><head></head><body>")  );
  server.sendContent(String("5000"));
//server.sendContent(String("</body></html>")  );
//server.client().stop(); // Stop is needed because we sent no content length
}

/* URL:http://bombserver/get */ 
void handleGetBombStatus() {
  String resp = "";
  Serial.println("#REQUEST GET: /getbombstatus");
  Serial.println(millis());
  RestClient client  = RestClient("192.168.1.166",80);
  int statusCode = client.get("/bomb.txt", &resp);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: http://192.168.10.1/get = ");
  Serial.println(resp);
  server.sendContent(
        "<html><head><script>"
        "window.setInterval('reloadFrame();', 20000);"
        "function reloadFrame()"
        "{"
        "  document.location.reload();  "
        "}"
        "</script><font color='white'> "
        ) ;
  server.sendContent(resp);
  //conta o tempo e mostra na getbombstatus
  long game_time = 3200 - (millis() - bomb_planted_time)/1000;
  server.sendContent(String(game_time));
  Serial.println("game time:" + String(game_time));
  server.sendContent(" </font>");
  
  server.client().stop(); // Stop is needed because we sent no content length
}


void handleBombSetuping(){
  if (logged_in == true ) { 
      bomb_planted = true;
      fase1=true;
      bomb_planted_time = millis();
      server.sendHeader("Location", "/admin", true);
      server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
      server.sendHeader("Pragma", "no-cache");
      server.sendHeader("Expires", "-1");
      server.send ( 302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
      server.client().stop(); // Stop is needed because we sent no content length
  
  }
} 

void handleBombDefusing(){
  if (logged_in == true ) { 
      //bomb_planted = false;
      fase4=false;
      fase5=true;
      server.sendHeader("Location", "/admin", true);
      server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
      server.sendHeader("Pragma", "no-cache");
      server.sendHeader("Expires", "-1");
      server.send ( 302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
      server.client().stop(); // Stop is needed because we sent no content length
  
  }
}


