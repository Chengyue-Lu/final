#include <Adafruit_GFX.h>    // Core graphics library for all Adafruit displays
#include <Adafruit_ST7735.h> // Library specific to the ST7735 TFT display

#include <Adafruit_MPU6050.h> // Library for MPU6050 accelerometer and gyroscope
#include <Adafruit_Sensor.h>  // Generic sensor library needed for the MPU6050
#include <Wire.h>             // Wire library for I2C communication

#include "spi_w25q64.h"
#include "soursepush.h"
#include "display.h"
#include "sumsensor.h"

// define all the pins
// TFT
// SCK: 13, SDI: 11, CS: 10, RS: 9, RST: 4
// MPU6050
// SCL: A5, SDA: A4
// W25Q64
// SCK: 5, MISO: 6, MOSI: 7, CS: 8
// rotary encoder
// ADC: A3
// press sensor
// upADC: A0 left ADC: A1 right ADC: A2

// create all structs
// Pin definitions for the Adafruit 1.44" TFT with ST7735
#define TFT_CS 10 // Chip select line for TFT display
#define TFT_RST 4 // Reset line for TFT (optional use, can connect to Arduino RESET pin)
#define TFT_DC 9

// Create an ST7735 object. Since we are using hardware SPI, MOSI and SCK are set automatically
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_MPU6050 mpu;
bool mpu_able = true;
SoftSPI W25Q64 = SoftSPI(SOFTSPI_SCK, SOFTSPI_MISO, SOFTSPI_MOSI, SOFTSPI_CS);
soursepush sp;
sumsensor ss;

#include <avr/pgmspace.h>

uint8_t mode_flag = 0;
// 0: 开机/待机 1：睡觉 2：晕 3： 疼痛 4： 舒服 5： 捏脸 6：朝左看 7：朝右看 8：害怕
uint32_t play_record_flag = 600;
const long _10msTime = 10; // 10 ms
unsigned long _10msLastTime;
const long _100msTime = 100; // 100 ms
unsigned long _100msLastTime;
const long _1sTime = 1000; // 1 second
unsigned long _1sLastTime;
long a = 0;
long b = 0;
long c = 0;
long min = 0;

void setup()
{
  // begin serial with bode 9600
  Serial.begin(9600);
  // befin tft spi
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  Serial.println("TFT seccessful!");
  // begin mpu
  if (!mpu.begin())
  {
    mpu_able = false; // If MPU6050 initialization fails, update flag
    Serial.println("Failed to find MPU6050 chip");
  }
  else
  {
    Serial.println("MPU6050 seccessful!");
  }
  // begin w25q64
  W25Q64.pin_init(SOFTSPI_SCK, SOFTSPI_MISO, SOFTSPI_MOSI, SOFTSPI_CS);
  for (int i = 0; i < 3; i++)
  {
    if (sp.soursetest())
    {
      Serial.println("W25Q64 seccessful!");
      break;
    }
    else
      delay(500);
  }

  Serial.println("setup end!");

  // TODO: 开机动画
}

void loop()
{
  TimeProc();
}

void TimeProc()
{
  // 1s执行一次
  if ((millis() - _1sLastTime) >= _1sTime)
  {

    _1sLastTime = millis();
    c++;
    // test();
    clock();
  }
  // 100ms执行一次
  if ((millis() - _100msLastTime) >= _100msTime)
  {
    _100msLastTime = millis();
    ss.sumdata();
    ss.dataprint();
    b++;
  }
  // 10ms执行一次
  if ((millis() - _10msLastTime) >= _10msTime)
  {
    _10msLastTime = millis();
    a++;
  }
  if (a >= 10)
    a = 0;
  if (b >= 10)
    b = 0;
  if (c >= 60)
  {
    min++;
    c = 0;
  }
}

void test()
{
  // uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
  // uint8_t data_rec[4];
  // W25Q64.SectorErase(0x000000);
  // W25Q64.ReadData(0x000000, data_rec, 4);
  // Serial.print("data_rec_old: ");
  // for (int i = 0; i < 4; i++)
  // {
  //   Serial.print(data_rec[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
  // W25Q64.PageWrite(0x000000, data, 4);
  // W25Q64.ReadData(0x000000, data_rec, 4);
  // Serial.print("data_rec_new: ");
  // for (int i = 0; i < 4; i++)
  // {
  //   Serial.print(data_rec[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
  // sp.soursew25q64(37, data, 0x000010);
  // sp.sourseread(37, data, 0x000010);
  // W25Q64.SectorErase(0x000010);
}

void clock()
{
  Serial.print(min);
  Serial.print("min ");
  Serial.print(c);
  Serial.print("s ");
  Serial.println();
}