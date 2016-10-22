/*
Exemplo b‡sico de conex‹o a Konker Plataform via MQTT, baseado no https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_auth/mqtt_auth.ino. Este exemplo se utiliza das bibliotecas do ESP8266 programado via Arduino IDE (https://github.com/esp8266/Arduino) e a biblioteca PubSubClient que pode ser obtida em: https://github.com/knolleary/pubsubclient/
*/
 
 
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
// Vamos primeiramente conectar o ESP8266 com a rede Wireless (mude os par‰metros abaixo para sua rede).
 
const char* ssid = "thi";
const char* password = "thiago123";
int randomNumber = random(26,30);
 
 
//senha: SzS3YqiDxbsa
 
//Criando a fun‹o de callback
void callback(char* topic, byte* payload, unsigned int length) {
  // Essa fun‹o trata das mensagens que s‹o recebidas no t—pico no qual o Arduino esta inscrito.
}
 
//Criando os objetos de conex‹o com a rede e com o servidor MQTT.
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
 
    //Configurando a conex‹o com o servidor MQTT
    if (client.connect("arduinoClient", "o7faqq827bhr", "SzS3YqiDxbsa")) {
 
    //Subscrevendo no t—pico <t—pico para subscri‹o>
    client.subscribe("sub/o7faqq827bhr/receber");
 
    //Agora vamos publicar uma mensagem no <t—pico para pubica‹o>. Nota: a mensagem deve estar no formato JSON.
    String mensagem = "{\"token\":\"8797RFDE344DS\",\"temperatura\":29,\"id_wearable\":\"00:01\",\"codigocliente\":\"cli1900\"}";
    //mensagem+=String(randomNumber)+"\"}";
 
    mensagem.toCharArray(mensagemC,mensagem.length()+1);
    Serial.println(mensagemC);
    client.publish("pub/o7faqq827bhr/enviar",mensagemC);
 
  }
}
 
void loop()
{
  //Vamos manter o cliente ativo para receber mensagens no t—pico de subscri‹o
  client.loop();
}
