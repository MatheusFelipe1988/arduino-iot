#include <WiFiEsp.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleShieldEsp8266.h>

#define rele 2
#define ESP8266_BAUD 9600

SoftwareSerial Serial1(6, 7); //pinos que ira colocar no arduino para emular 6 rx e 7 tx

char auth[] = "YourAuthToken";

char ssid[] = "NET_2GE9F4EB";
char pass[] = "E2E9F4EB";

int status = WL_IDLE_STATUS;

//WiFiEspServer server(80);
ESP8266 wifi(&EspSerial);

RingBuffer buf(8);

int statusled = LOW;

void setup() {

EspSerial.begin(ESP8266_BAUD);
delay(10);
pinMode(LED_BUILTIN, OUTPUT); //definindo pino para saida que é o pino 13
Blynk.begin(auth, wifi, ssid, pass); //paramentros para comunicar o blynk
digitalWrite(LED_BUILTIN, LOW);// pino 13 inicia off
Serial.begin(9600);// inicializa o serial
Serial1.begin(9600); //inicia o modulo
WiFi.init(&Serial1);// iniciando a comunicação

if(WiFi.status() == WL_NO_SHIELD){
  while(true);
}
//while(staus != WL_CONNECTED){
 // status = WiFi.begin(ssid, pass);
//}
server.begin();
}

void loop() {
WiFiEspClient client = server.avaliable();

  if(client){
  buf.init();
    while(client.connected()){
      if(client.avaliable()){
      char c = client.read();
      buf.push(c);

        if(buf.endsWith("\r\n\r\n")){
          sendHttpResponse(client);
          break;
        }
        if(buf.endsWith("GET /H"){
          digitalWrite(LED_BUILTIN, HIGH);
          statusLed = 1;
          }
        else{
        if(buf.endsWith("GET /L")){
          digitalWrite(LED_BUILTIN, LOW);
          statusLed = 0;
        }
       }
      }
    }
    client.stop();
  }
}
void loop(){
  Blynk.run();//inicia o app
  timer.run();//inicia o tempo
}

/*
void sendHttpResponse(WiFIEspClient client){
client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html"); 
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>Lampada IoT Arduino</title>");
  client.println("</head>");
  

  client.println("<body>");
  client.println("<p style='line-height:2'><font>Ligando e desligando a lampada inteligente por WiFi e com Arduino</font></p>");
  client.println("<font>ESTADO ATUAL DO LED</font>");

  if(statusLed == HIGH){
    client.println("<p style='line-height:0'><font color='green'>LIGADO</font></p>");
    client.println("<a href=\"/L\">APAGAR</a>");
  }else{
    if(statusLed == LOW){
      client.println("<p style='line-height:0'><font color='red'>DESLIGADO</font></p>");
      client.println("<a href=\"/H\">ACENDER</a>");
    }
  }
  client.println("<hr />");
  client.println("<hr />");
  client.println("</body>");
  client.println("</html>");
  delay(1)
  }
  */
