/** Handle root or redirect to captive portal */
void handleRoot() {
  String login_user;
   int retry;
  if (captivePortal()) { // If caprive portal redirect instead of displaying the page.
    return;
  }
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.sendContent("<html><head>"
  "<style type='text/css'> "
  " #textbox {  background-color: white; margin:20px; padding:0; font: 100%/1.3 arial,helvetica,sans-serif; background:#3F6A8A; } "
  " #titulo { background-color: red; margin-top:10px; margin-botton:10px; margin-left:20px;margin-right:20px; padding:0; font: 130%/1.3 arial,helvetica,sans-serif; } "
  
  
  " </style> "
  
  
  
  "</head><body bgcolor='#FFFFFF' text='white'  >");
  ShowMenu();
  server.sendContent(
    "<div id='textbox'> <div id='titulo'> <h3> H2HC - BOMB CTF! </h3> </div> "
    "<p> Voce tem que descobrir a senha do usuario admin e acessar a <b> Remote Control Admin</b> page </p>"
    "<p> Apos acessar, plante a bomba para iniciar o game. Tem um tempo para acabar e voce tem que </p>"
    "<p> responder pelo menos 1 de 3 peruntas para poder desarmar a bomba, existem bonus de tempo, 3 bonus de +75%, use no final, pois a pontuacao maxima recebe uma pena 20%" 
    " Cada questao vale pontos, portanto se nao conseguir responder todas, foque em uma conseguir para desarmar a bomba.</p>"
    "<p> Ajuda no Manual da Bomba <a href=' ./manual' > manual </a> </p>"
    );
  
  if (server.client().localIP() == apIP) {
    server.sendContent(String("<p>Agora voce esta conecta atraves do AP: ") + softAP_ssid + "</p>");
  } else {
    server.sendContent(String("<p>Agora voce esta conecta atravez da rede wifi: ") + ssid + "</p>");
  }
  login_user=server.arg("login");
  
  server.sendContent(
    "<p> voce pode conectar em outras re. </p>"
    "<p> If you connect to another wifi, you will lost that password, to recover the </p>"
    "<p> password click here <a href='/wifi'> recover bomb password </a>.   </p>"
    "<p> or try login admin pages <a href='/admin'> Remote Control Admin </a>.</p>"
    "<form method='POST' action='admin'><h5>Login:</h5>");
    //server.sendContent(login_user);
    retry = login_user.length();
    if (retry > 0 ) {
        server.sendContent(
          "User: <input type='text' placeholder='"+ login_user +"' name='u'/>"
          "<br/> Password:<input type='password' placeholder='password' name='p'/>"
          "<br/> <input type='submit' value='Login'/></form>"
          "</body></html>"
        );  
    }
    else{
        server.sendContent(
          "<input type='text' placeholder='user' name='u'/>"
          "<br /><input type='password' placeholder='password' name='p'/>"
          "<br /><input type='submit' value='Login'/></form>"
          "</div></body></html>"
        );  
    }
    
    
  server.client().stop(); // Stop is needed because we sent no content length
}

