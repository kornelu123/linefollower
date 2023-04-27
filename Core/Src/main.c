#include "main.h"
#include "stm32wbxx.h"
#include <stdint.h>
#include "uart.h"


int main(void)
{
  uint32_t baud = 115200;
  uint32_t periph = 64000000;
  uart_init_tx(periph,baud);

  RCC->AHB2ENR |= (1U<<1);
  GPIOB->MODER |= (1U<<0);
  GPIOB->MODER &=~(1U<<1);
  while (1)
  {
    GPIOB->ODR ^= (1U<<0);
    for(int i=0;i<1000000;i++);
    write_uart('a');
  }
 }
