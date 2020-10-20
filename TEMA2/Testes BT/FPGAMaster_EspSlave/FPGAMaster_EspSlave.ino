//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include <string.h>
#include <SPI.h>

static const int spiClk = 1000000; // 1 MHz

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run 'make menuconfig' to and enable it
#endif

/*Bluetooth objects*/
BluetoothSerial SerialBT;

/*SPI objects*/
SPIClass * vspi = NULL;
//SPIClass * hspi = NULL;

void setup() {
  /*initialise two instances of the SPIClass attached to VSPI and HSPI respectively*/
  vspi = new SPIClass(VSPI);
  //hspi = new SPIClass(HSPI);

  Serial.begin(115200);//monitoramento
  SerialBT.begin("ESP32-SerialBT"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  /*initialise vspi with default pins*/
  /*SCLK = 18, MISO = 19, MOSI = 23, SS = 5*/
  vspi->begin();
  //hspi->begin(14, 12, 13, 15);

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= bit(SPE);

  // turn on interrupts
  SPCR |= bit(SPIE);

} // end of setup

volatile char buf [20] = "Hello, world!";
volatile int pos;
volatile bool active;

// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;

  if (c == 1)  // starting new sequence?
    {
    active = true;
    pos = 0;
    SPDR = buf [pos++];   // send first byte
    return;
    }

  if (!active)
    {
    SPDR = 0;
    return;
    }

  SPDR = buf [pos];
  if (buf [pos] == 0 || ++pos >= sizeof (buf))
    active = false;
}  // end of interrupt service routine (ISR) SPI_STC_vect

void loop() {
  /*MOSI = BTtoSPI*/
  if (SerialBT.available()) {
    //use it as you would the regular arduino SPI API
    vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
    digitalWrite(5, LOW); //pull SS slow to prep other end for transfer
    vspi->transfer( SerialBT.read() );  
    digitalWrite(5, HIGH); //pull ss high to signify end of data transfer
    vspi->endTransaction();
  }

  /*MISO = SPItoBT*/
  if(digitalRead(5) == HIGH) {
    char buf[33]

    // enable Slave Select
    digitalWrite(SS, LOW);//turn on transmission
    SPI.transfer (1);   // initiate transmission
    for (int pos = 0; pos < sizeof (buf) - 1; pos++)
      {
      delayMicroseconds (15);
      buf [pos] = SPI.transfer (0); //receive SPI data
      if (buf [pos] == 0)
        {
        break;
        }
      }

    buf [sizeof (buf) - 1] = 0;  // ensure terminating null

    // disable Slave Select
    digitalWrite(SS, HIGH);//turn off transmission

    Serial.print ("We received: ");
    Serial.println (buf);
    
    SerialBT.write(buf);
  }
  
  delay(2000);
}
