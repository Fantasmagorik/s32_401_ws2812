//#include "main.h"
#define ws2812_count  13
enum colorScheme{
	RGB,
	BGR,
	GRB,
	BRG
};
union ws2812_pixel{
	uint32_t pixelColor;
	uint8_t byteColor[4];

};

#define colorRED 		 0xff0000
#define colorGREEN 	 0xff00
#define colorBLUE		 0xff
#define colorWHITE	 0xffffff
#define colorPINK 	 0xff0064
#define colorCYAN 	 0xffff
#define colorORANGE	 0xe65000

typedef union ws2812_pixel _color;

uint32_t getStepColor(uint32_t sourceColor, uint32_t needColor, uint32_t currentStep, uint32_t countOfSteps);
uint16_t* getColorData(uint32_t);
void ws2812_init(int ledCount, enum colorScheme order);
void ws2812_setPixelColor(int pixel, int color);
void ws2812_fill(uint32_t color);
void ws2812_show();