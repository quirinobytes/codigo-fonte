void handleGet() {
  Serial.println("#GET: /get");
//  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
//  server.sendHeader("Pragma", "no-cache");
//  server.sendHeader("Expires", "-1");
//  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.setContentLength(4);
//server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
//server.sendContent(String("<html><head></head><body>")  );
  server.sendContent(String("5000"));
//server.sendContent(String("</body></html>")  );
//server.client().stop(); // Stop is needed because we sent no content length
}

/* URL:http://bombserver/get */ 
void handleGetBombStatus() {
  Serial.println("#GET: /getbombstatus");
  String resp;
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.

  RestClient client  = RestClient("192.168.10.1",80);
  String response;
  resp = "";
  int statusCode = client.get("/get", &resp);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: http://192.168.10.1/get = ");
  Serial.println(resp);
  server.sendContent(String("<html><head></head>") ) ;
  ShowMenu();
  server.sendContent(String("<body>Status Bomb=")  );
  server.sendContent(resp);
  server.sendContent(String("</body></html>")  );
  server.client().stop(); // Stop is needed because we sent no content length
}

