/********************************************************************************
 * ADS1115 - Medidas de tensao e conversor analogico digital ADS1115 (16 bit)
 * ------------------------------------------------------------------------------
 * https://github.com/...
 * developed by: Leonardo do Nascimento - leonardo3.nascimento@gmail.com
 * 2020/04/23 - v 1.0
 ********************************************************************************/
#include <Wire.h>                 //biblioteca i2c
#include <Adafruit_ADS1015.h>     //biblioteca conversor ADS
#define   ADC_16BIT_MAX   65536   /* possibilidades/niveis de acordo com a resolução */
Adafruit_ADS1115 ads1(0x48);     /* cria instância do conversor analogico digital ADC */
float ads_bit_Voltage;

void setup(void) 
{
  Serial.begin(115200);   /* inicializa a serial */
  while (!Serial);    /* aguarda a serial estar disponível */
  
  // ads1.setGain(GAIN_TWOTHIRDS);    float ads_InputRange =  6.144f;
  // ads1.setGain(GAIN_ONE);          float ads_InputRange =  4.096f;
  // ads1.setGain(GAIN_TWO);          float ads_InputRange =  2.048f;
   ads1.setGain(GAIN_FOUR);         float ads_InputRange =  1.024f;
  // ads1.setGain(GAIN_EIGHT);        float ads_InputRange =  0.512f;
  // ads1.setGain(GAIN_SIXTEEN);      float ads_InputRange =  0.256f;
 
  ads1.begin();  /* inicializa o ADC1 */
  ads_bit_Voltage = (ads_InputRange * 2) / (ADC_16BIT_MAX - 1);   /* no range de +-6.144V, 187.502uV/bit */
  analogReference(INTERNAL);    /* seta a referencia interna */
  
  /*Legenda do grafico*/
  Serial.println("CH1\tCH2\tCH3\tCH4\t");   
}

void loop(void) 
{
   Serial.print(ads1.readADC_SingleEnded(0));  Serial.print("\t");
   Serial.print(ads1.readADC_SingleEnded(1));  Serial.print("\t");
   Serial.print(ads1.readADC_SingleEnded(2));  Serial.print("\t");
   Serial.print(ads1.readADC_SingleEnded(3));  Serial.println("\t");
}
