#include "main.h"
#include "stm32wbxx.h"
#include <stdint.h>
#include "uart.h"
#include "adc.h"

int main(void)
{
  uint32_t baud = 115200;
  uint32_t periph = 32000000;
  uint32_t uart_presc = 8;
  uart_init_tx(baud,periph,uart_presc);
  adc_init();
  prints("cwel \n");
  RCC->AHB2ENR |= (1U<<1);
  GPIOB->MODER |= (1U<<0);
  GPIOB->MODER &=~(1U<<1);
  while (1)
  {
    uint16_t adc_value = adc_read();
    GPIOB->ODR ^= (1U<<0);
    for(int i=0;i<100000;i++);
    printint(adc_value);
    prints("\n");
  }
 } 
