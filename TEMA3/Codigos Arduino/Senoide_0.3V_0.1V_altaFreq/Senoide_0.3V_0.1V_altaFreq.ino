static byte WaveFormTable[100] =  // 100 samples sin wave
{
    0x80, 0x88, 0x90, 0x97, 0x9F, 0xA7, 0xAE, 0xB5, 0xBC, 0xC3,
    0xC9, 0xD0, 0xD6, 0xDB, 0xE0, 0xE5, 0xEA, 0xEE, 0xF1, 0xF4,
    0xF7, 0xF9, 0xFB, 0xFC, 0xFD, 0xFD, 0xFD, 0xFC, 0xFB, 0xF9,
    0xF7, 0xF4, 0xF1, 0xEE, 0xEA, 0xE5, 0xE0, 0xDB, 0xD6, 0xD0,
    0xC9, 0xC3, 0xBC, 0xB5, 0xAE, 0xA7, 0x9F, 0x97, 0x90, 0x88,
    0x80, 0x78, 0x70, 0x69, 0x61, 0x59, 0x52, 0x4B, 0x44, 0x3D,
    0x37, 0x30, 0x2A, 0x25, 0x20, 0x1B, 0x16, 0x12, 0x0F, 0x0C,
    0x09, 0x07, 0x05, 0x04, 0x03, 0x03, 0x03, 0x04, 0x05, 0x07,
    0x09, 0x0C, 0x0F, 0x12, 0x16, 0x1B, 0x20, 0x25, 0x2A, 0x30,
    0x37, 0x3D, 0x44, 0x4B, 0x52, 0x59, 0x61, 0x69, 0x70, 0x78
};
int i = 0;

void setup() {
  Serial.begin(115200);   // start Serial for output
}

void loop() {
  dacWrite(25, (WaveFormTable[i]/8) ); //255 = 3.22V  0 = 0.09V
  Serial.print( (WaveFormTable[i]/8) ); Serial.print("\t");
  Serial.println();
  i++;
  if (i >= 100) i = 0;
}
