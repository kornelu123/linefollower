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



void write_char_uart(uint8_t ch){
  if(ch == '\n'){
    write_char_uart('\r');
  }
  //Wait until Transfer Data Register is not full
  while(!(USART1->ISR && (1U << 23)));
  //Write to Transmit Data Register
  USART1->TDR = (uint8_t) ( ch & 0xFFU );
}

void prints(char *text){
  for(int i=0;text[i] != '\0';i++){
    if(i%100==99) write_char_uart('\n');
    write_char_uart(text[i]);
    for(int i=0;i<100;i++);
  }
}

void printint(int integer){
  int *string_int;
  int i = 0;
  string_int[i] = 0;
  
  for(i=1;integer != 0;i++){
    string_int[i] = integer%10 + '0';
    integer = integer/10;
  }

  write_char_uart(i + '0');

  for(int j=i-1;string_int[j] != 0;j--){
    write_char_uart(string_int[j] + '0');
  }
}


