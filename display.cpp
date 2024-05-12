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
    if (len * 3 > 256)
    {
        W25Q64.ReadData(address, expression, 256);
        W25Q64.ReadData(address + 256 * 16, expression + 256, len * 3 - 256);
    }
    else
    {
        W25Q64.ReadData(address, expression, len * 3);
    }

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

void Display::clear_screen()
{
    // tft.fillScreen(ST7735_BLACK);
    // RST: 4
    // digitalWrite(4, LOW);
    // delayMicroseconds(10);
    // digitalWrite(4, HIGH);
    tft.fillScreen(ST7735_BLACK);
}

void Display::total_display()
{ // TODO 时间待定义，函数待填写
    int expression_index = -1;
    switch (mode_flag)
    {
    case 0:
        // 展示待机动画
        if (play_record_flag % 20 == 0)
        {
            Serial.println("待机");
            clear_screen();
            dp1(15, ST7735_WHITE);
        }
        else if (play_record_flag % 20 == 10) {
            Serial.println("待机闭眼");
            clear_screen();
            dp1(12, ST7735_WHITE);
        }
    
        break;
    case 1:
        // 展示睡眠动画
        if (play_record_flag == 100)
        {
            clear_screen();
            dp1(15, ST7735_WHITE);
        } 
        else if (play_record_flag == 97) {
            clear_screen();
            dp1(14, ST7735_WHITE);
        }
        else if (play_record_flag == 94) {
            clear_screen();
            dp1(13, ST7735_WHITE);
        }
        else if (play_record_flag == 91) {
            clear_screen();
            dp1(12, ST7735_WHITE);
        }
        else if (play_record_flag > 80) {

        }
        else if (play_record_flag % 20 == 0) {
            clear_screen();
            dp1(22, ST7735_WHITE);
        }
        else if (play_record_flag % 20 == 14) {
            clear_screen();
            dp1(23, ST7735_WHITE);
        } else if (play_record_flag == 9) {
            clear_screen();
            dp1(27, ST7735_WHITE);
        } else if (play_record_flag == 6) {
            clear_screen();
            dp1(28, ST7735_WHITE);
        } else if (play_record_flag == 3) {
            clear_screen();
            dp1(29, ST7735_WHITE);
        }
        else if (play_record_flag % 20 == 8 && play_record_flag >= 20) {
            clear_screen();
            dp1(26, ST7735_WHITE);
        } 
        break;
    case 2:
        // 展示晕动画

        if (play_record_flag % 24 == 0)
        {
            clear_screen();
            dp1(4, ST7735_WHITE);
        }
        else if (play_record_flag % 24 == 21)
        {
            clear_screen();
            dp1(5, ST7735_WHITE);
        }
        else if (play_record_flag % 24 == 18)
        {
            clear_screen();
            dp1(6, ST7735_WHITE);
        }
        else if (play_record_flag % 24 == 15)
        {
            clear_screen();
            dp1(7, ST7735_WHITE);
        }
        else if (play_record_flag % 24 == 12)
        {
            clear_screen();
            dp1(8, ST7735_WHITE);
        }
        else if (play_record_flag % 24 == 9)
        {
            clear_screen();
            dp1(9, ST7735_WHITE);
        }
        else if (play_record_flag % 24 == 6)
        {
            clear_screen();
            dp1(10, ST7735_WHITE);
        }
        else if (play_record_flag % 24 == 3)
        {
            clear_screen();
            dp1(11, ST7735_WHITE);
        }
        break;
    case 3:
        // 展示疼痛动画
        if (play_record_flag % 10 == 0)
        {
            Serial.println("疼痛");
            clear_screen();
            dp1(3, ST7735_WHITE);
        }
        else if (play_record_flag % 10 == 2)
        {
            Serial.println("疼痛");
            clear_screen();
            dp1(0, ST7735_WHITE);
        }
        break;
    case 4:
        // 展示舒服动画
        if (play_record_flag == 18)
        {
            Serial.println("舒服");
            clear_screen();
            dp1(34, ST7735_WHITE);
        }
        else if (play_record_flag == 13)
        {
            Serial.println("舒服");
            clear_screen();
            dp1(35, ST7735_WHITE);
        }
        else if (play_record_flag == 8)
        {
            Serial.println("舒服");
            clear_screen();
            dp1(36, ST7735_WHITE);
        }
        else if (play_record_flag == 3)
        {
            Serial.println("舒服");
            clear_screen();
            dp1(37, ST7735_WHITE);
        }
        break;
    case 5:
        // 展示捏脸动画
        if (play_record_flag == 30)
        {
            Serial.println("捏脸");
            clear_screen();
            dp1(32, ST7735_WHITE);
        }
        else if (play_record_flag == 27)
        {
            Serial.println("捏脸");
            clear_screen();
            dp1(33, ST7735_WHITE);
        }
        else if (play_record_flag == 20) {
            Serial.println("捏脸");
            clear_screen();
            dp1(32, ST7735_WHITE);
        }
        else if (play_record_flag == 17) {
            Serial.println("捏脸");
            clear_screen();
            dp1(33, ST7735_WHITE);
        }
        else if (play_record_flag == 10) {
            Serial.println("捏脸");
            clear_screen();
            dp1(32, ST7735_WHITE);
        }
        else if (play_record_flag == 7) {
            Serial.println("捏脸");
            clear_screen();
            dp1(31, ST7735_WHITE);
        }
        
        
        break;
    case 6:
        // 展示朝右看动画
        if (play_record_flag == 30)
        {
            
            // Serial.println("look left");
            clear_screen();
            dp1(17, ST7735_WHITE);
        }
        else if (play_record_flag == 25)
        {   
            // Serial.println("look left");
            clear_screen();
            dp1(18, ST7735_WHITE);
        }
        else if (play_record_flag == 10)
        {   
            // Serial.println("look left");
            clear_screen();
            dp1(17, ST7735_WHITE);
        }
        else if (play_record_flag == 5)
        {
            // Serial.println("look left");
            clear_screen();
            dp1(16, ST7735_WHITE);
        }
        break;
    case 7:
        // 展示朝左看动画
        if (play_record_flag == 30)
        {
            // Serial.println("look right");
            clear_screen();
            dp1(20, ST7735_WHITE);
        }
        else if (play_record_flag == 25)
        {
            // Serial.println("look right");
            clear_screen();
            dp1(21, ST7735_WHITE);
        }
        else if (play_record_flag == 10)
        {
            // Serial.println("look right");
            clear_screen();
            dp1(20, ST7735_WHITE);
        }
        else if (play_record_flag == 5)
        {
            // Serial.println("look right");
            clear_screen();
            dp1(19, ST7735_WHITE);
        }
        break;
    case 8:
        // 展示害怕动画
        if (play_record_flag == 20)
        {
            Serial.println("害怕");
            clear_screen();
            // print some words
            tft.setCursor(0, 0);
            tft.setTextColor(ST7735_WHITE);
            tft.setTextSize(2);
            tft.println("I'm scared");
            
        }
        break;
    }
}