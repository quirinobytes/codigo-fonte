
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
      "<div id='textbox'> <div id='titulo'>  <font aling='center'> <h3>Remote Control Bomb - Admin Page</h3> </font></div> <br/>"
      "Welcome! &nbsp;&nbsp;&nbsp;&nbsp; Your Time: &nbsp;&nbsp;&nbsp; ");
      if (bomb_planted and not win){
       //server.sendContent("<iframe color='white' width='100' height=25' src='/getbombstatus'></iframe>");
      }
    if (bomb_planted){ 
        server.sendContent(
      "<form method='POST' action='/admin/timerextend'>"
      "You could extend the time 3x, but you loose 10% of points on each time. "
      "<input type='submit' value='Extend'/></form>"             
      );
     }
      
      if (fase1) {
        server.sendContent("<br>&nbsp;&nbsp;&nbsp;&nbsp;| &#10004; | &nbsp;&nbsp; Fase 1");
      } 
      if (fase2) {
        server.sendContent(" &nbsp;&nbsp;&nbsp;&nbsp;| &#10004; | &nbsp;&nbsp; Fase 2");
      } 
      if (fase3) {
        server.sendContent(" &nbsp;&nbsp;&nbsp;&nbsp;| &#10004; | &nbsp;&nbsp; Fase 3");
      }
      if (fase4) {
        server.sendContent(" &nbsp;&nbsp;&nbsp;&nbsp;| &#10004; | &nbsp;&nbsp; Fase 4");
      }
      if (fase5) {
        server.sendContent(" &nbsp;&nbsp;&nbsp;&nbsp;| &#10004; | &nbsp;&nbsp; Fase 5");
      }
      
      server.sendContent(" &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; | Points: <b> ");
      server.sendContent(String(pontos_atual));
      server.sendContent(" / ");
      server.sendContent(String(pontuacao_maxima));
  
        
      server.sendContent(" &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; | <label> Timer Extented: <b>") ;
      server.sendContent(String(time_extended));
      server.sendContent("</b> Times ");
      server.sendContent("</b></label>");
      
     
     
     if (!bomb_planted) {
        server.sendContent(
          "<br><br><br/><hr>"
          "<form method='POST' action='/admin/b0mbsetuping'>"
          "<br/> To start the game Plant the Bomb <input type='submit' value='Plant'/></form>"
        );
      }
     
      if (fase1) {
         server.sendContent("<hr><br/><br/><br><br><br/> &nbsp;&nbsp;&nbsp;&nbsp;| &#10004; |&nbsp;&nbsp;"); 
        server.sendContent(
          "Qual os 10 ultimos d&iacute;gitos da somatoria de 100 numeros de 50 algarismos! <a href='/admin/arquivo.zip'> donwload </a><br>"
          "<form method='POST' action='/admin/somatoria'><br>"
          "Resposta: <input type='text' placeholder='int' name='answer'/>"
          "<input type='submit' value='Answer'/></form>"
          );
      }
      if (fase2){ 
           server.sendContent("<hr><br/><br/><br><br><br/> &nbsp;&nbsp;&nbsp;&nbsp;| &#10004; |&nbsp;&nbsp;"); 
          server.sendContent(
          
          "Quais os 10 primeiros d&iacute;gitos do resultado de fibonacci(1754)?<br><br>"
          "<form method='POST' action='/admin/fibonacci'>"
          "Resposta: <input type='text' placeholder='int' name='answer'/>"
          "<input type='submit'  value='Answer'/></form>");   
      }
      if (fase3){ 
          server.sendContent("<hr><br/><br/><br><br><br/> &nbsp;&nbsp;&nbsp;&nbsp;| &#10004; |&nbsp;&nbsp;"); 
          server.sendContent(
          "Qual cor de resistor e necess&aacute;ria para ter 0,100mA com 250V de tensao? com no max 5% de tolerancia <br> <br> Resposta: <br>"
          "<form method='POST' action='/admin/resistors'>"
          "<select class='form-control digit-picker' id='coluna1' name='coluna1' onChange=\"changeColor('coluna1');\" >"
          "<option class='brown' value='brown'>Brown</option>"
          "<option class='red' value='red'>Red</option>"
          "<option class='orange' value='orange'>Orange</option>"
          "<option class='yellow' value='yellow'>Yellow</option>"
          "<option class='green' value='green'>Green</option>"
          "<option class='blue' value='blue'>Blue</option>"
          "<option class='purple' value='purple'>Violet</option>"
          "<option class='grey' value='grey'>Gray</option>"
          "<option class='white' value='white' selected=''>White</option>"
          "</select>"
          
          "<select class='form-control digit-picker' id='coluna2' name='coluna2' onChange=\"changeColor('coluna2');\"  >"
          "<option class='black' value='black'>Black</option>"
          "<option class='brown' value='brown'>Brown</option>"
          "<option class='red' value='red'>Red </option>"
          "<option class='orange' value='orange'>Orange</option>"
          "<option class='yellow' value='yellow'>Yellow</option>"
          "<option class='green' value='green'>Green</option>"
          "<option class='blue' value='blue' selected=''>Blue</option>"
          "<option class='purple' value='purple'>Violet</option>"
          "<option class='grey' value='grey'>Gray</option>"
          "<option class='white' value='white'>White</option>"
          "</select>"
    
          "<select class='form-control digit-picker' id='coluna3' name='coluna3' onChange=\"changeColor('coluna3');\">"
          "<option class='black' value='black'> Black</option>"
          "<option class='brown' value='brown'> Brown</option>"
          "<option class='red' value='red'> Red</option>"
          "<option class='orange' value='orange'> Orange</option>"
          "<option class='yellow' value='yellow'> Yellow</option>"
          "<option class='green' value='green'> Green</option>"
          "<option class='blue' value='blue'> Blue</option>"
          "<option class='purple' value='purple'> Violet</option>"
          "<option class='grey' value='grey'> Gray</option>"
          "<option class='white' value='white'> White</option>"
          "<option class='gold' value='gold'> Gold</option>"
          "<option class='silver' value='silver' selected=''> Silver</option>"
          "</select>"
    
          "<select class='form-control digit-picker' id='coluna4' name='coluna4' onChange=\"changeColor('coluna4');\">"
          "<option class='brown' value='brown'> Brown </option>"
          "<option class='red' value='red'> Red </option>"
          "<option class='orange' value='orange'> Orange </option>"
          "<option class='yellow' value='yellow'> Yellow </option>"
          "<option class='green' value='green'> Green </option>"
          "<option class='blue' value='blue'> Blue </option>"
          "<option class='purple' value='purple'> Violet </option>"
          "<option class='grey' value='grey'> Gray </option>"
          "<option class='gold' value='gold' selected=''> Gold</option>"
          "<option class='silver' value='silver'>Silver</option>"
          "</select>"
          "<input type='submit'  value='Enviar'/></form>"   
      );
      }
    if (fase4) {
      final_fase = true;
       server.sendContent(  
       "<hr><br><br><br><br><br><br><br><br><form method='POST' action='/admin/b0mbdefusing'>"
       "Get your code until ... <input type='submit' value='go to next fase'/></form>"
       );
       
    }
    if (fase5){
      final_fase = false;
           server.sendContent("<hr><br/><br/><br><br><br/> &nbsp;&nbsp;&nbsp;&nbsp;| &#10004; |&nbsp;&nbsp;"); 
          server.sendContent(
          "<form method='POST' action='/admin/final'>"
          "Digite o codigo Final? <input type='text' placeholder='int' name='answer'/>"
          "<input type='submit'  value='Answer'/></form>");   
    }
    if (win){
      final_fase = false;
           server.sendContent("<hr><br/><br/><br><br><br/> &nbsp;&nbsp;&nbsp;&nbsp;| &#10004; |&nbsp;&nbsp;"); 
           server.sendContent(
            "Congratulations you win the game!"
            "<br><br>Take your flag: <b>{Mohamedlives}</b>");   
    }
 server.sendContent("</div></body>");
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
