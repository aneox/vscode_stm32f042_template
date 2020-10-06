#include "can.h"

void CAN_Config(void)
{
    CAN_InitTypeDef CAN_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    //    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE ); //сделано в main
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_4);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_4);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    CAN_DeInit(CAN);
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = ENABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq; //1MBIT
    CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStructure.CAN_Prescaler = 2;
    CAN_Init(CAN, &CAN_InitStructure);

    // CAN_FilterInitTypeDef CAN_FilterInitStructure;
    // CAN_FilterInitStructure.CAN_FilterNumber = 0;
    // CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    // CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    // CAN_FilterInitStructure.CAN_FilterIdHigh = RX_CAN_ID << 5;
    // CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    // CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x7FF << 5;
    // CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    // CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
    // CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    // CAN_FilterInit(&CAN_FilterInitStructure);

    // NVIC_InitTypeDef NVIC_InitStructure;
    // NVIC_InitStructure.NVIC_IRQChannel = CEC_CAN_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
    // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_Init(&NVIC_InitStructure);

    // CAN_ITConfig(CAN, CAN_IT_FMP0, ENABLE);

    // CAN->sTxMailBox[0].TIR &= ((uint32_t)0x00000001); //TMIDxR_TXRQ; /* Transmit mailbox request */
    // CAN->sTxMailBox[0].TIR |= (TX_CAN_ID << 21);
    // CAN->sTxMailBox[0].TDTR &= (uint32_t)0xFFFFFFF0;
    // CAN->sTxMailBox[0].TDTR |= 1;
    // CAN->sTxMailBox[0].TDLR = 0;
    // CAN->sTxMailBox[0].TDHR = 0;
    // CAN->sTxMailBox[0].TIR |= ((uint32_t)0x00000001); //TMIDxR_TXRQ; /* Transmit mailbox request */
}

void CEC_CAN_IRQHandler(void)
{
    if ((CAN->RF0R & CAN_RF0R_FMP0))
    {
        CAN->RF0R |= CAN_RF0R_RFOM0; //Release FIFO
    }
}
