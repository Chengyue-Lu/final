#include <Arduino.h>
#include "spi_w25q64.h"
#include "soursepush.h"
#include <Wire.h>
#include "sourse.h"
SoftSPI W25Q64 = SoftSPI(SOFTSPI_SCK, SOFTSPI_MISO, SOFTSPI_MOSI, SOFTSPI_CS);
soursepush sp;

uint32_t address[31] = {
    0x001000,
    0x012000,
    0x014000,
    0x016000, // angry
    0x021000,
    0x023000,
    0x025000,
    0x027000,
    0x029000,
    0x02B000,
    0x02D000,
    0x02F000, // dizzy
    0x031000,
    0x033000,
    0x035000,
    0x037000, // happy
    0x041000,
    0x043000,
    0x045000, // left
    0x051000,
    0x053000,
    0x055000, // right
    0x061000,
    0x063000,
    0x065000,
    0x067000,
    0x069000, // sleep
    0x071000,
    0x073000,
    0x075000,
    0x077000, // wake
              // TODO pinched,scared
};
uint8_t data_length[31] = {
    30, 55, 83, 92,
    133, 129, 139, 137, 133, 131, 139, 137,
    37, 61, 84, 95,
    94, 93, 93,
    94, 92, 90,
    41, 54, 128, 126, 132,
    106, 83, 69, 61};

void setup()
{
  Serial.begin(9600);
  W25Q64.pin_init(SOFTSPI_SCK, SOFTSPI_MISO, SOFTSPI_MOSI, SOFTSPI_CS);
  for (int i = 0; i < 3; i++)
  {
    if (sp.soursetest())
    {
      Serial.println("W25Q64 successful!");
      break;
    }
    else
      delay(500);
  }
  // W25Q64.ChipErase();
  Serial.println("erase successful!");
  // delay(1000);

  delay(1000);
}

void loop()
{
  int x = 1;
  delay(1000);
  Serial.print("x");
}
