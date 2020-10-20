// slave

#include <SPI.h>

void setup (void)
{
  //SERIAL SETUP
    Serial.begin (115200);
    Serial.println ("Slave Starting");

  //SPI SETUP
    pinMode(MISO, OUTPUT);
    
    //Arduino SPI Control Register (SPCR)
    SPCR |= bit(SPE);// turn on SPI in slave mode
    SPCR |= bit(SPIE);// turn on interrupts
  
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

void loop (void)
{

}  // end of loop
