/*
Exemplo b�sico de conex�o a Konker Plataform via MQTT, baseado no https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_auth/mqtt_auth.ino. Este exemplo se utiliza das bibliotecas do ESP8266 programado via Arduino IDE (https://github.com/esp8266/Arduino) e a biblioteca PubSubClient que pode ser obtida em: https://github.com/knolleary/pubsubclient/
*/
 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
// Vamos primeiramente conectar o ESP8266 com a rede Wireless (mude os parâmetros abaixo para sua rede).
 
const char* ssid = "rocknet";
const char* password = "ontherocks";
int randomNumber =0;
 
 
//senha: SzS3YqiDxbsa
 
//Criando a função de callback
void callback(char* topic, byte* payload, unsigned int length) {
  // Essa função trata das mensagens que são recebidas no tópico no qual o Arduino esta inscrito.
}
 
//Criando os objetos de conexão com a rede e com o servidor MQTT.
WiFiClient espClient;
PubSubClient client("mqtt.hackathon.konkerlabs.net", 1883, callback, espClient);
ADC_MODE(ADC_VCC);
char mensagemC[100];
 
void setup()
{
 
  //Conectando na Rede
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
      }
 
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("O numero randomico eh = ");
    Serial.println(randomNumber);
 
    //Configurando a conexão com o servidor MQTT
    if (client.connect("arduinoClient", "o7faqq827bhr", "SzS3YqiDxbsa")) {
 
    //Subscrevendo no tópico <tópico para subscrição>
    client.subscribe("sub/o7faqq827bhr/receber");
 
    //Agora vamos publicar uma mensagem no <tópico para pubicação>. Nota: a mensagem deve estar no formato JSON.
    String mensagem = "{\"token\":\"8797RFDE344DS\",\"temperatura\":29,\"id_wearable\":\"00:01\",\"codigocliente\":\"cli1900\"}";
    //mensagem+=String(randomNumber)+"\"}";
 
    mensagem.toCharArray(mensagemC,mensagem.length()+1);
    Serial.println(mensagemC);
    client.publish("pub/o7faqq827bhr/enviar",mensagemC);


 /*if you have added all the resistors, and you call ESP.restart(); the bord will reboot to the "setup".
keep in mind if you connect other sensors / hardware the GPIO0 need to be HIGH and GPIO15 need to be LOW when you call ESP.restart();*/
  // prepare GPIO4
  
  //PINO-1UP
  pinMode(3, OUTPUT);
  //PINO2UP
  pinMode(13, OUTPUT);
  //PINO4UP
  pinMode(14, OUTPUT);
  //PINO-8UP
  pinMode(4, OUTPUT);
  //PINO-16UP
  pinMode(0, OUTPUT);
  
  //PINO2DOWN
  pinMode(15, OUTPUT);
  //PINO4DONW
  pinMode(12, OUTPUT); 
  //PINO8DONW
  pinMode(2, OUTPUT);
  //PINO16DONW
  pinMode(5, OUTPUT);
  //PINO32DOWN
  pinMode(16, OUTPUT);


  //APARENTEMENTE NENHUM
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(17, OUTPUT);



  /*<----------------
  //PINO-1DONN (DA PAU ESSA ZICA -> LIGOU PARA A FUNCAO LOOP)
  //pinMode(1, OUTPUT);
  //software board restart -> Se ligar fica dando => Wdt Reset
  //pinMode(6, OUTPUT);]
  //pinMode(7, OUTPUT);
  // pinMode(9, OUTPUT);
  // pinMode(8, OUTPUT); tirar duvida depois
  //pinMode(11, OUTPUT);
  -------------------->*/
  }
}
 
void pisca(){
  digitalWrite(15, 1);
  digitalWrite(12, 1);
  digitalWrite(2, 1);
  digitalWrite(5, 1);
  digitalWrite(16, 1);
  digitalWrite(0, 1);
  digitalWrite(4, 1);
  digitalWrite(14, 1);
  digitalWrite(13, 1);
  digitalWrite(3, 1);
  delay(100);
  digitalWrite(15, 0);
  digitalWrite(12, 0);
  digitalWrite(2, 0);
  digitalWrite(5, 0);
  digitalWrite(16, 0);
  digitalWrite(13, 0);
  digitalWrite(3, 0);
  digitalWrite(14, 0);
  digitalWrite(0, 0);
  digitalWrite(4, 0);
  delay(30);
  }

void girar(int tempo){  
  int s=tempo*tempo;
  digitalWrite(15, 1);
  delay(s+20);
  digitalWrite(15, 0);
  delay(s);

  digitalWrite(12, 1);
  delay(s+20);
  digitalWrite(12, 0);
  delay(s);

  digitalWrite(2, 1);
  delay(s+20);
  digitalWrite(2, 0);
  delay(s);

  digitalWrite(5, 1);
  delay(s+20);
  digitalWrite(5, 0);
  delay(s);

  digitalWrite(16, 1);
  delay(s+20);
  digitalWrite(16, 0);
  delay(s);

  digitalWrite(0, 1);
  delay(s+20);
  digitalWrite(0, 0);
  delay(s);

  digitalWrite(4, 1);
  delay(s+20);
  digitalWrite(4, 0);
  delay(s);

  digitalWrite(14, 1);
  delay(s+20);
  digitalWrite(14, 0);
  delay(s);
  
  digitalWrite(13, 1);
  delay(s+20);
  digitalWrite(13, 0);
  delay(s);
  
  digitalWrite(3, 1);
  delay(s+20);
  digitalWrite(3, 0);
  delay(s);
}


void loop()
{
  //Vamos manter o cliente ativo para receber mensagens no topico de subscricao
  // client.loop();

  randomNumber = random(1,50);
  Serial.println(randomNumber);

  for (int c=0;c<12;c++)
    girar(c);
  pisca();
  pisca();
  pisca();
}

