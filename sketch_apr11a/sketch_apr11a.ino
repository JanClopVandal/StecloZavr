#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "TP-LINK_5A50";
const char* password = "84913944";

IPAddress staticIP(192,168,0,11);
IPAddress gateway(192,168,0,9);
IPAddress subnet(255,255,255,0);


WiFiUDP Udp;
IPAddress localUdpIP(192,168,0,100);
unsigned int localUdpPort = 9100;  // local port to listen on

char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back

const int analogInPin = A0;
int sensorValue = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s\n", ssid);
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}


void loop()
{  
  int sensorValue = analogRead(analogInPin);

  String strSensorValue = String(sensorValue);
  int arrayLen = strSensorValue.length() + 1; 
  char stringSensorValue[arrayLen];
  strSensorValue.toCharArray(stringSensorValue, arrayLen);
  
  int Sucsesfull = Udp.beginPacket(localUdpIP, localUdpPort);
  if(Sucsesfull == 1){
      
      Udp.write(stringSensorValue);
      Udp.endPacket();
      Serial.println(stringSensorValue);
  }

  delay(30);
}
