#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>

void display(int expression_index, uint16_t color);

void display(char expression[][3], int len, uint16_t color);

#endif