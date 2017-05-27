void handleManual(){

    server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    server.sendHeader("Pragma", "no-cache");
    server.sendHeader("Expires", "-1");
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.sendContent("<html><head></head><body>");
    ShowMenu();
    server.sendContent(
    "<h2> Bomb Manual </h2>"
    " This manual cover how arm and desarm the bomb."       
    );
    server.sendContent("</body>");

    
  server.client().stop(); // Stop is needed because we sent no content length
}

