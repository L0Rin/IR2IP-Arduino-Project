/**********************************************************************************************
Project name: IR2IP
Students: Lorin - Gabriel COJOCARIU
          Muhammad AMMAD
RCS - MASTER
CES - Lab

Description
An arduino with an infrared LED should be used to receive IR commands from remotes 
of consumer devices and forward them via an ethernet-port to a webserver as a GET request 
**********************************************************************************************/

/*********************************************************************************************
                                         LIBRARY                                          
*********************************************************************************************/
 
#include <SPI.h>
#include <Ethernet.h>
#include <IRremote.h>

/*********************************************************************************************
                                        IR setup / PIN / functions                        
*********************************************************************************************/

int IRpin = 11;
IRrecv irrecv(IRpin);
decode_results results;

/*********************************************************************************************
                                        Ethernet setup                                     
*********************************************************************************************/

byte mac[] = {  0x90, 0xA2, 0xDA, 0x00, 0xEE, 0xF8 }; // Device MAC address
char server[] = "www.mobieshot.com";                 // Name address for the server resolved by DNS

IPAddress ip(192, 168, 0, 201);      // Set the static IP address to use if the DHCP fails to assign
EthernetClient client;              // Initialize the Ethernet client library
                                   // with the IP address and port of the server
                                  // that you want to connect to (port 80 is default for HTTP):

/*********************************************************************************************
                                        Arduino setup                                      
*********************************************************************************************/

void setup() {
  Serial.begin(9600);                      // Open serial communications and wait for port to open:
  Serial.println("Boot sequence - DONE"); //announce that Arduino done the Boot sequence
  irrecv.enableIRIn();                   // Start the receiver
  while (!Serial) {
    ;                                  // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip); // try to congifure using IP address instead of DHCP
  }
  
  delay(5000);             // give the Ethernet shield a second to initialize:
  Serial.println("connecting...");

  
  if (client.connect(server, 80)) {
    Serial.println("connected");           // if you get a connection, report back via serial
    delay(3000);                          // give some time to write on console smooth
    Serial.print("IP = ");               // print on console what is the Device IP
    Serial.println(Ethernet.localIP()); // print on console what is the Device IP
  }
  else {
        Serial.println("connection failed"); // if you didn't get a connection to the server:
  }
}


/*********************************************************************************************
                                        Main loop                                          
*********************************************************************************************/

void loop()
{
  if (irrecv.decode(&results)) {      //if you receive a code and decoded
    String Code;                     //store the value and 
    Code = String(results.value);   //convert it into string to send it via HTTP incorporated in URL
    client.println("GET /api/mobieshot/arduino.php?code=" + Code + " HTTP/1.1"); //send the GET command to server
    client.println("Host: www.mobieshot.com");
    Code = "";
    //  client.println("Connection: close");
    client.println();
    //    Serial.println(Code);
    irrecv.resume();            //resume to reading the next value from remote control
  }
          /**********************************************************
            /!\ This part is only for demonstrate that the server 
                            receive the command                                          
          ***********************************************************/
  if (client.available()) {     
    char c = client.read();   //reading the server's response for our request
    Serial.print(c);         //print the message on Console
    // Receive the next
  }
           /**********************************************************
            /!\ End Console printing part                                     
          ***********************************************************/

  if (!client.connected()) {   // if the server's disconnected, stop the client:
    //  Serial.println();
    //  Serial.println("disconnecting.");
    // client.stop();

  }
}