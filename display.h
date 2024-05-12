#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>

class Display
{
private:
    /* data */
public:
    display(){};
    uint32_t expression_address[42] = {
        0x001000,
        0x012000,
        0x014000,
        0x016000, // fury 3
        0x021000,
        0x023000,
        0x025000,
        0x027000,
        0x029000,
        0x02B000,
        0x02D000,
        0x02F000, // dizzy 11
        0x031000,
        0x033000,
        0x035000,
        0x037000, // happy 15
        0x041000,
        0x043000,
        0x045000, // left 18 
        0x051000,
        0x053000,
        0x055000, // right 21
        0x061000,
        0x063000,
        0x065000,
        0x067000,
        0x069000, // sleep 26
        0x071000,
        0x073000,
        0x075000,
        0x077000, // wake 30
        0x081000,
        0x083000,
        0x085000, // pinch 33
        0x091000,
        0x093000,
        0x095000,
        0x097000,
        0x07A000,
        0x07C000,
        0x09D000,
        0x09F000, //wowie 41
                  // TODO pinched,scared
    };
    uint8_t expression_length[42] = {
        30, 55, 83, 92, // angry
        133, 129, 139, 137, 133, 131, 139, 137, //dizzy
        37, 61, 84, 95, //happy
        94, 93, 93, //left
        94, 92, 90, //right
        41, 54, 128, 126, 132, //sleep
        106, 83, 69, 61, //wake
        105, 122, 151, // pinched
        159, 154, 168, 169, 167, 160, 170, 167 // wowie
        };

    void dp1(int expression_index, uint16_t color);
    void dp2(char expression[][3], int len, uint16_t color);
    void clear_screen();
    void total_display();
};

#endif