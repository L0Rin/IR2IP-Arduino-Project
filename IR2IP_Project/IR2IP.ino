/*
Project: IR2IP
Team: Lorin - Gabriel COJOCARIU
      Muhammad Ammad Khan

An arduino with an infrared LED should be used to receive IR commands from remotes of consumer devices and forward them via an ethernet-port to a webserver as a GET request e.g.

http://<ip-of-pc>/ir-command-received/tv-samsung-power-on
http://<ip-of-pc>/ir-command-received/rc5-code-11100000010000

*/
#include <IRremote.h>
#include <SPI.h>
#include <Ethernet.h>
 

int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;
 
// Network settings for Arduino
byte mac[] = {  0x90, 0xA2, 0xDA, 0x00, 0xEE, 0xF8 }; //the media access control (ethernet hardware) address for the shield:
//byte ip[] = { 192,168,1,200 };  //the IP addess of the Arduino board
//byte subnet[] = {255,255,255,0}; //the IP for Subnet of network
byte gateway[] = { 192,168,1,1 };//the IP for Gateway

 
// IP of the Target Web server or Arduino with IR emitter
IPAddress server(198,57,247,197);
char serverName[] ="www.mobleshot.com";
EthernetClient client;

unsigned int rawCodes[RAWBUF]; // The durations if raw
int codeLen; // The length of the code
//Get the infrared codes from remote

void storeCode(decode_results *results) {
  int count = results->rawlen;
  Serial.println("Received code");
  codeLen = results->rawlen - 1;
    for (int i = 1; i <= codeLen; i++) {
      if (i % 2) {
        // Mark
        rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      } 
        
      else {
        // Space
        rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      Serial.print(rawCodes[i - 1], DEC);
    }
    Serial.println("");
}

 
void setup()
{
  // For debug
  Serial.begin(9600);
  // Start ethernet
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    while(true);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
  //Ethernet.begin(mac, ip, subnet, gateway);
  //Serial.println("Initialised");
}

//sending the raw IR code over the ether net
void connect(){
// if you get a connection, report back via serial:
  client.connect(server, 80);
  Serial.println("CONNECTED");
  delay(1000);
} 
void sendIR()
{
   
    // Send over HTTP server
    if (client.connect(server, 80))
    {
      client.print("GET /api/mobieshot/arduino.php?code=test HTTP/1.1");
      
      //for (int i = 0; i < codeLen; i++) {
       // client.print(rawCodes[i]);
        //}
        
      //client.println("HTTP/1.0");
      //Serial.println("HTTP/1.0");
      client.println("Host: 198.57.247.197"); //???
      Serial.println("Host: 192.254.233.90");
      client.println("Connection: close");
      Serial.println("Connection: close");
      client.println();;
      client.stop();
    } 
    else
    {
       Serial.println("not connecvt");
    }
  
}
 
int k=0;
void loop()
{
  //if (irrecv.decode(&results))
  //{
    //storeCode(&results);
    if (k==0)
    {
    sendIR();
    k++;}
    //irrecv.resume(); // Receive the next value
  //}
}
