typedef enum __TIM_DMA_OPTIONS{
	MINC
} TIM_DMA_OPTIONS;
typedef enum ___DMA_CH_STATE{
	FREE,
	BUSY
} DMA_CH_STATE;

void TIM3_CH_DMA_Send(uint8_t timChannel, TIM_DMA_OPTIONS options, uint32_t addrData);
void TIM3_CH_1_IRQHandler();