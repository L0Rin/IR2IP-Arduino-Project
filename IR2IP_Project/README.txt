  /******************************************************************************************/
 /                                         README                                           /
/******************************************************************************************/

  /******************************************************************************************/
 /                           Project purpose and description                                /
/******************************************************************************************/

	The purpose of the project is to read commands from an TV Remote Control via an IR 
Sensor and send them via Ethernet protocol to another device (or another Arduino board).
	The project is based on "Arduino Ethernet" (the version who include PoE module) but 
the software is compatible with any Arduino board, with an extra Ethernet shield.

	Attention! If you use the software on Arduino board + Ethernet shield you need to make few
adjustments regarding the communication PINs between board and shield.

	Components:
		- Arduino Ethernet
		- FTDI Module - for programming the board
		- IR Sensor
		- LED's (optional)
		- Power adapter (it is strongly recommended to provide enough power for the Ethernet module)
		- Any IR remote
		- Jumper Cables (optional)

   /******************************************************************************************/
  /                                       Implementation                                     /
 /******************************************************************************************/
/******************************************************************************************/

	Hardware setup:
		IR Sensor 
			PIN 1 - DATA  (to PIN11 - Arduino) 
			PIN 2 - GND   (to GND - Arduino)
			PIN 3 - VCC   (to +5V - Arduino)
			
	Software setup:
	
		Library included
			SPI.h
			Ethernet.h
			IRremote.h
			
		Ethernet setup
			To establish an Ethernet connection you need to configure the following:
				- byte mac[]  	 - Arduino board MAC
				- IPAddress ip() - Set the static IP address to use if the DHCP fails to assign
				- char server[]	 - Declare the server address of the remote device
				
				Optionally you can configure the following:
				- IPAddress subnet();
				- IPAddress gateway();
				- IPAddress dnServer();
				
		Ethernet functions used
			- EthernetClient  	- Initialize the Ethernet client library with the IP 
								  address and port of the server
                                  that you want to connect to (port 80 is default for HTTP):
			- Ethernet.begin 	- Initializes the ethernet library and network setting
			- client.connect	- Connects to a specified IP address and port. The return value 
								  indicates success or failure. Also supports DNS lookups when 
								  using a domain name.
			- client.print
			- client.println    - Print data, followed by a carriage return and newline, to the server 
			                      a client is connected to. Prints numbers as a sequence of digits, each 
								  an ASCII character (e.g. the number 123 is sent as the three characters 
								  '1', '2', '3').

	Software functions used for IR:
	
		IRrecv irrecv(IRpin);   	Call the function for receiving IR
		decode_results results; 	Results returned from the decoder
		irrecv.enableIRIn();  		Enable the receiver
		irrecv.decode(&results);	Results returned from the decoder
		irrecv.resume(); 			Resume to read the next value

  /******************************************************************************************/
 /                                           Web Server                                     /
/******************************************************************************************/





  /******************************************************************************************/
 /                                     Future implementations                               /
/******************************************************************************************/

	We intend to implement some new futures like signalling with LED the status for the reading,
sending and communication and others.

  /******************************************************************************************/
 /                                     Thank you for reading!                               /
/******************************************************************************************/