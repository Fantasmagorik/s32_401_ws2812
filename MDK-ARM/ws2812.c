#define WS2812_MEMORY_SIZE	321
#include "main.h"
#include "C:\projects\stm32\401\s32_401_ws2812\MDK-ARM\ws2812.h"

enum colorScheme ws2812_order;


uint16_t ws2812_memory[ws2812_count * 24 + 1];
uint32_t ws2812_pixels[32];
 
uint32_t getStepColor(uint32_t sourceColor, uint32_t needColor, uint32_t currentStep, uint32_t countOfSteps) {
  _color rColor, sColor, nColor;
  sColor.pixelColor = sourceColor;
  nColor.pixelColor = needColor;
	uint32_t result = 0;
	uint8_t bres, bsource;
  if (currentStep > countOfSteps || countOfSteps == 0 || currentStep == 0)
    return 0;//wrong arguments
 
	/*for (int i = 1; i < 3; i++)  {
    if (nColor.byteColor[i] > sColor.byteColor[i])
      rColor.byteColor[i] = sColor.byteColor[i] + ((nColor.byteColor[i] - sColor.byteColor[i]) / countOfSteps * currentStep);
    else if (nColor.byteColor[i] < sColor.byteColor[i])
      rColor.byteColor[i] = sColor.byteColor[i] - ((sColor.byteColor[i] - nColor.byteColor[i]) / countOfSteps * currentStep);
    else //eq
      rColor.byteColor[i] = nColor.byteColor[i];
  }*/

	for (int i = 0; i < 3; i++)  {
    if (nColor.byteColor[i] > sColor.byteColor[i])
      bres = sColor.byteColor[i] + ((nColor.byteColor[i] - sColor.byteColor[i]) / countOfSteps * currentStep);
    else if (nColor.byteColor[i] < sColor.byteColor[i])
      bres = sColor.byteColor[i] - ((sColor.byteColor[i] - nColor.byteColor[i]) / countOfSteps * currentStep);
    else //eq
      bres = nColor.byteColor[i];
		result |= bres << i * 8;
  }
	
	return result;
  //return rColor.pixelColor;
}

void ws2812_init(int ledCount, enum colorScheme order)	{
	int i;
	if(ledCount < 0)
			return;
	for(i = 0; i < WS2812_MEMORY_SIZE; i++)
		ws2812_memory[i] = 0;
	//ws2812_count = ledCount;
	ws2812_order = order;
	
}

void ws2812_setPixelColor(int pixelNo, int color)	{
	union ws2812_pixel pixel;
	uint8_t tempByte;
	pixel.pixelColor = color;
	switch(ws2812_order){
		case GRB: 
			tempByte = pixel.byteColor[0];
			pixel.byteColor[0] = pixel.byteColor[1];
			pixel.byteColor[1] = pixel.byteColor[2];
			pixel.byteColor[2] = tempByte;
			break;
			
	}
	ws2812_pixels[pixelNo] = pixel.pixelColor;
}

void ws2812_fill(uint32_t color)	{
	int i;
	uint8_t tempByte;
	union ws2812_pixel pixel;
	pixel.pixelColor = color;
	switch(ws2812_order){
		case GRB: 
			tempByte = pixel.byteColor[0];
			pixel.byteColor[0] = pixel.byteColor[1];
			pixel.byteColor[1] = pixel.byteColor[2];
			pixel.byteColor[2] = tempByte;
			break;
			
	};
	for(i = 0; i < ws2812_count; i++)
		ws2812_pixels[i] = pixel.pixelColor;
}

uint16_t* ws2812_show()	{
	int i, x;
	for(x = 0; x < ws2812_count; x++){
		for(i = 0; i < 24; i++){
			ws2812_memory[x * 24 + i] = (ws2812_pixels[x] & (1 << (23 - i)))? ONE : ZERO;
	}
}
		
		return ws2812_memory;
}
