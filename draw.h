#pragma once

#include "font.h"
#include "util.h"

struct MultibootInfo* mbi;

volatile unsigned char* framebuffer;

#define FRAMEBUFFER_PITCH mbi->mbiFramebufferPitch
#define FRAMEBUFFER_WIDTH mbi->mbiFramebufferWidth
#define FRAMEBUFFER_HEIGHT mbi->mbiFramebufferHeight
#define RED_MASK mbi->mbiFramebufferRedMask
#define BLUE_MASK mbi->mbiFramebufferBlueMask
#define GREEN_MASK mbi->mbiFramebufferGreenMask
#define RED_POS mbi->mbiFramebufferRedPos
#define GREEN_POS mbi->mbiFramebufferGreenPos
#define BLUE_POS mbi->mbiFramebufferBluePos

int get8bitColor(int r, int g, int b);

char color2char(char* color);

void set_pixel(int x, int y, unsigned char r2, unsigned char g2, unsigned char b2 );

void drawRect(int width, int height, int startX, int startY, unsigned char r1, unsigned char g1, unsigned char b1 );