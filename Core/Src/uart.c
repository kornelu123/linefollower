#include "uart.h"

void uart_init_tx(uint32_t baud , uint32_t periph,uint32_t presc){
  //Enabling clock access to GPIOB pin 
  RCC->AHB2ENR |= (1U << 1);
  //Enabling clock access to USART1 
  RCC->APB2ENR |= (1U << 14);
  //Setting PB6 to alternate function mode
  GPIOB->MODER &=~(1U << 12);
  GPIOB->MODER |= (1U << 13);
  //Setting PB6 alternate function to AF07
  GPIOB->AFR[0]  |= (1U << 24);
  GPIOB->AFR[0]  |= (1U << 25);
  GPIOB->AFR[0]  |= (1U << 26);
  GPIOB->AFR[0]  &=~(1U << 27);
  //Setting word length 
  USART1->CR1   &=~(1U << 12);
  USART1->CR1   &=~(1U << 28);
  //Setting parity control to disabled
  USART1->CR1   &=~(1U << 10);
  //Selecting baudrate (115200)
  USART1->BRR   = (uint8_t)(periph/(presc*baud));
  //Setting the number of stop bits
  USART1->CR2   &=~ (1U << 12);
  USART1->CR2   &=~ (1U << 13);
  //Enabling FIFO mode 
  USART1->CR1   |= (1U << 29);
  //Enabling UART  
  USART1->CR1   |=  (1U << 0);
  //Enabling Transfer for UART
  USART1->CR1   |=  (1U << 3);
}

void __io_putchar(uint8_t ch){
  write_char_uart(ch);
  return 1;
}

void write_char_uart(uint8_t ch){
  if(ch == '\n'){
    write_char_uart('\r');
  }
  //Wait until Transfer Data Register is not full
  while(!(USART1->ISR && (1U<<7)));
  //Write to Transmit Data Register
  USART1->TDR = (uint8_t) ( ch & 0xFFU );
}

void write_string_uart(char *text){
  for(int i=0;text[i] != '\0';i++){
    write_char_uart(text[i]);
  }
  write_char_uart('\n');
}
