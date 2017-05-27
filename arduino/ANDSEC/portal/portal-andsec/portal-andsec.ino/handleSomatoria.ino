void handleSomatoria(){



 if ( (server.arg("answer") == "567") and logged_in) {

  fase1 = true;
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.sendContent("<html><head></head><body>");
  ShowMenu();
  pontos_atual+=200;
  server.sendContent("<h2> Congratulations, you pass.</h2> <br><br> Now, get your serial number.");

  Serial.print(
      " "
      "Try to use some matematics to may help you, and defuse the bomb."
      "could kirshoff or ohms help you?"
      ""
      ""
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

