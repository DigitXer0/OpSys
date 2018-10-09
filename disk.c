#include "disk.h"
#include "console.h"

void outb(unsigned short port, unsigned char value){
	asm volatile( "out dx,al"
		:
		: "a"(value), "d"(port)
		: "memory"
	);
}

void outw(unsigned short port, unsigned short value){
	asm volatile("out dx,ax"
		:
		: "a"(value),"d"(port)
		: "memory"
	);
}

unsigned char inb(unsigned short port)
{
	unsigned value;
	asm volatile("in al, dx" : "=a"(value): "d"(port) );
	return (unsigned char) value;
}

unsigned short inw(unsigned short port)
{
	unsigned value;
	asm volatile("in ax, dx" : "=a"(value): "d"(port) );
	return (unsigned short) value;
}

int isBusy()
{
	return inb(0x1f7) & 0x80;
}

void disk_read_sector(unsigned sector, void* datablock)
{
	while(isBusy())
		;	
	
	outw(0x1f6, 0xe0 | sector >> 24);
	outw(0x3f6, 2);
	outw(0x1f2, 1);
	outw(0x1f3, sector >> 0);
	outw(0x1f4, sector >> 8);
	outw(0x1f5, sector >> 16);
	outw(0x1f7, 0x20);

	while(1)
	{
		while(isBusy())
			;

		if(inw(0x1f7) & 0x8)
			break;
		else if(inw(0x1f7) & 0x0 || inw(0x1f7) & 0x20)
		{
			kprintf("Error!\n\n Bit 0: %d \n\n Bit 5: %d\n\n", inw(0x1f7) & 0x0, inw(0x1f7) & 0x20);
			break;
		}
	}


		while(isBusy())
			;

	unsigned short* p = (unsigned short*)datablock;

	for(int i = 0; i < 256; ++i)
	{
		unsigned short d = inw(0x1f0);
		*p = d;
		p++;
	}
}

void disk_write_sector(unsigned sector, const void* datablock)
{
	while(isBusy())
		;

	outw(0x1f6, 0xe0 | sector >> 24);
	outw(0x3f6, 2);
	outw(0x1f2, 1);
	outw(0x1f3, sector >> 0);
	outw(0x1f4, sector >> 8);
	outw(0x1f5, sector >> 16);
	outw(0x1f7, 0x30);
	while(1)
	{
		while(isBusy())
			;

		if(inw(0x1f7) & 0x8)
			break;
		else if(inw(0x1f7) & 0x0 || inw(0x1f7) & 0x20)
		{
			kprintf("Error!\n\n Bit 0: %d \n\n Bit 5: %d\n\n", inw(0x1f7) & 0x0, inw(0x1f7) & 0x20);
		}
	}

	const short* p = (short*)datablock;

	while(isBusy())
		;

	for(int i = 0; i < 256; i++)
	{
			outw(0x1f0, *p);			
			p++;
	}
	outw(0x1f7, 0xe7);
}

void disk_read_block()
{
	
}