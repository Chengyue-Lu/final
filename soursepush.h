#ifndef SOURESPUSH_H
#define SOURESPUSH_H
#include <Arduino.h>
#include "spi_w25q64.h"

class soursepush
{
public:
    soursepush(){};
    void soursew25q64(int length, char data[][3], uint32_t address);
    void sourseread(int length, char data[][3], uint32_t address);
    bool soursetest();
};
#endif