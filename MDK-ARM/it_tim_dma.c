#include "stm32f4xx_hal.h"
#include "C:\projects\stm32\401\s32_401_ws2812\MDK-ARM\ws2812.h"
#include "C:\projects\stm32\401\s32_401_ws2812\MDK-ARM\periph_structs.h"
#include "C:\projects\stm32\401\s32_401_ws2812\MDK-ARM\it_tim_dma.h"


//TIM3_CH1_DEFINES
uint16_t uint16_NULL = 0;

DMA_CH_STATE TIM3_CH1_STATUS = FREE;

//END___TIM3_CH1_DEFINES
void TIM3_CH_1_IRQHandler()	{
	uint32_t addr = (uint32_t) &uint16_NULL;
	if(DMA1_Stream2->M0AR == addr){
		TIM3_CH1_STATUS = FREE;
		return;
	}
	DMA1_Stream2->M0AR = (uint32_t) &uint16_NULL;
	DMA1->LIFCR = 61 << 16;
	DMA1_Stream2->NDTR = 60 ;
	DMA1_Stream2->CR &= ~DMA_SxCR_MINC;
	DMA1_Stream2->CR |= DMA_SxCR_TCIE;
	DMA1_Stream2->CR |= DMA_SxCR_EN;
}

void TIM3_CH_DMA_Send(uint8_t timChannel, TIM_DMA_OPTIONS options, uint32_t addrData){
	if(TIM3_CH1_STATUS != FREE)
		return;
	TIM3_CH1_STATUS = BUSY;
	DMA1_Stream2->M0AR = addrData;
	DMA1->LIFCR = 61 << 16;
	if( options == MINC)	{
		DMA1_Stream2->CR |= DMA_SxCR_MINC;
		DMA1_Stream2->NDTR = ws2812_count * 24 ;
	}
	else	{
		DMA1_Stream2->CR &= ~DMA_SxCR_MINC;
		DMA1_Stream2->NDTR = 50000;
	}
	DMA1_Stream2->CR |= DMA_SxCR_TCIE;

	while(TIM3->CNT > 5);
	DMA1_Stream2->CR |= DMA_SxCR_EN;
}