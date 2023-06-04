#include <adc.h>

void adc_init(){
  //Exit Deep-power-down mode 
  ADC1->CR      &=~(1U << 29 );
  //Enable ADC voltage regulator
  ADC1->CR      |= (1U << 28);
  //Wait for 20 micro seconds for adc to setup
  for(int i=0;i<80;i++);
  //Disable clock access to adc 
  RCC->AHB2ENR &=~(1U << 13);
  //Set ADCEN bit to 1
  ADC1->CR      |= (1U << 0);
  //Wait until ADRDY is set to 1
  //Select single-ended input 
  ADC1->CR      &=~(1U << 30);
  //Calibrate adc 
  ADC1->CR      |= (1U << 31);
  //Want until adc is  calibrated
  while((ADC1->CR & (1U<<31) == 1));
  //Enable clock access to ADC
  RCC->AHB2ENR  |= (1U << 13);
  //Clear the ADRDY bit 
  ADC1->ISR     |= (1U << 0);
  //Wait until ADC is ready to convert
  while(!(((ADC1->ISR) & (1U<<0)) == 0));
  //Enable clock access to GPIOC 
  RCC->AHB2ENR  |= (1U << 2);
  //Set PC0 pin to Analog 
  GPIOC->MODER  |= ((1U << 1) | (1U << 0));
  //Set Regular sequence 1st sequence to ch 1 
  ADC1->SQR1    |= (1U << 7);
} 

uint16_t adc_read(){
  //ADC start of regular conversion
  ADC1->CR      |= (1U << 2);
  //Wait until end of conversion flag is set 
  while((ADC1->ISR & (1U<<3) == 0));
  //Read the data from ADC data register
  uint16_t adc_value = ADC1->DR & 0xffff;
  return adc_value;
}
