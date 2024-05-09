#include "display.h"
#include <Arduino.h>
#include "spi_w25q64.h"
#include <Adafruit_GFX.h>    // Core graphics library for all Adafruit displays
#include <Adafruit_ST7735.h> // Library specific to the ST7735 TFT display

extern Adafruit_ST7735 tft;

extern SoftSPI W25Q64;

int expression_length[1] = {37};
uint32_t expression_address[3] = {0x000010};

// expression index
//
void display(int expression_index, uint16_t color)
{
    int len = expression_length[expression_index];
    uint32_t address = expression_address[expression_index];
    uint8_t expression[len * 3];

    // print the expression
    for (int i = 0; i < len; i++)
    {
        Serial.print(expression[3 * i]);
        Serial.print(" ");
        Serial.print(expression[3 * i + 1]);
        Serial.print(" ");
        Serial.print(expression[3 * i + 2]);
        Serial.print("\r\n");
    }

    // read data from W25Q64
    W25Q64.ReadData(address, expression, len * 3);

    // display
    for (int i = 0; i < len * 3; i += 3)
    {
        tft.drawFastHLine(expression[i + 1], expression[i], expression[i + 2], color);
    }
}

void display(char expression[][3], int len, uint16_t color)
{
    for (int i = 0; i < len; i++)
    {
        tft.drawFastHLine(expression[i][1], expression[i][0], expression[i][2], color);
    }
}