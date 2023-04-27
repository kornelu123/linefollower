#include "uart.h"

#define GPIOBEN (1U<<1)
#define AFMODE_1 (1U<<12)
#define AFMODE_2 (1U<<13)
#define USART1EN (1U<<14)
#define CR1TE (1U<<3)
#define CR1UE (1U<<0)
#define ISRTXE (1U<<7)
#define BAUDRATE 115200
#define PERIPHCLK 64000000

void uart_init_tx(){
  //Enable clock access to GPIOB
  RCC->AHB2ENR |= GPIOBEN;
  //Set PB6 mode to Alternate function mode
  GPIOB->MODER |= AFMODE_1;
  GPIOB->MODER &=~AFMODE_2;
  //Set PB6 alternate function type to UART_TX ( AF07 )
  GPIOB->AFR[0] |= (1U<<24);
  GPIOB->AFR[0] |= (1U<<25);
  GPIOB->AFR[0] |= (1U<<26);
  GPIOB->AFR[0] &=~(1U<<27);
  //Enable clock access to uart1
  RCC->APB2ENR |= USART1EN;
  //Configure baudrate 
  uart_set_baudrate(PERIPHCLK,BAUDRATE);
  //Configure the transfer direction
  USART1->CR1 |= CR1TE;
  //Enable uart module
  USART1->CR1 |= CR1UE; 
}

static void uart_set_baudrate(uint32_t PeriphClk,uint32_t BaudRate){
  USART1->BRR = uart_compute_baudrate(PeriphClk,BaudRate);
}

static int uart_compute_baudrate(uint32_t PeriphClk, uint32_t BaudRate){
  return ((PeriphClk + ( BaudRate / 2U ))/BaudRate);
}

void write_uart(uint8_t ch){
  //Wait until Transfer Data Register is not full
  while(!(USART1->ISR & ISRTXE));
  //Write to Transmit Data Register
  USART1->TDR = ( ch & 0xFFU );
}
