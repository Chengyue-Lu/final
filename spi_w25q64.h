#ifndef SPI_W25Q64_H
#define SPI_W25Q64_H

#include <Arduino.h>

// 定义引脚
#define SOFTSPI_SCK 5
#define SOFTSPI_MISO 6
#define SOFTSPI_MOSI 7
#define SOFTSPI_CS 8

// 定义引脚操作
#define SOFTSPI_CS_HIGH digitalWrite(SOFTSPI_CS, HIGH)
#define SOFTSPI_CS_LOW digitalWrite(SOFTSPI_CS, LOW)
#define SOFTSPI_SCK_HIGH digitalWrite(SOFTSPI_SCK, HIGH)
#define SOFTSPI_SCK_LOW digitalWrite(SOFTSPI_SCK, LOW)
#define SOFTSPI_MOSI_HIGH digitalWrite(SOFTSPI_MOSI, HIGH)
#define SOFTSPI_MOSI_LOW digitalWrite(SOFTSPI_MOSI, LOW)

// W25Q64指令表1
#define W25Q64_Write_Enable 0x06
#define W25Q64_Write_Disable 0x04
#define W25Q64_Read_Status_register_1 0x05
#define W25Q64_Read_Status_register_2 0x35
#define W25Q64_Write_Status_register 0x01
#define W25Q64_Page_Program 0x02
#define W25Q64_Quad_Page_Program 0x32
#define W25Q64_Block_Erase_64KB 0xD8
#define W25Q64_Block_Erase_32KB 0x52
#define W25Q64_Sector_Erase_4KB 0x20
#define W25Q64_Chip_Erase 0xC7
#define W25Q64_Erase_Suspend 0x75
#define W25Q64_Erase_Resume 0x7A
#define W25Q64_Power_down 0xB9
#define W25Q64_High_Performance_Mode 0xA3
#define W25Q64_Continuous_Read_Mode_Reset 0xFF
#define W25Q64_Release_Power_Down_HPM_Device_ID 0xAB
#define W25Q64_Manufacturer_Device_ID 0x90
#define W25Q64_Read_Uuique_ID 0x4B
#define W25Q64_JEDEC_ID 0x9F
#define W25Q64_DUMMY_BYTE 0xFF

// W25Q64指令集表2(读指令)
#define W25Q64_Read_Data 0x03
#define W25Q64_Fast_Read 0x0B
#define W25Q64_Fast_Read_Dual_Output 0x3B
#define W25Q64_Fast_Read_Dual_IO 0xBB
#define W25Q64_Fast_Read_Quad_Output 0x6B
#define W25Q64_Fast_Read_Quad_IO 0xEB
#define W25Q64_Octal_Word_Read_Quad_IO 0xE3

class SoftSPI
{
public:
    SoftSPI(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t cs){};
    void pin_init(uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t cs);
    void data_init();
    uint8_t Read_DO_Level(void);
    uint8_t SPI_SendByte(uint8_t data);
    void WriteEnable(void);
    void WriteDisable(void);
    void WaitForBusyStatus(void);
    void SectorErase(uint32_t Sector_Address);
    void PageWrite(uint32_t address, uint8_t *data, uint16_t dataSize);
    void ReadData(uint32_t address, uint8_t *data, uint16_t dataSize);
};
#endif