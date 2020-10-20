//forum
/*master*/

#include "SPI.h"
#include "pin_arduino.h"

int pin_miso = 19;
int pin_mosi = 23;
int pin_sck = 18;
int pin_ss = 5;
//int pin_ss = 10;




void setup(){

	//SETUP PINS
	pinMode(pin_miso,INPUT);
	pinMode(pin_mosi,OUTPUT);
	pinMode(pin_sck,OUTPUT);
   	pinMode(pin_ss,OUTPUT);

   //SETUP SERIAL
   	Serial.begin(115200);
   	Serial.println();

   //SETUP SPI MASTER
    digitalWrite(pin_ss,HIGH);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);
 }

// Loop Routine
void loop(){

	byte a,b,c;
	
	digitalWrite(pin_ss,LOW);
	
		SPI.transfer('a');

		a = SPI.transfer(17);
		delayMicroseconds(20);

		b =  SPI.transfer(33);
		delayMicroseconds(20);

		c = SPI.transfer(0);
		delayMicroseconds(20);
	
	digitalWrite(pin_ss,HIGH);

	Serial.println(a,DEC);
	Serial.println(b,DEC);
	Serial.println(c,DEC);
	delay(1000);
}
