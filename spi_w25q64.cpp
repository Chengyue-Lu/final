#include <Arduino.h>

#include "spi_w25q64.h"

void SoftSPI::pin_init(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t cs)
{
    pinMode(sck, OUTPUT);
    pinMode(miso, INPUT);
    pinMode(mosi, OUTPUT);
    pinMode(cs, OUTPUT);
}
void SoftSPI::data_init()
{
    SOFTSPI_CS_HIGH;
    SOFTSPI_SCK_LOW;
    SOFTSPI_MOSI_LOW;
}
uint8_t SoftSPI::Read_DO_Level(void)
{
    return digitalRead(SOFTSPI_MISO);
}
uint8_t SoftSPI::SPI_SendByte(uint8_t data)
{
    uint8_t i;
    uint8_t Outdata = 0x00;
    for (i = 0; i < 8; i++)
    {
        if (data & (0x80 >> i))
        {
            SOFTSPI_MOSI_HIGH;
        }
        else
        {
            SOFTSPI_MOSI_LOW;
        }
        SOFTSPI_SCK_HIGH;
        delayMicroseconds(10);
        if (Read_DO_Level())
        {
            Outdata |= (0x80 >> i);
        }
        SOFTSPI_SCK_LOW;
    }
    return Outdata;
}
void SoftSPI::WriteEnable(void)
{
    SOFTSPI_CS_LOW;
    SPI_SendByte(W25Q64_Write_Enable);
    SOFTSPI_CS_HIGH;
}
void SoftSPI::WriteDisable(void)
{
    SOFTSPI_CS_LOW;
    SPI_SendByte(W25Q64_Write_Disable);
    SOFTSPI_CS_HIGH;
}
void SoftSPI::WaitForBusyStatus(void)
{
    uint16_t Timeout = 0xFFFF;
    SOFTSPI_CS_LOW;
    SPI_SendByte(W25Q64_Read_Status_register_1);
    while (Timeout > 0)
    {
        uint8_t status = SPI_SendByte(W25Q64_DUMMY_BYTE);
        if ((status & 0x01) == 0) // 检查忙状态是否结束
        {
            break;
        }
        Timeout--;
        if (Timeout == 0)
        {
            printf("W25Q64 ERROR \r\n");
            break;
        }
    }
    SOFTSPI_CS_HIGH;
}
void SoftSPI::SectorErase(uint32_t Sector_Address)
{
    WriteEnable(); // W25Q64写使能
    SOFTSPI_CS_LOW;
    SPI_SendByte(W25Q64_Sector_Erase_4KB);
    SPI_SendByte(Sector_Address >> 16); // 24位扇区地址
    SPI_SendByte(Sector_Address >> 8);
    SPI_SendByte(Sector_Address);
    SOFTSPI_CS_HIGH;
    WaitForBusyStatus(); // 等待 W25Q64 芯片的忙状态结束
    WriteDisable();      // W25Q64禁止写使能
}
void SoftSPI::PageWrite(uint32_t address, uint8_t *data, uint16_t dataSize)
{
    WriteEnable(); // W25Q64写使能
    SOFTSPI_CS_LOW;
    SPI_SendByte(W25Q64_Page_Program);
    SPI_SendByte((address & 0xFF0000) >> 16);
    SPI_SendByte((address & 0xFF00) >> 8);
    SPI_SendByte(address & 0xFF);
    if (dataSize <= 256)
    {
        for (uint16_t i = 0; i < dataSize; i++)
        {
            SPI_SendByte(data[i]);
        }
    }
    SOFTSPI_CS_HIGH;
    WaitForBusyStatus(); // 等待 W25Q64 芯片的忙状态结束
    WriteDisable();      // W25Q64禁止写使能
}
void SoftSPI::ReadData(uint32_t address, uint8_t *data, uint16_t dataSize)
{
    uint16_t i;
    SOFTSPI_CS_LOW;
    SPI_SendByte(W25Q64_Read_Data);
    SPI_SendByte((address & 0xFF0000) >> 16);
    SPI_SendByte((address & 0xFF00) >> 8);
    SPI_SendByte(address & 0xFF);
    for (i = 0; i < dataSize; i++)
    {
        data[i] = SPI_SendByte(W25Q64_DUMMY_BYTE);
    }
    SOFTSPI_CS_HIGH;
}
