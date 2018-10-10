#include "draw.h"

int get8bitColor(int r, int g, int b)
{
	int color = (b*6/256)*36 + (g*6/256)*6 + (r*6/256);
	return color;
}

char color2char(char* color)
{
	color[0] >>= (8-RED_MASK);
	color[1] >>= (8-GREEN_MASK);
	color[2] >>= (8-BLUE_MASK);

	unsigned char colorValue = (color[2] << BLUE_POS) | (color[1] << GREEN_POS) | (color[0] << (RED_POS));
	return colorValue;
}

void set_pixel(int x, int y, unsigned char r2, unsigned char g2, unsigned char b2)
{
	volatile unsigned char* temp = framebuffer + (2 * x +(y * FRAMEBUFFER_PITCH));

	r2 >>= (8-RED_MASK);
	g2 >>= (8-GREEN_MASK);
	b2 >>= (8-BLUE_MASK);

	unsigned int colorValue = (b2 << BLUE_POS) | (g2 << GREEN_POS) | (r2 << (RED_POS));
	*(unsigned short*)temp = colorValue;
}

void drawRect(int width, int height, int startX, int startY, unsigned char r1, unsigned char g1, unsigned char b1)
{
	for(int y = startY; y < startY + height; ++y)
	{
		for(int x = startX; x < startX + width; ++x)
		{
			set_pixel(x, y, r1, g1, b1);
		}
	}
}