/********************************************************************************
 * ADS1115 - Medicao de tensao e conversor analogico digital ADS1115 (16 bit)
 * ------------------------------------------------------------------------------
 * https://github.com/...
 * developed by: Leonardo do Nascimento - leonardo3.nascimento@gmail.com
 * 2020/03/21 - v 1.0
 ********************************************************************************/
#include <Wire.h>                 //biblioteca i2c
#include <Adafruit_ADS1015.h>     //biblioteca conversor ADS
 
#define   ADC_16BIT_MAX   65536   /* possibilidades/niveis de acordo com a resolução */
 
Adafruit_ADS1115 ads(0x48);       /* cria instância do conversor analogico digital ADC */

/* Variaveis */
float ads_bit_Voltage;
int16_t sample;

 
void setup(void) 
{
  
  Serial.begin(115200);   /* inicializa a serial */

  while (!Serial);    /* aguarda a serial estar disponível */
 
  /*
   * configura o ganho do PGA interno do ADS1115
   * - Sem configurar ele inicia automaticamente na escala de +/- 6.144V
   * - lembre-se de não exceder os limites de tensao nas entradas
   * - - VDD+0.3v ou GND-0.3v
   * 
   *  2/3x gain   +/- 6.144V    1 bit = 3mV       0.1875mV (default)
   *  1x gain     +/- 4.096V    1 bit = 2mV       0.125mV
   *  2x gain     +/- 2.048V    1 bit = 1mV       0.0625mV
   *  4x gain     +/- 1.024V    1 bit = 0.5mV     0.03125mV
   *  8x gain     +/- 512mV     1 bit = 0.25mV    0.015625mV
   *  16x gain    +/- 256mV     1 bit = 0.125mV   0.0078125mV
   */
  
  // ads.setGain(GAIN_TWOTHIRDS);      float ads_InputRange =  6.144f;
  ads.setGain(GAIN_ONE);            float ads_InputRange =  4.096f;
  // ads.setGain(GAIN_TWO);            float ads_InputRange =  2.048f;
  // ads.setGain(GAIN_FOUR);           float ads_InputRange =  1.024f;
  // ads.setGain(GAIN_EIGHT);          float ads_InputRange =  0.512f;
  // ads.setGain(GAIN_SIXTEEN);        float ads_InputRange =  0.256f;
 
  ads.begin();  /* inicializa o ADC */
  ads_bit_Voltage = (ads_InputRange * 2) / (ADC_16BIT_MAX - 1);   /* no range de +-6.144V, 187.502uV/bit */
  analogReference(INTERNAL);    /* seta a referencia interna */
//  analogReference(EXTERNAL);  /*a tensao aplicada ao pino AREF (0 a 5V apenas).*/
 
  /*
   * imprime o valor da tensao por bit
   * - ADS1115 (de acordo com o ganho do PGA)
   * - Arduino Nano/Uno com referencia em Vcc
   * - Arduino Nano/Uno com referencia interna de 1.1V
   */
  Serial.println(F("\r\n"__FILE__"\t"__DATE__" "__TIME__));   /* imprime o nome do arquivo com data e hora */
  Serial.println();
  Serial.print("ADS volt/bit: ");   Serial.print(ads_bit_Voltage * 1000, 4);     Serial.println(" mV/bit");
  Serial.println();
  //Serial.println("RAW0 \tRAW1 \tADS0 \tADS1 \t\t"); /* imprime a primeira linha com identificacao dos dados */
  Serial.println("RAW0 \tADS0");
}
 


void loop(void) 
{
  
  int16_t raw_ch0 = 0;          /* variavel para armazenar o valor RAW do adc */
  // int16_t raw_ch1 = 0;
  // int16_t raw_ch2 = 0;
  // int16_t raw_ch3 = 0;

  float ads_Voltage_ch0 = 0.0f; /* variaveis para armazenar o resultado em tensao */
  // float ads_Voltage_ch1 = 0.0f; /* variaveis para armazenar o resultado em tensao */
  // float ads_Voltage_ch2 = 0.0f; /* variaveis para armazenar o resultado em tensao */
  // float ads_Voltage_ch3 = 0.0f; /* variaveis para armazenar o resultado em tensao */

  // int16_t uno_ch3 = 0;          /*usando referencia interna do arduino (1.1V)*/
  // int16_t uno_ch2 = 0;
  // int16_t uno_ch1 = 0;
  // int16_t uno_ch0 = 0;


  /********************************************
   * ADS1115 - 16bit ADC
   * - le o ADC
   * - converter o valor RAW em tensao
   ********************************************/
  raw_ch0 = ads.readADC_SingleEnded(0);
  // raw_ch1 = ads.readADC_SingleEnded(1);
  // raw_ch2 = ads.readADC_SingleEnded(2);
  // raw_ch3 = ads.readADC_SingleEnded(3);

  ads_Voltage_ch0 = raw_ch0 * ads_bit_Voltage;
  // ads_Voltage_ch1 = raw_ch1 * ads_bit_Voltage;
  // ads_Voltage_ch2 = raw_ch2 * ads_bit_Voltage;
  // ads_Voltage_ch3 = raw_ch3 * ads_bit_Voltage;


  // uno_ch3 = analogRead(17);
  // uno_ch2 = analogRead(16);
  // uno_ch1 = analogRead(15);
  // uno_ch0 = analogRead(14);

  /* imprime os resultados */
  Serial.print(raw_ch0);
  Serial.print("\t");
  // Serial.print(raw_ch1);
  // Serial.print("\t");
  Serial.print(ads_Voltage_ch0, 3);
  Serial.print("\t");
  // Serial.print(ads_Voltage_ch1, 3);
  // Serial.print("\t");
  
  // Serial.print(uno_ch3);
  // Serial.print("\t");
  // Serial.print(uno_ch2);
  // Serial.print("\t");
  // Serial.print(uno_ch1);
  // Serial.print("\t");
  // Serial.print(uno_ch0);
  // Serial.print("\t");
  
  Serial.println();
  
}
