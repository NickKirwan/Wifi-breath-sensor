// This program converts UDP OSC messages into SLIP Serial OSC messages on the ESP8266 wifi board
// At the moment there is no OSC bundle support, not sure I need it at the moment

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUDP.h>
#include <OSCMessage.h>
#include <Wire.h>





int status = WL_IDLE_STATUS;
int breath;

//const char* ssid = "UMI SUPER";  //  your network name (SSID)
//const char* pass = "miles500";       // your network password
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

