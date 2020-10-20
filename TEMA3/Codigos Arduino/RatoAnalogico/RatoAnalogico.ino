//nomes das portas
#define DAC1 25
#define DAC2 26


//constantes
//#define Frequency  1000 //Hz
//#define Amplitude  50   //%        100% = 2.44V (default)
//#define Num_Samples  1000

//variaveis globais
//int fator = (int)(100/Amplitude);
int value;


void setup() {
  Serial.begin(115200);   // start Serial for output
  Serial.println("Start loop");
  Serial.print("Senoide"); Serial.print("\t\t"); Serial.print(dac2);
  Serial.println();
}

void loop() {
  for (int deg = 0; deg < 360; deg = deg + 8){
    value = int(3 + sin(deg*PI/180) + 11*sin(11*deg*PI/180)/11);
    dacWrite(DAC1, value); // senoide 50mv~12mv
    dacWrite(DAC2, 1);
    Serial.print(value); Serial.print("\t\t"); Serial.print( 3.22/255 );
    Serial.println();
  }
  delay(1);
}
