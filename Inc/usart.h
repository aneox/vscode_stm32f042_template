#ifndef USART_H
#define USART_H
#include "main.h"

#define DEBUG_UART USART2
#define DEF_DEBUG_UART_BAUD 230400

void Usart_Send_String(char *str, USART_TypeDef *uartName);
void Usart_Send_symbol(uint8_t data, USART_TypeDef *USARTx);
void Usart_Send_chars(char *str, USART_TypeDef *uartName);
void Usart_Send_chars_with_int(char *str, int64_t integer, USART_TypeDef *uartName);
void Usart_Send_String_with_int(char *str, int64_t integer, USART_TypeDef *uartName);
uint8_t convertCharToInt(char ch);

void Uart_init(uint32_t uart_baud);
#endif // USART_H
