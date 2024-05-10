#include "display.h"
#include <Arduino.h>
#include "spi_w25q64.h"
#include <Adafruit_GFX.h>    // Core graphics library for all Adafruit displays
#include <Adafruit_ST7735.h> // Library specific to the ST7735 TFT display

extern Adafruit_ST7735 tft;
extern uint8_t mode_flag;
extern uint32_t play_record_flag;
extern Display dp;
extern SoftSPI W25Q64;

// expression index
//
void Display::dp1(int expression_index, uint16_t color)
{
    int len = expression_length[expression_index];
    uint32_t address = expression_address[expression_index];
    uint8_t expression[len * 3];

    // print the expression
    // for (int i = 0; i < len; i++)
    // {
    //     Serial.print(expression[3 * i]);
    //     Serial.print(" ");
    //     Serial.print(expression[3 * i + 1]);
    //     Serial.print(" ");
    //     Serial.print(expression[3 * i + 2]);
    //     Serial.print("\r\n");
    // }

    // read data from W25Q64
    W25Q64.ReadData(address, expression, len * 3);

    // display
    for (int i = 0; i < len * 3; i += 3)
    {
        tft.drawFastHLine(expression[i + 1], expression[i], expression[i + 2], color);
    }
}

void Display::dp2(char expression[][3], int len, uint16_t color)
{
    for (int i = 0; i < len; i++)
    {
        tft.drawFastHLine(expression[i][1], expression[i][0], expression[i][2], color);
    }
}

void Display::total_display()
{ // TODO 时间待定义，函数待填写
    switch (mode_flag)
    {
    case 0:
        // 展示待机动画
        if (play_record_flag == 100)
        {
        }
        break;
    case 1:
        // 展示睡眠动画
        if (play_record_flag == 1000000000)
        {
        }
    case 2:
        // 展示晕动画
        if (play_record_flag == 10)
        {
        }
        else if (play_record_flag == 5)
        {
        }
        break;
    case 3:
        // 展示疼痛动画
        if (play_record_flag == 10)
        {
        }
        else if (play_record_flag == 5)
        {
        }
        break;
    case 4:
        // 展示舒服动画
        break;
    case 5:
        // 展示捏脸动画
        break;
    case 6:
        // 展示朝左看动画
        break;
    case 7:
        // 展示朝右看动画
        break;
    case 8:
        // 展示害怕动画
        break;
    }
}