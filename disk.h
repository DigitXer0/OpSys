#pragma once

void outb(unsigned short port, unsigned char value);

void outw(unsigned short port, unsigned short value);

unsigned char inb(unsigned short port);

unsigned short inw(unsigned short port);

int isBusy();

void disk_read_sector(unsigned sector, void* datablock);

void disk_write_sector(unsigned sector, const void* datablock);