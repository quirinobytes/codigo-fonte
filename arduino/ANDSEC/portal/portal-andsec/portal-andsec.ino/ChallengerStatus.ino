
void handleChallengerStatus() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.sendContent("<html><head></head><body>");
  ShowMenu();
  server.sendContent(  
    "<font aling='center'> <h1> Challenger Status !!! </h1> </font><br/><br/>"
    "<table cellspacing='0' cellpadding='5' border='1'><tr><th>Id</th>Pontucao <th></th> <th>Timer</th> <th>Fator Tempo</th>  </tr>"
    "<tr><td> 00A1 </td> <td>10</td> <td>05:01:10</td> <td><b>normal</b></td> </tr>"
    "<tr><td> 00B2 </td> <td>20</td> <td>09:01:10</td> <td><b>slower</b></td> </tr>"
    "<tr><td> 00C3 </td> <td>10</td> <td>03:01:10</td> <td><b>normal</b></td> </tr>"
    "<tr><td> 00D4 </td> <td>10</td> <td>23:01:10</td> <td><b>normal</b></td> </tr>"
    "</table>"
    );
  server.client().stop(); // Stop is needed because we sent no content length
}
