// the sensor communicates using SPI, so include the library:
#include <SPI.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// the sensor communicates using SPI, so include the library:
BluetoothSerial SerialBT;
int MISO = 19;
int MOSI = 23;
int SCK = 18;
int SS = 5;


void setup() {
  // start:
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  SPI.begin();

  // initalize the  data ready and chip select pins:
  pinMode(MISO, INPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(SCK, OUTPUT);
  pinMode(SS, OUTPUT);


  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
    digitalWrite(MOSI,LOW);
    Serial.println("LOW");
    delay(1000);
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
    digitalWrite(MOSI,HIGH);
    Serial.println("HIGH");
    delay(1000);
  }
  delay(20);
}
