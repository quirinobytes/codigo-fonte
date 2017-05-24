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
  server.sendContent("<html><head></head><body>");
  ShowMenu();
  server.sendContent(
    "<font aling='center'> <h1>WELCOME TO ANDSEC - CTF!!</h1></font>"
    "<p> You have to access the admin page to defuse the bomb, </p>"
    "<p> when you do, you will start a timer that you have to asnwer 3 questions,</p>"
    "<p> to take time past slower, or your time could be expire fast and the bomb exploded</p>"
    );
  
  if (server.client().localIP() == apIP) {
    server.sendContent(String("<p>Now you are connected through the AP: ") + softAP_ssid + "</p>");
  } else {
    server.sendContent(String("<p>Now you are connected through the wifi network: ") + ssid + "</p>");
  }
  login_user=server.arg("login");
  
  server.sendContent(
    "<p> You will need to connect to bomb wifi that that password already been saved. </p>"
    "<p> If you connect to another wifi, you will lost that password, to recover the </p>"
    "<p> password click here <a href='/wifi'> recover bomb password </a>.   </p>"
    "<p> or try login admin pages <a href='/admin'> Remote Control Admin </a>.</p>"
    "<form method='POST' action='admin'><h5>Login:</h5>");
    //server.sendContent(login_user);
    retry = login_user.length();
    if (retry > 0 ) {
        server.sendContent(
          "User: <input type='text' placeholder='"+ login_user +"' name='u'/>"
          "<br/> Password:<input maxlength='8' type='password' placeholder='password' name='p'/>"
          "<br/> <input type='submit' value='Login'/></form>"
          "</body></html>"
        );  
    }
    else{
        server.sendContent(
          "<input type='text' placeholder='user' name='u'/>"
          "<br /><input maxlength='8' type='password' placeholder='password' name='p'/>"
          "<br /><input type='submit' value='Login'/></form>"
          "</body></html>"
        );  
    }
    
    
  server.client().stop(); // Stop is needed because we sent no content length
}

