/*
 * LCD_GFX.c
 *
 * Created: 9/20/2021 6:54:25 PM
 *  Author: You
 */ 

#include "LCD_GFX.h"
#include "ST7735.h"

/******************************************************************************
* Local Functions
******************************************************************************/



/******************************************************************************
* Global Functions
******************************************************************************/

/**************************************************************************//**
* @fn			uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
* @brief		Convert RGB888 value to RGB565 16-bit color data
* @note
*****************************************************************************/
//uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
//{
//	return ((((31*(red+4))/255)<<11) | (((63*(green+2))/255)<<5) | ((31*(blue+4))/255));
//}

uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue) {
    uint16_t r = (red >> 3) & 0x1F;   // Red ???5??
    uint16_t g = (green >> 2) & 0x3F; // Green ???6??
    uint16_t b = (blue >> 3) & 0x1F;  // Blue ???5??
    return (r << 11) | (g << 5) | b;  // ??? 16 ????
}


/**************************************************************************//**
* @fn			void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color)
* @brief		Draw a single pixel of 16-bit rgb565 color to the x & y coordinate
* @note
*****************************************************************************/
void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color) {
	LCD_setAddr(x,y,x,y);
	SPI_ControllerTx_16bit(color);
}

/**************************************************************************//**
* @fn			void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor)
* @brief		Draw a character starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor){
	uint16_t row = character - 0x20;		//Determine row of ASCII table starting at space
	int i, j;
	if ((LCD_WIDTH-x>7)&&(LCD_HEIGHT-y>7)){
		for(i=0;i<5;i++){
			uint8_t pixels = ASCII[row][i]; //Go through the list of pixels
			for(j=0;j<8;j++){
				if ((pixels>>j)&1==1){
					LCD_drawPixel(x+i,y+j,fColor);
				}
				else {
					LCD_drawPixel(x+i,y+j,bColor);
				}
			}
		}
	}
}


/******************************************************************************
* LAB 4 TO DO. COMPLETE THE FUNCTIONS BELOW.
* You are free to create and add any additional files, libraries, and/or
*  helper function. All code must be authentically yours.
******************************************************************************/

/**************************************************************************//**
* @fn			void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius,uint16_t color)
* @brief		Draw a colored circle of set radius at coordinates
* @note
*****************************************************************************/
void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint16_t color)
{
    int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x; // Midpoint decision parameter

    while (y <= x) {
        LCD_drawPixel(x0 + x, y0 + y, color);
        LCD_drawPixel(x0 + y, y0 + x, color);
        LCD_drawPixel(x0 - y, y0 + x, color);
        LCD_drawPixel(x0 - x, y0 + y, color);
        LCD_drawPixel(x0 - x, y0 - y, color);
        LCD_drawPixel(x0 - y, y0 - x, color);
        LCD_drawPixel(x0 + y, y0 - x, color);
        LCD_drawPixel(x0 + x, y0 - y, color);
        y++;
        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1; // Inside
        } else {
            x--;
            decisionOver2 += 2 * (y - x) + 1; // Outside
        }
    }
}



/**************************************************************************//**
* @fn			void LCD_drawLine(short x0,short y0,short x1,short y1,uint16_t c)
* @brief		Draw a line from and to a point with a color
* @note
*****************************************************************************/
void LCD_drawLine(short x0, short y0, short x1, short y1, uint16_t color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        LCD_drawPixel(x0, y0, color); // Draw pixel at current point
        if (x0 == x1 && y0 == y1) break; // Reached the end point
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}


/**************************************************************************//**
* @fn			void LCD_drawBlock(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint16_t color)
* @brief		Draw a colored block at coordinates
* @note
*****************************************************************************/
void LCD_drawBlock(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color)
{
    for (uint8_t x = x0; x <= x1; x++) {
        for (uint8_t y = y0; y <= y1; y++) {
            LCD_drawPixel(x, y, color); // Set each pixel to the specified color
        }
    }
}

/**************************************************************************//**
* @fn			void LCD_setScreen(uint16_t color)
* @brief		Draw the entire screen to a color
* @note
*****************************************************************************/
void LCD_setScreen(uint16_t color) 
{
    LCD_setAddr(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1); // Set address for the whole screen
    for (uint32_t i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) {
        SPI_ControllerTx_16bit(color); // Send the color data to fill the screen
    }
}

/**************************************************************************//**
* @fn			void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fg, uint16_t bg)
* @brief		Draw a string starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fColor, uint16_t bColor)
{
    while (*str) {
        LCD_drawChar(x, y, *str, fColor, bColor); // Draw each character
        x += 6; // Move to the next character position (assuming 5x8 font + 1 space)
        str++;
    }
}


/**************************************************************************//**
* @fn            void LCD_drawLargeChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor)
* @brief         Draw a larger character (3x scale) starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawLargeChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor) {
    uint16_t row = character - 0x20; // Determine row of ASCII table starting at space
    int i, j, k, l;
    if ((LCD_WIDTH - x > 21) && (LCD_HEIGHT - y > 24)) { // Ensure character fits on screen
        for (i = 0; i < 5; i++) {
            uint8_t pixels = ASCII[row][i]; // Go through the list of pixels
            for (j = 0; j < 8; j++) {
                for (k = 0; k < 3; k++) { // Scale width by 3
                    for (l = 0; l < 3; l++) { // Scale height by 3
                        if ((pixels >> j) & 1) {
                            LCD_drawPixel(x + i * 3 + k, y + j * 3 + l, fColor);
                        } else {
                            LCD_drawPixel(x + i * 3 + k, y + j * 3 + l, bColor);
                        }
                    }
                }
            }
        }
    }
}

