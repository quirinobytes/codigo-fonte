/** Handle root or redirect to captive portal */
void handleRoot() {
  String loginerror;
  if (captivePortal()) { // If caprive portal redirect instead of displaying the page.
    return;
  }
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.sendContent("<html><head></head><body>");
  ShowMenu();
  server.sendContent("<font aling='center'> <h1>WELCOME TO ANDSEC - CTF!!</h1></font>");
  if (server.client().localIP() == apIP) {
    server.sendContent(String("<p>You are connected through the AP: ") + softAP_ssid + "</p>");
  } else {
    server.sendContent(String("<p>You are connected through the wifi network: ") + ssid + "</p>");
  }
  loginerror=server.arg("login");
  server.sendContent(
    "<p>You may want to <a href='/wifi'>config the wifi connection</a>.</p>"
    "<p>You try to login into admin pages <a href='/admin'>try access admin page</a>.</p>"
    "<form method='POST' action='admin'><h5>Login:</h5>");
  server.sendContent(loginerror);
  server.sendContent(
    "<input type='text' placeholder='user' name='n'/>"
    "<br /><input maxlength='8' type='password' placeholder='password' name='p'/>"
    "<br /><input type='submit' value='Login'/></form>"
    "</body></html>"
  );
  server.client().stop(); // Stop is needed because we sent no content length
}

