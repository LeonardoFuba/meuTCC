//forum
/*slave*/

#include "SPI.h"
#include "pins_arduino.h"

int pin_miso = 19;
int pin_mosi = 23;
int pin_sck = 18;
int pin_ss = 5;
//int pin_ss = 10;
//int pin_miso = 11;

byte b = 0;

void setup(){

	//SETUP PINS
   	pinMode(pin_miso,OUTPUT);
   	pinMode(pin_mosi,INPUT);
		pinMode(pin_sck,INPUT);
   	pinMode(pin_ss,INPUT);

    //SETUP SERIAL
   	Serial.begin(115200);

   //SETUP SPI SLAVE
   	SPCR = 0b11000000;	// turn on SPI in slave mode
   	SPCR |= bit(SPIE);	// turn on interrupts
}


// Interrupt Service Routine (ISR)
ISR(SPI_STC_vect){

	byte data = SPDR;	//MOSI data
	switch(b){

		case 0: //vazio
			b = data;
			SPDR = 0;
			break;

		case 'a':
			SPDR = data + 15;
			break;
   }
}

void loop(){
     if(digitalRead(pin_ss)==HIGH)
     b = 0;
   }
