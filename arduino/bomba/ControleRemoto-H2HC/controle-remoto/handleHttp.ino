/** Handle root or redirect to captive portal */
void handleRoot() {
  if (captivePortal()) { // If captive portal redirect instead of displaying the page.
    return;
  }
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.sendContent(
    "<html><head></head><body>"
    "<h1>Desarme a Bomba!</h1>"
  );
  if (server.client().localIP() == apIP) {
    server.sendContent(String("<p>Voc&ecirc; est&aacute; nesse site pela AP ") + softAP_ssid + "</p>");
  } else {
    server.sendContent(String("<p>Voc&ecirc; est&aacute; nesse site pelo Rede ") + ssid + "</p>");
  }
  server.sendContent(
    "<p>Configurar uma conex&atilde;o wifi para ativar a bomba remotamente <a href='/wifi'>Config Wifi</a>.</p>"
    "<p>Ver informa&ccedil;&otilde;es para desativar a bomba <a href='/desativar'>Desativar a Bomba</a>.</p>"
     "<p><h2> Ativar </h2> <a href='/bomb'>BOMBA</a>.</p>"
    "</body></html>"
  );
  server.client().stop(); // Stop is needed because we sent no content length
}

/** Redirect to captive portal if we got a request for another domain. Return true in that case so the page handler do not try to handle the request again. */
boolean captivePortal() {
  if (!isIp(server.hostHeader()) && server.hostHeader() != (String(myHostname)+".local")) {
    Serial.print("Request redirected to captive portal");
    server.sendHeader("Location", String("http://") + toStringIp(server.client().localIP()), true);
    server.send ( 302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
    server.client().stop(); // Stop is needed because we sent no content length
    return true;
  }
  return false;
}



/** Wifi config page handler */
void handleWifi() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.sendContent(
    "<html><head></head><body>"
    "<h1>Wifi config</h1>"
  );
  if (server.client().localIP() == apIP) {
    server.sendContent(String("<p>Voc&ecirc; est&aacute; nesse site pelo pr&oacute;AP: ") + softAP_ssid + "</p>");
  } else {
    server.sendContent(String("<p>Voc&ecirc; est&aacute; nesse site pelo Wifi: ") + ssid + "</p>");
  }
  server.sendContent(
    "\r\n<br />"
    "<table><tr><th align='left'>SoftAP config</th></tr>"
  );
  server.sendContent(String() + "<tr><td>SSID " + String(softAP_ssid) + "</td></tr>");
  server.sendContent(String() + "<tr><td>IP " + toStringIp(WiFi.softAPIP()) + "</td></tr>");
  server.sendContent(
    "</table>"
    "\r\n<br />"
    "<table><tr><th align='left'>WLAN config</th></tr>"
  );
  server.sendContent(String() + "<tr><td>SSID " + String(ssid) + "</td></tr>");
  server.sendContent(String() + "<tr><td>IP " + toStringIp(WiFi.localIP()) + "</td></tr>");
  server.sendContent(
    "</table>"
    "\r\n<br />"
    "<table><tr><th align='left'>Lista WLAN (atualize se algum estiver faltando)</th></tr>"
  );
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      server.sendContent(String() + "\r\n<tr><td>SSID " + WiFi.SSID(i) + String((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":" *") + " (" + WiFi.RSSI(i) + ")</td></tr>");
    }
  } else {
    server.sendContent(String() + "<tr><td>WLAN n&atilde;o encontrada</td></tr>");
  }
  server.sendContent(
    "</table>"
    "\r\n<br /><form method='POST' action='wifisave'><h4>Conectar na Rede:</h4>"
    "<input type='text' placeholder='network' name='n'/>"
    "<br /><input type='password' placeholder='password' name='p'/>"
    "<br /><input type='submit' value='Connect/Disconnect'/></form>"
    "<p>Ou voc&eacute pode querer <a href='/'>voltar para home page</a>.</p>"
    "</body></html>"
  );
  server.client().stop(); // Stop is needed because we sent no content length
}


void handleBomb(){
    String buf[30];
    int g = 7;
    
    Serial.println("Armando a bomba");
    Serial.println(g);
    
    server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    server.sendHeader("Pragma", "no-cache");
    server.sendHeader("Expires", "-1");
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
 
    *buf += "<script> function callAjax(url) { var xReq = new XMLHttpRequest(); xReq.open('GET', url , false); xReq.send(null); var serverResponse = xReq.responseText; } </script>" ;   
    *buf += "<h4> Ative a bomba </h4>";    
    *buf += "<p> <a href=\"http://192.168.1.50/?cronometro=1\"><button>1</button></a> ";
    *buf += "- <a href=\"javascript:void(0);\" onclick='callAjax(\"http://192.168.1.50/?cronometro=2\");'><button>2</button></a> ";
    *buf += "- <a href=\"javascript:void(0);\" onclick='callAjax(\"http://192.168.1.50/?cronometro=3\");'><button>3</button></a> ";
    *buf += "- <a href=\"javascript:void(0);\" onclick='callAjax(\"http://192.168.1.50/?cronometro=4\");'><button>4</button></a> ";
    *buf += "- <a href=\"javascript:void(0);\" onclick='callAjax(\"http://192.168.1.50/?cronometro=5\");'><button>5</button></a> ";
    *buf += "- <a href=\"javascript:void(0);\" onclick='callAjax(\"http://192.168.1.50/?cronometro=6\");'><button>6</button></a> ";
    *buf += "- <a href=\"javascript:void(0);\" onclick='callAjax(\"http://192.168.1.50/?cronometro=7\");'><button>7</button></a> ";
    *buf += "- <a href=\"javascript:void(0);\" onclick='callAjax(\"http://192.168.1.50/?cronometro=8\");'><button>8</button></a> ";
    *buf += "- <a href=\"javascript:void(0);\" onclick='callAjax(\"http://192.168.1.50/?cronometro=9\");'><button>9</button></a> ";
    *buf += "- <a href=\"javascript:void(0);\" onclick='callAjax(\"http://192.168.1.50/?cronometro=0\");'><button>0</button></a> ";
   
    *buf += "<form action='.' method='get'> Valor: <input name='cronometro' type='number' maxlenght='4'>  <input type='submit' value='Enviar'> | <a href=\"?cronometro=\"><button>Apagar Display</button></a>  </form> ";
    *buf += "<BR> <a href=\"javascript:void(0);\" onclick='callAjax(\"http://192.168.1.50/?bomba\");'><button>BOMBA</button></a> ";
    *buf += "- <a href=\"javascript:void(0);\" onclick='callAjax(\"http://192.168.1.50/loop\");'><button>LOOP</button></a> ";
    *buf += "<h4>Criado por Rafael Quirino </h4>";
    *buf += "</html>\n";
  
    server.sendContent(*buf);
}
  


/** Handle the WLAN save form and redirect to WLAN config page again */
void handleWifiSave() {
  Serial.println("wifi save");
  server.arg("n").toCharArray(ssid, sizeof(ssid) - 1);
  server.arg("p").toCharArray(password, sizeof(password) - 1);
  server.sendHeader("Location", "wifi", true);
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send ( 302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.client().stop(); // Stop is needed because we sent no content length
  saveCredentials();
  connect = strlen(ssid) > 0; // Request WLAN connect with new credentials if there is a SSID
}

void handleNotFound() {
  if (captivePortal()) { // If captive portal redirect instead of displaying the error page.
    return;
  }
  String message = "Arquivo nao encontrado\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send ( 404, "text/plain", message );
}

