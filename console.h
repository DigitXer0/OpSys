#pragma once
#include "kprintf.h"
#include "disk.h"
#include "draw.h"

void clearBss(char* bssStart, char* bssEnd);

void console_init();

void clearScreen();

void console_draw_character(int x, int y, char ch, int isBold);

void console_scroll();

void console_putc(char c);

void kmemset(void *p, char c, int n);

void kmemcpy(void* dv, const void* sv, unsigned n);