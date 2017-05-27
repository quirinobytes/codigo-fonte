void handleTips(){
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.sendContent("<html><head></head><body>");
  ShowMenu();
  server.sendContent(
      "<h2> Tips </h2>"
      "<br><br><p>You have to plant the bomb to start the game.</p>"
      "<p>Try to answer the questions to win the bonus: slower count down.</p>"
      "<p>So read the manual and go to defuse the bomb.</p>"
  );
  
  server.client().stop(); // Stop is needed because we sent no content length
}

