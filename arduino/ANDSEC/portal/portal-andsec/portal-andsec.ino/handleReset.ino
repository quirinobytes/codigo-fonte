void handleReset(){
   server.sendHeader("Location", String("http://") + toStringIp(server.client().localIP()), true);
   server.send ( 302, "text/plain", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves.
   server.client().stop(); // Stop is needed because we sent no content length
   ESP.reset();
}
