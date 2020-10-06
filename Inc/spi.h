// #ifndef SPI_H
// #define SPI_H
#include "main.h"

#define CS_UP GPIOA->BSRR = GPIO_Pin_4
#define CS_DOWN GPIOA->BRR = GPIO_Pin_4

void SPI_Config(uint8_t prescaler);
uint8_t SPI_WriteRead_8Bit(uint8_t data);

// #endif // SPI_H
