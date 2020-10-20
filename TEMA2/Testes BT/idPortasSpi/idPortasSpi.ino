
	
void setup() {
  Serial.begin(115200);
  Serial.println("The device started");
  Serial.println(MISO);//19
  Serial.println(MOSI);//23
  Serial.println(SCK);//18
  Serial.println(SS);//5
}

void loop() {
	
  delay(200);
}
