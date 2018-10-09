#include "console.h"

int row = 0, col = 0;

char lastChar;
int isBold = 0;

char gray[3] = {40,68,80};
int light_gray[3] = {100, 200, 200};

void clearBss(char* bssStart, char* bssEnd)
{
	for(;bssStart != bssEnd; bssStart++)
	{
		*bssStart = 0;
	}
}

void console_init()
{
	framebuffer = (volatile unsigned char*)
		(unsigned)mbi->mbiFramebufferAddress;

	clearScreen();
}

void clearScreen()
{
	for(int y = 0; y < FRAMEBUFFER_HEIGHT; ++y)
	{
		volatile unsigned char* fb = framebuffer + y * FRAMEBUFFER_PITCH;
		kmemset((void*)(volatile unsigned char*)fb , get8bitColor(30, 50, 50), 1600);
	}
	col = row = 0;
}

void console_draw_character(int x, int y, char ch, int isBold)
{
    int *C = (int*)(font_data[(int)ch]);
    int cx, cy;

    for(cy=0; cy<CHAR_HEIGHT; ++cy)
    {
        for(cx=0;cx<CHAR_WIDTH;++cx)
        {
            if((MASK_VALUE>>cx)&C[cy])
                set_pixel(cx+x,cy+y,light_gray[0],light_gray[1],light_gray[2]);
            else if(!isBold)
                set_pixel(cx+x,cy+y,gray[0],gray[1],gray[2]);
        }
    }
}

void console_scroll()
{
	if(col > FRAMEBUFFER_WIDTH - CHAR_WIDTH)
	{
		col = 0;
		row += CHAR_HEIGHT;
	}
	if(row > FRAMEBUFFER_HEIGHT - CHAR_HEIGHT)
	{
		kmemcpy((void*)(volatile unsigned char*)framebuffer, 
			(void*)(volatile unsigned char*)framebuffer + (FRAMEBUFFER_PITCH * CHAR_HEIGHT),
			(FRAMEBUFFER_HEIGHT - CHAR_HEIGHT) * FRAMEBUFFER_PITCH);

		for(int y = 0; y <= CHAR_HEIGHT; ++y)
		{
			volatile unsigned char* fb = framebuffer + FRAMEBUFFER_PITCH * (FRAMEBUFFER_HEIGHT - y);
			kmemset((void*)(volatile unsigned char*)fb, get8bitColor(30, 50, 50), FRAMEBUFFER_WIDTH * 2);
		}
		
		row -= CHAR_HEIGHT;
		col = 0;
	}
}

void console_putc(char c)
{
	console_scroll();
	if(c == '\f')
	{
		clearScreen();
	}
	else if(c == '\t')
	{
		if(!(col%80))
		{
			for(int i = 0; i < 8; ++i)
			{
				if(col > FRAMEBUFFER_WIDTH)
				{
					col = 0;
					row += CHAR_HEIGHT;
					break;
				}
				else
				{
					console_draw_character(col, row, ' ', 0);
					col += CHAR_WIDTH;
				}
			}
		} else
		{
		
			while(col%80)
			{
				if(col > FRAMEBUFFER_WIDTH)
				{
					col = 0;
					row += CHAR_HEIGHT;
					break;
				}
				else
				{
					console_draw_character(col, row, ' ', 0);
					col += CHAR_WIDTH;
				}
			}
		}
	}
	else if(c == '\n')
	{
		while(col < 800)
		{
			console_draw_character(col, row, ' ', 0);
			col += CHAR_WIDTH;
		}
		row += CHAR_HEIGHT;
		col = 0;
	}
	else if(c == '\x7f' && !(col == 0 && row == 0))
	{
		if(col == 0)
		{
			row -= CHAR_HEIGHT;
			col = FRAMEBUFFER_WIDTH - CHAR_WIDTH;
		} else col -= CHAR_WIDTH;
		console_draw_character(col, row, ' ',0);
	}
	else if(c == '\r')
	{
		col = 0;
	}
	else if(c == '\b')
	{
		isBold = 1;
	}
	else
	{
		if(isBold)
		{
			if(c == lastChar)
			{
				col -= CHAR_WIDTH;
				console_draw_character(col, row, c, 0);
				++col;
				console_draw_character(col, row, c, 1);
				col += (CHAR_WIDTH - 1);
			} else
			{
				col -= CHAR_WIDTH;
				console_draw_character(col, row, c, 0);
				col += CHAR_WIDTH;
			}
			isBold = 0;
		} else
		{
			if(row < FRAMEBUFFER_HEIGHT - CHAR_HEIGHT)
			{
				lastChar = c;
				console_draw_character(col, row, c, 0);
				col += CHAR_WIDTH;
			}
			
		}
	}	
	outb(0x3f8, c);
}

void kmemset(void *p, char c, int n)
{
	char *v = (char*)p;
	for(int i = 0; i < n; ++i)
	{
		v[i] = c;
	}
}

void kmemcpy(void* dv, const void* sv, unsigned n)
{
	char* d = (char*)dv;
	const char* s = (char*)sv;
	while(n--)
	{
		*d++ = *s++;
	}
}

