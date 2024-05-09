#include "soursepush.h"

extern SoftSPI W25Q64;
void soursepush::soursew25q64(int length, char data[][3], uint32_t address)
{

    char sequantial_data[3 * length];
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sequantial_data[3 * i + j] = data[i][j];
        }
    }
    W25Q64.PageWrite(address, (uint8_t *)sequantial_data, 3 * length);
}
void soursepush::sourseread(int length, char data[][3], uint32_t address)
{
    uint8_t data_rec[3 * length];
    W25Q64.ReadData(address, data_rec, 3 * length);
    // for (int i = 0; i < 3 * length; i++)
    // {
    //     Serial.print(data_rec[i]);
    //     Serial.print(" ");
    // }

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (data_rec[3 * i + j] != data[i][j])
            {
                // print the position of mismatch
                Serial.print("Mismatch at ");
                Serial.print(i);
                Serial.print(" ");
                return;
            }
        }
    }

    Serial.print("success\r\n");
    return;
}
bool soursepush::soursetest()
{
    uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    uint8_t data_rec[4];
    W25Q64.SectorErase(0x000000);
    W25Q64.PageWrite(0x000000, data, 4);
    W25Q64.ReadData(0x000000, data_rec, 4);
    for (int i = 0; i < 4; i++)
    {
        if (data_rec[i] != data[i])
        {
            return false;
        }
    }
    return true;
}