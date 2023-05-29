#include "main.h"
#include "stm32wbxx.h"
#include <stdint.h>
#include "uart.h"
#include <stdio.h>
#include <utils.h>

int main(void)
{
  uint32_t baud = 115200;
  uint32_t periph = 32000000;
  uint32_t uart_presc = 8;
  uart_init_tx(baud,periph,uart_presc);
  RCC->AHB2ENR |= (1U<<1);
  GPIOB->MODER |= (1U<<0);
  GPIOB->MODER &=~(1U<<1);
  while (1)
  {
    GPIOB->ODR ^= (1U<<0);
    delay_ms(1000);
    write_string_uart("cipa");
  }
 } 
