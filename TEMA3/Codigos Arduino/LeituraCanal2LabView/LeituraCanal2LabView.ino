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
float ads_bit_Voltage;
int16_t sample;

void setup(void) 
{
  
  Serial.begin(115200);   /* inicializa a serial */

  while (!Serial);    /* aguarda a serial estar disponível */
 
  
  // ads.setGain(GAIN_TWOTHIRDS);      float ads_InputRange =  6.144f;
   ads.setGain(GAIN_ONE);            float ads_InputRange =  4.096f;
  // ads.setGain(GAIN_TWO);            float ads_InputRange =  2.048f;
  // ads.setGain(GAIN_FOUR);           float ads_InputRange =  1.024f;
  // ads.setGain(GAIN_EIGHT);          float ads_InputRange =  0.512f;
  // ads.setGain(GAIN_SIXTEEN);        float ads_InputRange =  0.256f;
 
  ads.begin();  /* inicializa o ADC */
  ads_bit_Voltage = (ads_InputRange * 2) / (ADC_16BIT_MAX - 1);   /* no range de +-6.144V, 187.502uV/bit */
  analogReference(INTERNAL);    /* seta a referencia interna */
  
  /*Legenda do grafico*/
  Serial.println("A0\tA1\t"); 
}
 
void loop(void) 
{
  /* variavel para armazenar o valor RAW do adc */
  int16_t raw_ch0, raw_ch1; 
           
  /* variaveis para armazenar o resultado em tensao */
  float ads_Voltage_ch0 = 0.0f;
  float ads_Voltage_ch1 = 0.0f;
  //float ads_Voltage_ch2 = 0.0f;
  //float ads_Voltage_ch3 = 0.0f;

  raw_ch0 = ads.readADC_SingleEnded(0);
  raw_ch1 = ads.readADC_SingleEnded(1);
  //raw_ch2 = ads.readADC_SingleEnded(2);
  //raw_ch3 = ads.readADC_SingleEnded(3);
  
  ads_Voltage_ch0 = raw_ch0 * ads_bit_Voltage;
  ads_Voltage_ch1 = raw_ch1 * ads_bit_Voltage;
  //ads_Voltage_ch2 = raw_ch2 * ads_bit_Voltage;
  //ads_Voltage_ch3 = raw_ch3 * ads_bit_Voltage;

  Serial.print(raw_ch0);  Serial.print("\t");
  Serial.print(raw_ch1);  Serial.print("\t");
 // Serial.print(raw_ch2);  Serial.print("\t");
 // Serial.print(raw_ch3);  Serial.print("\t");
 
 // Serial.print(ads_Voltage_ch0, 3);  Serial.print("\t");
 // Serial.print(ads_Voltage_ch1, 3);  Serial.print("\t");
 // Serial.print(ads_Voltage_ch2, 3);  Serial.print("\t");
 // Serial.print(ads_Voltage_ch3, 3);  Serial.print("\t");
 
  Serial.print("\n");  //delay(1);
  
}
