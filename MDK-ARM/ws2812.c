#define WS2812_MEMORY_SIZE	321
#include "main.h"
#include "C:\projects\stm32\401\s32_401_ws2812\MDK-ARM\ws2812.h"
int ws2812_count = 10;
enum colorScheme ws2812_order;

uint16_t ws2812_memory[WS2812_MEMORY_SIZE];
uint32_t ws2812_pixels[32];

uint16_t* getColorData(uint32_t color)	{
	int i;
	for(i = 0; i < 32; i++){
		ws2812_memory[i] = (color & 1 << i)? ONE : ZERO;
	}
	return ws2812_memory;
	}

void ws2812_init(int ledCount, enum colorScheme order)	{
	int i;
	if(ledCount < 0)
			return;
	for(i = 0; i < WS2812_MEMORY_SIZE; i++)
		ws2812_memory[i] = 0;
	ws2812_count = ledCount;
	ws2812_order = order;
	
}

void ws2812_setPixelColor(int pixel, int color)	{
	ws2812_pixels[pixel] = color;
}

void ws2812_fill(uint32_t color)	{
	int i;
	for(i = 0; i < ws2812_count; i++)
		ws2812_pixels[i] = color;
}

uint16_t* ws2812_show()	{
	int i, x;
	for(x = 0; x < ws2812_count; x++)
		for(i = 0; i < 24; i++){
			ws2812_memory[i + x * 32] = (ws2812_pixels[x] & 1 << i)? ONE : ZERO;
	}
		return ws2812_memory;
}