
void handleAdmin() {
  String login_user;
  Serial.println("Remote Control Bomb - Admins Page");
 
  if ( (server.arg("u") == "admin") and (server.arg("p") == "qwerty") or logged_in) {
    logged_in = true;
    Serial.println("User " + server.arg("u")+" logged in!");
    
    server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    server.sendHeader("Pragma", "no-cache");
    server.sendHeader("Expires", "-1");
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.sendContent("<html><head></head><body>");
    ShowMenu();
    server.sendContent(  
      "<font aling='center'> <h1>Welcome to Remote Control Bomb - Admins Page!!!</h1> </font><br/>"
      "<label> Timer Extented: <b>") ;
      server.sendContent(String(time_extended));
      server.sendContent(
      " </b> Times </label><br/>"
      
      "<form method='POST' action='/admin/timerextend'"
      "<p> You could extend the time 3x, but lost 10% of points on each time. ></p> "
      "Extend the time! <input type='submit' value='Extend'/></form>"
      
      "<form method='POST' action='/admin/b0mbsetuping'>"
      "Plant the Bomb! <input type='submit' value='Plant'/></form>"
      
      "<form method='POST' action='/admin/b0mbdefusing'>"
      "Primeiros 6 digitos da somatoria de 100 numeros de 50 algarismos! <a href='http:'//download.it/arquivo.zip> file.zip </a>"
      "<input type='text' maxlength='10' placeholder='int' name='answer'/>"
      "<input type='submit' value='Answer'/></form>"

      "<form method='POST' action='/admin/fibonacci'>"
      "fibonacci(1500) <input type='text' maxlength='10' placeholder='int' name='answer'/>"
      "<input type='submit'  value='Answer'/></form>"
      
      
      "<frameset>  <frame cols='50%' src='\get'> </frameset>"
    );

  if (bomb_planted){
    server.sendContent(  
      "<h1>Bomb Planted - Answer 3 questions !!!</h1>"
      "<form method='POST' action='fibonacci'>"
      "fibonnaci (1500) ? <input type='text' placeholder='int' name='asnwer'/>"
      "<input type='submit' value=' Answer '/></form>"
      "<form method='POST' action='somatoria'>"
      "Defuse the Bomb! <input type='submit' value='Defuse'/></form>"
      "<frameset>  <frame cols='50%' src='\get'> </frameset>"
    );
  }


  }
  // Senao faca o redirect e caia fora, mas ja deixa o usuario salvo pra facilitar.
  else
      {
            server.sendHeader("Location", "./?login="+server.arg("u"), true);
            server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
            server.sendHeader("Pragma", "no-cache");
            server.sendHeader("Expires", "-1");
            server.send ( 302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
            server.client().stop(); // Stop is needed because we sent no content length
      }
    
    server.client().stop(); // Stop is needed because we sent no content length
}

void handleBombSetuping(){
  if (logged_in == true ) { 
      bomb_planted = true;
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
      bomb_planted = false;
      server.sendHeader("Location", "/admin", true);
      server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
      server.sendHeader("Pragma", "no-cache");
      server.sendHeader("Expires", "-1");
      server.send ( 302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
      server.client().stop(); // Stop is needed because we sent no content length
  
  }
}


void handleTimerExtend(){
  if (logged_in == true ) { 
      if (time_extended < 3) time_extended += 1;
      
      server.sendHeader("Location", "/admin", true);
      server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
      server.sendHeader("Pragma", "no-cache");
      server.sendHeader("Expires", "-1");
      server.send ( 302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
      server.client().stop(); // Stop is needed because we sent no content length
  
  }
}
