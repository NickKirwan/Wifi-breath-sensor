// Arduino code for a Wifi based breath controller

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUDP.h>
#include <OSCMessage.h>
#include <Wire.h>





int status = WL_IDLE_STATUS;
int breath;

//const char* ssid = "your ssid";  //  your network name (SSID)
//const char* pass = "your pass";       // your network password
const char *ssid = "Breathsensor";     //BS SSID

int localPort = 8000;
int destPort = 9000;

IPAddress outIp(192, 168, 4, 2); //default IP, will change with received udp

WiFiUDP Udp;


void setup()
{
  
/*  WiFi.begin(ssid, pass);

  int tries=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tries++;
    if (tries > 30){
      break;
    }
  }*/
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Udp.begin(localPort);
}

void loop(){ 

 
  breath=(analogRead(A0));
   //the message wants an OSC address as first argument
  OSCMessage msg("/data"); //OSC message compilation
 
      msg.add((int32_t)breath);
      Udp.beginPacket(outIp, destPort);
      msg.send(Udp);
      Udp.endPacket();
      msg.empty(); // free space occupied by message
      delay(5);
    }


