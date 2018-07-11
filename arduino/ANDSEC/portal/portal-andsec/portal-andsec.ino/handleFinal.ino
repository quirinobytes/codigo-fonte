void handleFinal(){
Serial.println("### FINAL FASE ###");

Serial.println(server.arg("coluna1"));

String resultado = "x2";
// -..- ..---

Serial.println(server.arg("answer"));
 if ( (server.arg("answer") == resultado) and logged_in) {
  fase5 = false;
  final_fase = false; 
  win = true;
  bomb_planted = false;
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
      "<div id='textbox'> <div id='titulo-green'>  <font aling='center'> <h1> FINAL </h1></font></div>"
      "<br><h2> Gotcha</h2>"
      "<br>"
      "<br>"
      "<p> The bomb has been defused!</p>"
       "<a href='/admin'> <button> Flag </button> </a>"
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

