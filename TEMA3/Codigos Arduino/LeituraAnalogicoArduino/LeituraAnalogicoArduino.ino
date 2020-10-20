byte sample;

void setup() {
  Serial.begin(115200);
  sample = 0;

}

void loop() {
  //255 = 3.3V
  sample = analogRead(17);
  Serial.println(sample);
  delay(10);
}
