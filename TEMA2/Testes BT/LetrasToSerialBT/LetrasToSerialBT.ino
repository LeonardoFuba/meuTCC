#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int nome[8] = {76,101,111,110,97,114,100,111};
int i;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32-SerialBT"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    for(i=0;i<8;i++){
      SerialBT.write((uint8_t)nome[i]);
      delay(300);
    }
  }
  delay(5000);
}
