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
 
const char* ssid = "rocknet";
const char* password = "ontherocks";
String buf[30];
 String gatilho;
 
WiFiServer server(80);
 
void setup() {
  Serial.begin(250000);
  delay(10);
  String gatilho;

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
  
  Serial.println("new client=waiting");
  while(!client.available()){
    //para avisar a cada requisicao pisca o vermelho (16) como se fosse o HD trabalhando.
   // Serial.println("SEM REQUISICAO ->> PISCA LUZ");
    digitalWrite(16, 0);
    delay(1);
    digitalWrite(16, 1);
      
  }
    Serial.println("new client=sucess");
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if (req.indexOf("cronometro=") != -1)
   gatilho = req.indexOf("cronometro=");
   gatilho = req[17];
   int g = gatilho.toInt();
   Serial.println("GATILHO:");
   Serial.println(g);

 
  *buf = "";
 
  *buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  *buf += "<h4> Counter Bomb @ H2HC </h4>";
  *buf += "<p> <a href=\"./?cronometro=1\"><button>1</button></a> ";
  *buf += "- <a href=\"./?cronometro=2\"><button>2</button></a> ";
  *buf += "- <a href=\"./?cronometro=3\"><button>3</button></a> ";
  *buf += "- <a href=\"./?cronometro=4\"><button>4</button></a> ";
  *buf += "- <a href=\"./?cronometro=5\"><button>5</button></a> ";
  *buf += "- <a href=\"./?cronometro=6\"><button>6</button></a> ";
  *buf += "- <a href=\"./?cronometro=7\"><button>7</button></a> ";
  *buf += "- <a href=\"./?cronometro=8\"><button>8</button></a> ";
  *buf += "- <a href=\"./?cronometro=9\"><button>9</button></a> ";
  *buf += "- <a href=\"./?cronometro=0\"><button>0</button></a> ";
    
  *buf += "<form action='.' method='get'> Valor: <input name='cronometro' type='number' maxlenght='4'>  <input type='submit' value='Enviar'> | <a href=\"?cronometro=\"><button>Apagar Display</button></a>  </form> ";
  *buf += "<BR> <a href=\"bomba=";
  *buf += g;
  *buf += "\"><button>BOMBA</button></a> ";
  *buf += "- <a href=\"./loop\"><button>LOOP</button></a> ";
  
   
 
  *buf += "<h4>Criado por Rafael Quirino </h4>";
  *buf += "</html>\n";
 
  client.print(*buf);
  client.flush();
  
  if (req.indexOf("cronometro=1") != -1)
    escreve(1);
  else if (req.indexOf("cronometro=2") != -1)
    escreve(2);
  else if (req.indexOf("cronometro=3") != -1)
    escreve(3);
  else if (req.indexOf("cronometro=4") != -1)
    escreve(4);
  else if (req.indexOf("cronometro=5") != -1)
    escreve(5);
  else if (req.indexOf("cronometro=6") != -1)
    escreve(6);
  else if (req.indexOf("cronometro=7") != -1)
    escreve(7);
  else if (req.indexOf("cronometro=8") != -1)
    escreve(8);
  else if (req.indexOf("cronometro=9") != -1)
    escreve(9);
  else if (req.indexOf("cronometro=0") != -1)
    escreve(0);
  else if (req.indexOf("bomba=") != -1){
   gatilho = req[11];
   int g = gatilho.toInt();
   Serial.println("Chamando com");
   Serial.println(g);
   bomba(g);
  }
  else if (req.indexOf("loop") != -1)
    eternity();  
  else if (req.indexOf("cronometro=") != -1)
    zeratudo();
  else {
    Serial.println("invalid request:");
    Serial.println(req);
    client.stop();
  }
  Serial.println("Task Done, connetion closed\n\n");
  client.stop();
}


void escreve(int num){

   switch (num){
    case 1:
            zeratudo();
            digitalWrite(13, 1);//g
            digitalWrite(2, 1);
         break;
    case 2:
            zeratudo();
            digitalWrite(0, 1);
            digitalWrite(2, 1);
            digitalWrite(5, 1);
            digitalWrite(14, 1);
            digitalWrite(12, 1);
         break;
    case 3:
            zeratudo();
            digitalWrite(0, 1);
            digitalWrite(2, 1);
            digitalWrite(5, 1);
            digitalWrite(12, 1);
            digitalWrite(13, 1);
         break;  
    case 4:
            zeratudo();
            digitalWrite(4, 1);
            digitalWrite(5, 1);
            digitalWrite(2, 1);
            digitalWrite(13, 1);
         break;    
     case 5:
            zeratudo();
            digitalWrite(0, 1);
            digitalWrite(4, 1);
            digitalWrite(5, 1);
            digitalWrite(12, 1);
            digitalWrite(13, 1);
         break;       
     case 6:
            zeratudo();
            digitalWrite(0, 1);
            digitalWrite(4, 1);
            digitalWrite(5, 1);
            digitalWrite(12, 1);
            digitalWrite(14, 1);
            digitalWrite(13, 1);
         break;    
     case 7:
            zeratudo();
            digitalWrite(0, 1);
            digitalWrite(2, 1);
            digitalWrite(13, 1);
         break;    
     case 8:
            zeratudo();
            digitalWrite(0, 1);
            digitalWrite(4, 1);
            digitalWrite(2, 1);
            digitalWrite(5, 1);
            digitalWrite(12, 1);
            digitalWrite(14, 1);
            digitalWrite(13, 1);
         break;
    case 9:
            zeratudo();
            digitalWrite(0, 1);
            digitalWrite(2, 1);
            digitalWrite(4, 1);
            digitalWrite(5, 1);
            digitalWrite(12, 1);
            digitalWrite(13, 1);
         break;
             
     case 0:
            zeratudo();
            digitalWrite(0, 1);
            digitalWrite(4, 1);
            digitalWrite(2, 1);
            digitalWrite(12, 1);
            digitalWrite(14, 1);
            digitalWrite(13, 1);
         break;  
                   
   }
}

void bomba(int disparo){
  int c=10,d;
Serial.println("CHAMOU COM");
Serial.println(disparo);

  if (disparo > 0 || disparo == -5)
  { 
      c=disparo;
    
    for (;c>=0;c--){
      escreve(c);
      for (d=0;d<100;d++){
        digitalWrite(16, 1);
       delay(1);
        digitalWrite(16, 0);
       delay(9);
      }
  
    }
  }
  delay(1);
  digitalWrite(16, 0);
}

void  zeratudo(){
  digitalWrite(4, 0);//a 
  digitalWrite(5, 0);//b
  digitalWrite(2, 0);//c
  digitalWrite(0, 0);//d
  digitalWrite(14, 0);//e
  digitalWrite(12, 0);//f
  digitalWrite(13, 0);//g
}

void eternity(){
  int c=0;
  while(true){
    escreve(c);
    c++;
    if (c==10) c=0;
    delay(350);
    }
   
  }
