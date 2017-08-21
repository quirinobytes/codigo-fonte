
void handleAdmin() {
  
  Serial.println("Remote Control Bomb - Admins Page");
  Serial.println("User="+ server.arg("u") + "\nPass=" + server.arg("p") );
 
  if ( ((server.arg("u") == "admin") and (server.arg("p") == "hacktheplanet")) or logged_in) {
    logged_in = true;
    Serial.println("User " + server.arg("u")+" logged in!");
    
    server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    server.sendHeader("Pragma", "no-cache");
    server.sendHeader("Expires", "-1");
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.sendContent("<html><head></head><body>");
    includeCss();
    includeJS();
    ShowMenu();
    server.sendContent(  
      "<font aling='center'> <h2>Remote Control Bomb - Admin Page</h2> </font><br/>"
      "welcome!"
      "<br/><br/>"
      
      
      "<label> Timer Extented: <b>") ;
      server.sendContent(String(time_extended));
      server.sendContent(" </b> Times ");
      server.sendContent(" &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; | Pontuacao: <b>");
      server.sendContent(String(pontos_atual));
      server.sendContent(" / ");
      server.sendContent(String(pontuacao_maxima));
      server.sendContent(
      "</b></label><br/>"
      "<form method='POST' action='/admin/timerextend'"
      "<p> You could extend the time 3x, but lost 10% of points on each time.</p> "
      "Extend the time! <input type='submit' value='Extend'/></form>"
      
      "<form method='POST' action='/admin/b0mbsetuping'>"
      "Plant the Bomb! <input type='submit' value='Plant'/></form>"
      
      "<form method='POST' action='/admin/b0mbdefusing'>"
      "Defuse the Bomb! <input type='submit' value='Defuse'/></form>"
      "<form method='POST' action='/admin/somatoria'>"
      );
      if (fase1) server.sendContent("&#10004;&nbsp;&nbsp;");
      server.sendContent(
      "10 ultimos digitos da somatoria de 100 numeros"
      "<p> de 50 algarismos! <a href='/admin/arquivo.zip'> donwload </a>"
      "<input type='text' placeholder='int' name='answer'/>"
      "<input type='submit' value='Answer'/></form>"
      "<form method='POST' action='/admin/fibonacci'>"
      );
      if (fase2) server.sendContent("&#10004;&nbsp;&nbsp;");
      server.sendContent(
      "fibonacci(1754) <input type='text' placeholder='int' name='answer'/>"
      "<input type='submit'  value='Answer'/></form>"   
      
      "<select class='form-control digit-picker' id='b4d1'>"
      "<option class='brown' value='1'>Brown</option>"
      "<option class='red' value='2'>Red </option>"
      "<option class='orange' value='3'>Orange</option>"
      "<option class='yellow' value='4'>Yellow</option>"
      "<option class='green' value='5'>Green</option>"
      "<option class='blue' value='6'>Blue</option>"
      "<option class='purple' value='7'>Violet</option>"
      "<option class='grey' value='8'>Gray</option>"
      "<option class='white' value='9' selected=''>White</option>"
      "</select>"
      
      "<select class='form-control digit-picker' id='b4d2'>"
      "<option class='black' value='0'>Black</option>"
      "<option class='brown' value='1'>Brown</option>"
      "<option class='red' value='2'>Red </option>"
      "<option class='orange' value='3'>Orange</option>"
      "<option class='yellow' value='4'>Yellow</option>"
      "<option class='green' value='5'>Green</option>"
      "<option class='blue' value='6' selected=''>Blue</option>"
      "<option class='purple' value='7'>Violet</option>"
      "<option class='grey' value='8'>Gray</option>"
      "<option class='white' value='9'>White</option>"
      "</select>"

      "<select class='form-control digit-picker' id='b4d3'>"
      "<option class='black' value='x1'> Black</option>"
      "<option class='brown' value='x10'> Brown</option>"
      "<option class='red' value='x100'> Red</option>"
      "<option class='orange' value='x1k'> Orange</option>"
      "<option class='yellow' value='x10k'> Yellow</option>"
      "<option class='green' value='x100k'> Green</option>"
      "<option class='blue' value='x1M'> Blue</option>"
      "<option class='purple' value='x10M'> Violet</option>"
      "<option class='grey' value='x100M'> Gray</option>"
      "<option class='white' value='x1G'> White</option>"
      "<option class='gold' value='÷10'> Gold</option>"
      "<option class='silver' value='100' selected=''> Silver</option>"
      "</select>"

      "<select class='form-control digit-picker' id='b4d4'>"
      "<option class='brown' value=''> Brown </option>"
      "<option class='red' value=''> Red </option>"
      "<option class='orange' value=''> Orange </option>"
      "<option class='yellow' value=''> Yellow </option>"
      "<option class='green' value=''> Green </option>"
      "<option class='blue' value=''> Blue </option>"
      "<option class='purple' value=''> Violet </option>"
      "<option class='grey' value=''> Gray </option>"
      "<option class='gold' value='' selected=''> Gold</option>"
      "<option class='silver' value=''>Silver</option>"
      "</select>"
);

  if (bomb_planted){
    server.sendContent(  
      "<br><br><h2> The game start and the Bomb is Planted! </h2>"
      "<iframe width='400' height='80' src='/getbombstatus'>"
      "<p>Your browser does not support iframes.</p>"
      "</iframe>"
//      "<br><form method='POST' action='fibonacci'>"
//      "fibonnaci (1500) ? <input type='text' placeholder='int' name='asnwer'/>"
//      "<input type='submit' value=' Answer '/></form>"
//      "<form method='POST' action='somatoria'>"
//      "<br>Defuse the Bomb! <input type='submit' value='Defuse'/></form>"
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


void handleTimerExtend(){
  if (logged_in == true ) { 
      if (time_extended < 3) {
        time_extended += 1;
        //aumenta o tempo em 20%
        bomb_planted_time +=(millis()-bomb_planted_time)*20/100;
        //a pontuacao maxima recebe uma pena
        pontuacao_maxima += (pontuacao_maxima*-1)*20/100;
      }
      
      server.sendHeader("Location", "/admin", true);
      server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
      server.sendHeader("Pragma", "no-cache");
      server.sendHeader("Expires", "-1");
      server.send ( 302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
      server.client().stop(); // Stop is needed because we sent no content length
  
  }
}
