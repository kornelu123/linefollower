#include <adc.h>

void adc_init(){
  //Setting clock source for ADC to sysclock
  RCC->CCIPR    |= ((1U<< 29) | (1U << 28));
  //Peripheral clock enable for ADC 
  RCC->AHB2ENR  |= (1U << 13);
  //Peripheral clock enable for GPIOA
  RCC->AHB2ENR  |= (1U << 0 );
  //Setting up PA0 to be in analog mode 
  GPIOA->MODER  |= ((1U << 0)  | (1U << 1) );
  //Setting clock to asynchronmous mode 
  //ADC1->CCR     &=~((1U << 16) | (1U << 17));
  //Setting adc resolution to 12B
  ADC1->CFGR    &=~((1U << 3)  | (1U << 4) );
  //Setting data alignment to right
  ADC1->CFGR    &=~(1U << 5 );
  //Setting conversion mode to single-conversion
  ADC1->CFGR    &=~(1U << 13);
  //Disable regular oversampling
  ADC1->CFGR2   &=~(1U << 0 );
  //Disable ADC dep power down mode 
  ADC1->CR      &=~(1U << 29);
  //Enable ADC internal voltage regulator
  ADC1->CR      |= (1U << 28);
  //Wait for 20 us
  uint16_t wait_loop_time_us = 20;
  for(int i=0;i<(wait_loop_time_us * ((64000000)/(1000000*2)));i++);
  //Setting 1st regular sequence channel to 5
  ADC1->SQR1     |= (5U << 6 );
  //Sampling time is default set to 2.5 cycles (ADC->SMPR register)
  //Setting channel 5 to single-diff 
  ADC1->DIFSEL   &=~(1U << 5 ); 
} 

uint16_t adc_read(){
  //Clearing ADRDY bit in ADC_ISR register 
  ADC1->ISR      |= (1U << 0 );
  //Enabling the ADC 
  ADC1->CR       |= (1U << 0 );
  //Waiting for ADRDY bit to be set
  //TODO :: find out why line 43 doesnt work
  //while((ADC1->ISR & (1U << 0)) == 0);
  //ADC start of regular conversion
  ADC1->CR       |= (1U << 2 );
  //Wait until end of conversion flag is set 
  while((ADC1->ISR & (1U<<3)) == 0);
  //Read the data from ADC data register
  uint16_t adc_value = ADC1->DR & 0xffff;
  return adc_value;
  //Disable the ADC 
  ADC1->CR       |= (1U << 2 );
}
