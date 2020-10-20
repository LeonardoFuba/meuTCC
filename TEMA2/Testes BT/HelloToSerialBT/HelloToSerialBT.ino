#include "BluetoothSerial.h"
#include <string.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run 'make menuconfig' to and enable it
#endif

BluetoothSerial SerialBT;
char texto[] = {"Hello World!"};
int tam = strlen(texto);

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32-SerialBT"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (Serial.available()) {
    int i;
    for(i=0;i<tam;i++){
      SerialBT.write(texto[i]);
    }
  }
  if (SerialBT.available()) {
    //Serial.write(SerialBT.read());
  }
  delay(2000);
}
