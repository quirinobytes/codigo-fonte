
/* URL:http://bombserver/getbombstatus */ 
void handleBombStatus() {
  String resp = "";
  Serial.println("#REQUEST GET: /getbombstatus");
  Serial.println(millis());
  RestClient client  = RestClient("192.168.4.1",80);
  int statusCode = client.get("/bomb.txt", &resp);
  Serial.print("Status code from server: ");
  Serial.println(statusCode);
  Serial.print("Response body from server: http://192.168.4.1/getbombstatus = ");
  Serial.println(resp);
  server.sendContent(
        "<script>"
        "window.setInterval('reloadFrame();', 10000);"
        "function reloadFrame()"
        "{"
        "  document.location.reload();  "
        "}"
        "</script>"
        ) ;
  server.sendContent(String("<body> getting your time from server... wait: ")  );
  server.sendContent(resp);
  server.sendContent("<p> the rest time: <b>");

  //conta o tempo e mostra na getbombstatus
  server.sendContent("Tempo acabando hahhh");
  Serial.println("Zazzzzz");
  server.sendContent("</b> seconds </p> </body></html>");
  
  server.client().stop(); // Stop is needed because we sent no content length
}
