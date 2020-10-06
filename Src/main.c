/* Includes ------------------------------------------------------------------*/
#include "main.h"

void DelayMillis(volatile uint32_t millis)
{
    millis = 1000 * millis * 9;
    /* 4 cycles for one loop */
    while (millis--)
        ;
}

void DelayMicros(volatile uint32_t micros)
{
    micros = micros * 9;
    /* 4 cycles for one loop */
    while (micros--)
        ;
}

int main(void)
{
    /* Check if the system has resumed from IWDG reset */
    if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
    {
        RCC_ClearFlag();
    }

    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_64);
    IWDG_SetReload(40000 / 128);
    IWDG_ReloadCounter();

    SystemInit();
    FLASH_SetLatency(FLASH_Latency_1);

    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_9); //36Mhz
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        ;
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Set HCLK, PCLK1, and PCLK2 to SCLK (these are default */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLKConfig(RCC_HCLK_Div1);
    SystemCoreClockUpdate();

#ifndef DEBUG
    IWDG_Enable();
#endif

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;        // Тактирования SYSCONFIG
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_PA11_PA12_RMP; // Ремап ножек PA10 PA9 на PA12 PA11
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_CRC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// timers
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TIM_TimeBaseInitTypeDef timer;
    TIM_TimeBaseStructInit(&timer);
    timer.TIM_Prescaler = SystemCoreClock / 1000 - 1;
    timer.TIM_Period = 1000;
    TIM_TimeBaseInit(TIM14, &timer);

    NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM14->CNT = 0;
    TIM14->SR = (uint16_t)~TIM_IT_Update;
    TIM14->DIER |= TIM_IT_Update;
    TIM14->CR1 |= TIM_CR1_CEN;

    while (1)
    {
    }
}

void vApplicationTickHook(void)
{
}

void TIM14_IRQHandler(void)
{
    TIM14->SR = (uint16_t)~TIM_IT_Update; //TIM_ClearITPendingBit
}
