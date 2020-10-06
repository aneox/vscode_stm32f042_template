#ifndef MAIN_H
#define MAIN_H

#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"

#include "can.h"
#include "usart.h"
#include "spi.h"

#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define UNUSED(x) (void)(x)

void DelayMillis(volatile uint32_t millis);
void DelayMicros(volatile uint32_t micros);

#endif // MAIN_H
