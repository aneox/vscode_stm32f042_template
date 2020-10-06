#include "usart.h"

void Uart_init(uint32_t uart_baud)
{
    //reset uarts
    RCC->APB1RSTR |= RCC_APB1Periph_USART2;
    RCC->APB1RSTR &= ~RCC_APB1Periph_USART2;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// gpio Usarts
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure); //USART2

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_BaudRate = uart_baud;
    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    uint16_t toResetItBit = 0;
    toResetItBit = USART2->ISR;
    toResetItBit = USART2->RDR;
    toResetItBit++;

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

void tostring(char str[], int64_t num)
{
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

void Usart_Send_symbol(uint8_t data, USART_TypeDef *USARTx)
{
    while (!(USARTx->ISR & USART_FLAG_TC))
        ;
    USARTx->TDR = (data & (uint16_t)0x01FF);
}

void Usart_Send_String(char *str, USART_TypeDef *uartName)
{
    uint8_t i = 0;
    while (str[i])
    {
        Usart_Send_symbol(str[i], uartName);
        i++;
    }
    Usart_Send_symbol(0x0D, uartName);
    Usart_Send_symbol(0x0A, uartName);
}

void Usart_Send_String_with_int(char *str, int64_t integer, USART_TypeDef *uartName)
{
    uint16_t i = 0;
    while (str[i])
    {
        Usart_Send_symbol(str[i], uartName);
        i++;
    }

    if (integer < 0)
    {
        Usart_Send_symbol('-', uartName);
        integer *= -1;
    }

    if (integer != 0)
    {
        char strint[20];
        tostring(strint, integer);
        i = 0;
        while (strint[i])
        {
            Usart_Send_symbol(strint[i], uartName);
            i++;
        }
    }
    else
        Usart_Send_symbol('0', uartName);

    Usart_Send_symbol(0x0D, uartName);
    Usart_Send_symbol(0x0A, uartName);
}

void Usart_Send_chars_with_int(char *str, int64_t integer, USART_TypeDef *uartName)
{
    uint16_t i = 0;
    while (str[i])
    {
        Usart_Send_symbol(str[i], uartName);
        i++;
    }

    if (integer < 0)
    {
        Usart_Send_symbol('-', uartName);
        integer *= -1;
    }

    if (integer != 0)
    {
        char strint[20];
        tostring(strint, integer);
        i = 0;
        while (strint[i])
        {
            Usart_Send_symbol(strint[i], uartName);
            i++;
        }
    }
    else
        Usart_Send_symbol('0', uartName);
}

void Usart_Send_chars(char *str, USART_TypeDef *uartName)
{
    uint16_t i = 0;
    while (str[i])
    {
        Usart_Send_symbol(str[i], uartName);
        i++;
    }
}

uint8_t convertCharToInt(char ch)
{
    switch (ch)
    {
    case '0':
        return 0;
        break;
    case '1':
        return 1;
        break;
    case '2':
        return 2;
        break;
    case '3':
        return 3;
        break;
    case '4':
        return 4;
        break;
    case '5':
        return 5;
        break;
    case '6':
        return 6;
        break;
    case '7':
        return 7;
        break;
    case '8':
        return 8;
        break;
    case '9':
        return 9;
        break;
    case 'A':
        return 10;
        break;
    case 'B':
        return 11;
        break;
    case 'C':
        return 12;
        break;
    case 'D':
        return 13;
        break;
    case 'E':
        return 14;
        break;
    case 'F':
        return 15;
        break;
    default:
        return 0;
        break;
    }
    return 0;
}

void USART2_IRQHandler(void)
{
    uint8_t data;

    UNUSED(data);

    if ((USART2->ISR & USART_ISR_RXNE))
    {
        data = USART2->RDR;
    }
    else if ((USART2->ISR & USART_ISR_ORE))
    {
        data = USART2->RDR;
    }

    return;
}
