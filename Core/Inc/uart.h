#include <stdint.h>
#include "stm32wbxx.h"

void init_uart_tx();
static void uart_set_baudrate(uint32_t PeriphClk,uint32_t BaudRate);
static int uart_compute_baudrate(uint32_t PeriphClk , uint32_t BaudRate);
void write_uart(uint8_t ch);
