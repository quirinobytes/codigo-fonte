void handleResistors(){
Serial.println("### ENTRANDO NA RESISTORS ###");

Serial.println(server.arg("coluna1"));

String resultado1 = "red", resultado2="green", resultado3 = "red", resultado4="gold";

Serial.println(server.arg("coluna1"));
 if ( (server.arg("coluna1") == resultado1) and (server.arg("coluna2") == resultado2) and (server.arg("coluna3") == resultado3 )and (server.arg("coluna4") == resultado4) and logged_in) {
  fase3 = false;
  fase4 = true; 
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.sendContent("<html><head>");
  includeCss();
  server.sendContent("</head><body>");
  ShowMenu();
  pontos_atual+=300;
  server.sendContent(
      "<div id='textbox'> <div id='titulo-green'>  <font aling='center'><h2> Congratulations, you pass.</h2></font></div>"
      "<p> clap clap clap</p>"
      "<a href='/admin'> <button> OK </button> </a>"
      "<br></div>"
      
  );
 }
 else{
            server.sendHeader("Location", "/admin", true);
            server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
            server.sendHeader("Pragma", "no-cache");
            server.sendHeader("Expires", "-1");
            server.send ( 302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
            server.client().stop(); // Stop is needed because we sent no content length 
 }
  server.client().stop(); // Stop is needed because we sent no content length
}

