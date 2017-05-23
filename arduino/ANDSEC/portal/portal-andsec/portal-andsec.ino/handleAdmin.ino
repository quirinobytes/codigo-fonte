
void handleAdmin() {
  char user[5] = "";
  char senha[8] = "";
  Serial.println("Remote Control Bomb - Admins Page");
  server.arg("n").toCharArray(user, sizeof(user) - 1);
  server.arg("p").toCharArray(senha, sizeof(senha) - 1);
  if (String(user).equals(String('rafael')) and String(senha).equals(String('xman'))){
    server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    server.sendHeader("Pragma", "no-cache");
    server.sendHeader("Expires", "-1");
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.sendContent("<html><head></head><body>");
    ShowMenu();
    server.sendContent(  
      "<font aling='center'> <h1>Gotch !!! Welcome to Remote Control Bomb - Admins Page !!!</h1> </font>"
      "<h1>Plant the Bomb! </h1><a href='/getbombstatus'> link </a>"
      "<h1>Refuse the Bomb! </h1><a href='/command'> link </a>"
      "<frameset>  <frame cols='50%' src='\get'> </frameset>"
    );
  }
    else
      {
            server.sendHeader("Location", "./?login=false", true);
            server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
            server.sendHeader("Pragma", "no-cache");
            server.sendHeader("Expires", "-1");
            server.send ( 302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
            server.client().stop(); // Stop is needed because we sent no content length
      }
    
    server.client().stop(); // Stop is needed because we sent no content length
}
