//#include "main.h"

enum colorScheme{
	RGB,
	BGR,
	GRB
};

uint16_t* getColorData(uint32_t);
void ws2812_init(int ledCount, enum colorScheme order);
void ws2812_setPixelColor(int pixel, int color);
void ws2812_fill(uint32_t color);
uint16_t* ws2812_show();