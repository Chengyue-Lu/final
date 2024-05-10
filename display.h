#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>

class Display
{
private:
    /* data */
public:
    display(){};
    uint32_t *expression_address;
    uint8_t *expression_length;
    void dp1(int expression_index, uint16_t color);
    void dp2(char expression[][3], int len, uint16_t color);
    void total_display();
};

#endif