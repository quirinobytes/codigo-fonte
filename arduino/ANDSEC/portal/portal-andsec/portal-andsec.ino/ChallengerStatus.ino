
void handleChallengerStatus() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.sendContent("<html><head></head><body>");
  ShowMenu();
  server.sendContent(  
    "<font aling='center'> <h1> Admin Page !!! </h1> </font>"
    "<h1>GetBombStatus! </h1><a href='/getbombstatus'> link </a>"
    "<h1>Remote Command Send! </h1><a href='/command'> link </a>"
    "<frameset>  <frame cols='50%' src='\get'> </frameset>"
  );
  server.client().stop(); // Stop is needed because we sent no content length
}
