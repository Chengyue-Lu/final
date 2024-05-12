# first
本代码是用于借助arduinonano，TFT显示屏，mpu6050陀螺仪传感器、压力传感器以及w25q64存储模块实现的一个可交互电子宠物项目的程序部分。
如果你要使用本代码，你的arduinoIDE或者其他平台中至少要包含以下库文件
+ Adafruit_GFX.h         ———— Core graphics library for all Adafruit displays
+ Adafruit_ST7735.h      ———— Library specific to the ST7735 TFT display
+ Adafruit_MPU6050.h     ———— Library for MPU6050 accelerometer and gyroscope
+ Adafruit_Sensor.h      ———— Generic sensor library needed for the MPU6050
+ Wire.h                 ———— Wire library for I2C communication (for communication with MPU6050)
此外，接线请参考final.ino文件注释中的引脚标注。（部分引脚是可自行定义的，具体可以参考引脚宏定义部分）
# second
目前本代码实现了对于压力，加速度等的屏幕反馈，后续仍会继续对本项目进行进一步的开发拓展，如添加声音反馈部分，更新屏幕显示部分使得动画更为连贯而优美等。
