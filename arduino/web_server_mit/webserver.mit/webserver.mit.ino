/*The MIT License (MIT)
Copyright (c) 2015 Pedro Minatel
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
 
#include <ESP8266WiFi.h>
 
const char* ssid = "m5";
const char* password = "ontherocks";
 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO4
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);
  pinMode(5, OUTPUT);
  digitalWrite(5, 0);
  pinMode(0, OUTPUT);
  digitalWrite(0, 0);
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);
  pinMode(12, OUTPUT);
  digitalWrite(12, 0);
  pinMode(13, OUTPUT);
  digitalWrite(13, 0);
 
  // prepare GPIO16 - O LED vermelho, interno.
  pinMode(16, OUTPUT);
  digitalWrite(16, 1);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  Serial.println("new client");
  while(!client.available()){
    //para avisar a cada requisicao pisca o vermelho (16) como se fosse o HD trabalhando.
    Serial.println("REQUISICAO CHEGOU ->> PISCA LUZ");
    digitalWrite(16, 0);
    delay(1);
    digitalWrite(16, 1);
      
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
 
  String buf = "";
 
  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  buf += "<h4> Quirino Web Server (ESP8266 model)</h4>";
  buf += "<p>LED A <a href=\"?function=led4_on\"><button>ON</button></a> <a href=\"?function=led4_off\"><button>OFF</button></a></p>";
  buf += "<p>LED B <a href=\"?function=led5_on\"><button>ON</button></a> <a href=\"?function=led5_off\"><button>OFF</button></a></p>";
  buf += "<p>LED C <a href=\"?function=led6_on\"><button>ON</button></a> <a href=\"?function=led6_off\"><button>OFF</button></a></p>";
  buf += "<p>LED D <a href=\"?function=led7_on\"><button>ON</button></a> <a href=\"?function=led7_off\"><button>OFF</button></a></p>";
  buf += "<p>LED E <a href=\"?function=led8_on\"><button>ON</button></a> <a href=\"?function=led8_off\"><button>OFF</button></a></p>";
  buf += "<p>LED F <a href=\"?function=led9_on\"><button>ON</button></a> <a href=\"?function=led9_off\"><button>OFF</button></a></p>";
  buf += "<p>LED G <a href=\"?function=led10_on\"><button>ON</button></a> <a href=\"?function=led10_off\"><button>OFF</button></a></p>";
  buf += "<p> NOTA <a href=\"?function=led11_on\"><button>ON</button></a> <a href=\"?function=led11_off\"><button>OFF</button></a></p>";

  
  if (req.indexOf("led4_on") != -1)
    buf += "<table bgcolor=\"#00FF00\"> ";
    else
    if (req.indexOf("led4_off") != -1)
    buf += "<table bgcolor=\"#FF0000\"> ";
    else
    buf += "<table> ";
    
  buf += "<tr><td> LED4 </td></tr>" ;
  buf += "</table><br>" ;
  
  if (req.indexOf("led5_on") != -1)
    buf += "<table bgcolor=\"#00FF00\"> ";
    else
    if (req.indexOf("led5_off") != -1)
    buf += "<table bgcolor=\"#FF0000\"> ";
    else
    buf += "<table> ";
    
  buf += "<tr><td> LED5 </td></tr>" ;
  buf += "</table>" ;

  if (req.indexOf("led6_on") != -1)
    buf += "<table bgcolor=\"#00FF00\"> ";
    else
    if (req.indexOf("led6_off") != -1)
    buf += "<table bgcolor=\"#FF0000\"> ";
    else
    buf += "<table> ";
    
  buf += "<tr><td> LED6 </td></tr>" ;
  buf += "</table>" ;

  if (req.indexOf("led7_on") != -1)
    buf += "<table bgcolor=\"#00FF00\"> ";
    else
    if (req.indexOf("led7_off") != -1)
    buf += "<table bgcolor=\"#FF0000\"> ";
    else
    buf += "<table> ";
    
  buf += "<tr><td> LED7 </td></tr>" ;
  buf += "</table>" ;

  if (req.indexOf("led8_on") != -1)
    buf += "<table bgcolor=\"#00FF00\"> ";
    else
    if (req.indexOf("led8_off") != -1)
    buf += "<table bgcolor=\"#FF0000\"> ";
    else
    buf += "<table> ";
    
  buf += "<tr><td> LED8 </td></tr>" ;
  buf += "</table>" ;
  
  if (req.indexOf("led9_on") != -1)
    buf += "<table bgcolor=\"#00FF00\"> ";
    else
    if (req.indexOf("led9_off") != -1)
    buf += "<table bgcolor=\"#FF0000\"> ";
    else
    buf += "<table> ";
    
  buf += "<tr><td> LED9 </td></tr>" ;
  buf += "</table>" ;

 
  if (req.indexOf("led10_on") != -1)
    buf += "<table bgcolor=\"#00FF00\"> ";
    else
    if (req.indexOf("led10_off") != -1)
    buf += "<table bgcolor=\"#FF0000\"> ";
    else
    buf += "<table> ";
    
  buf += "<tr><td> LED10 </td></tr>" ;
  buf += "</table>" ;

  if (req.indexOf("led11_on") != -1)
    buf += "<table bgcolor=\"#00FF00\"> ";
    else
    if (req.indexOf("led11_off") != -1)
    buf += "<table bgcolor=\"#FF0000\"> ";
    else
    buf += "<table> ";
    
  buf += "<tr><td> NOTA </td></tr>" ;
  buf += "</table>" ;

 //########
  buf += "<h4>Criado por Rafael Quirino ®</h4>";
  buf += "</html>\n";
 
  client.print(buf);
  client.flush();
  
  if (req.indexOf("led5_on") != -1)
    digitalWrite(5, 1);
  else if (req.indexOf("led5_off") != -1)
    digitalWrite(5, 0);
  else if (req.indexOf("led4_on") != -1)
    digitalWrite(4, 1);
  else if (req.indexOf("led4_off") != -1)
    digitalWrite(4, 0);
  else if (req.indexOf("led6_on") != -1)
    digitalWrite(2, 1);
  else if (req.indexOf("led6_off") != -1)
    digitalWrite(2, 0);
  else if (req.indexOf("led7_on") != -1)
    digitalWrite(0, 1);
  else if (req.indexOf("led7_off") != -1)
    digitalWrite(0, 0);
  else if (req.indexOf("led8_on") != -1)
    digitalWrite(14, 1);
  else if (req.indexOf("led8_off") != -1)
    digitalWrite(14, 0);
  else if (req.indexOf("led9_on") != -1)
    digitalWrite(12, 1);
  else if (req.indexOf("led9_off") != -1)
    digitalWrite(12, 0);
  else if (req.indexOf("led10_on") != -1)
    digitalWrite(13, 1);
  else if (req.indexOf("led10_off") != -1)
    digitalWrite(13, 0);
  else if (req.indexOf("led11_on") != -1)
    escreve(9);
  else if (req.indexOf("led11_off") != -1)
    zeratudo();
      
  else {
    Serial.println("invalid request:");
    Serial.println(req);
    //client.stop();
  }
  Serial.println("Task Done, connetion closed\n\n");
  client.stop();
}


void escreve(int num){

   switch (num){
    case 9:
          zeratudo();
          digitalWrite(0, 1);
          digitalWrite(2, 1);
          digitalWrite(4, 1);
          digitalWrite(5, 1);
          digitalWrite(12, 1);
          digitalWrite(13, 1);
         break;

    case 2:
         break;
             
   }
 
}

void  zeratudo(){
  digitalWrite(0, 0);
  digitalWrite(2, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
  digitalWrite(14, 0);
  
  
  }

