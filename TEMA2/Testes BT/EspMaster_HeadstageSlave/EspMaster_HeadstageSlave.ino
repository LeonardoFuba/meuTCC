#include "BluetoothSerial.h"
#include <string.h>
#include <SPI.h>

static const int spiClk = 1000000; // 1 MHz
uint16_t buf;
uint8_t BT;

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

  /*set up slave select pins as outputs as the Arduino API*/
  /*doesn't handle automatically pulling SS low*/
  pinMode(5, OUTPUT); //VSPI SS
  //pinMode(15, OUTPUT); //HSPI SS

  digitalWrite(SS, LOW);
  RHDcalibrate();
  digitalWrite(5, HIGH);
}


void loop() {
  /*MOSI = BTtoSPI*/
  if (SerialBT.available()) {
    //use it as you would the regular arduino SPI API
    vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
    digitalWrite(5, LOW); //pull SS slow to prep other end for transfer
    buf = RHDconvert( SerialBT.read() - 0b110000 );


    //for (int pos = 0,ch=0; pos < sizeof (buf) - 1; pos++,ch++){
    delayMicroseconds (15);
    digitalWrite(5, LOW); //pull SS slow to prep other end for transfer
    BT = (uint8_t)SerialBT.read();
    buf = RHDconvert( BT ); //receive SPI data
    digitalWrite(5, HIGH); //pull ss high to signify end of data transfer
    Serial.println(buf);/*MISO = SPItoBT*/
    //SerialBT.println(buf);
    //SerialBT.write(buf);
    //}
    Serial.println();
    //digitalWrite(5, HIGH); //pull ss high to signify end of data transfer
    vspi->endTransaction();

    //buf [sizeof (buf) - 1] = 0;  // ensure terminating null
    Serial.println ("We received: ");
    Serial.print ("canal ");
    Serial.println (BT);
  }

  delay(1000);
}

uint16_t RHDconvert(uint8_t channel){
  uint16_t A = vspi->transfer16( (0b00111111 & channel) << 8);
  return A;
}

uint16_t RHDcalibrate(void){
  uint16_t A = vspi->transfer16( 0b01010101 << 8);
  return A;
}

uint16_t RHDwrite(uint8_t reg, uint8_t data){

  uint16_t D = vspi->transfer16( (0b10000000 | reg) << 8 | data );
  if(D >> 8 == 0b11111111 && (uint8_t)D == data)
    Serial.println (" Sent without error. ");
  return D;
}

uint8_t RHDread(uint8_t reg){
  uint8_t D = (uint8_t)vspi->transfer16( 0b11000000 | reg << 8);
  return D;
}
