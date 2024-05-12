#include "sumsensor.h"
#define VOLTAGE_MIN 100
#define VOLTAGE_MAX 3500
#define PRESS_MIN1 10
#define PRESS_MAX1 10000
#define PRESS_MIN2 10
#define PRESS_MAX2 10000
#define SensorPin1 A0
#define SensorPin2 A1
#define SensorPin3 A2
#define SensorPin4 A3
extern Adafruit_MPU6050 mpu;
extern uint8_t mode_flag;
extern uint32_t play_record_flag;
void sumsensor::getmpudata()
{
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    sumacc[0] = a.acceleration.x;
    sumacc[1] = a.acceleration.y;
    sumacc[2] = a.acceleration.z;
    sumgyro[0] = g.gyro.x;
    sumgyro[1] = g.gyro.y;
    sumgyro[2] = g.gyro.z;
}
void sumsensor::getpressdata()
{
    int value1 = analogRead(SensorPin1);
    int value2 = analogRead(SensorPin2);
    int value3 = analogRead(SensorPin3);
    int VOLTAGE_A0 = map(value1, 0, 1023, 0, 5000);
    int VOLTAGE_A1 = map(value2, 0, 1023, 0, 5000);
    int VOLTAGE_A2 = map(value3, 0, 1023, 0, 5000);
    int PRESS_A0;
    int PRESS_A1;
    int PRESS_A2;
    if (VOLTAGE_A0 < VOLTAGE_MIN)
        PRESS_A0 = 0;
    else if (VOLTAGE_A0 > VOLTAGE_MAX)
        PRESS_A0 = PRESS_MAX1;
    else
        PRESS_A0 = map(VOLTAGE_A0, VOLTAGE_MIN, VOLTAGE_MAX, PRESS_MIN1, PRESS_MAX1);
    if (VOLTAGE_A1 < VOLTAGE_MIN)
        PRESS_A1 = 0;
    else if (VOLTAGE_A1 > VOLTAGE_MAX)
        PRESS_A1 = PRESS_MAX2;
    else
        PRESS_A1 = map(VOLTAGE_A1, VOLTAGE_MIN, VOLTAGE_MAX, PRESS_MIN2, PRESS_MAX2);
    if (VOLTAGE_A2 < VOLTAGE_MIN)
        PRESS_A2 = 0;
    else if (VOLTAGE_A2 > VOLTAGE_MAX)
        PRESS_A2 = PRESS_MAX2;
    else
        PRESS_A2 = map(VOLTAGE_A2, VOLTAGE_MIN, VOLTAGE_MAX, PRESS_MIN2, PRESS_MAX2);
    sumpress[0] = PRESS_A0;
    sumpress[1] = PRESS_A1;
    sumpress[2] = PRESS_A2;
}
void sumsensor::sumdata()
{
    getmpudata();
    getpressdata();
    accnorm = sqrt(sumacc[0] * sumacc[0] + sumacc[1] * sumacc[1] + sumacc[2] * sumacc[2]);
    if (sumpress[0] > 1000 && sumpress[0] < 2500 && Pin1_mode != 2)
        Pin1_mode = 1;
    else if (sumpress[0] > 2500)
        Pin1_mode = 2;

    if (sumpress[1] < 9400 && sumpress[1] > 500)
        Pin2_mode = 1;
    if (sumpress[2] < 9700 && sumpress[2] > 500)
        Pin3_mode = 1;

    if (accnorm > 16)
        being_shaked = true;
    else if (accnorm < 5)
        falling = true;
}
void sumsensor::dealthetft()
{
    play_record_flag--;
    // send signal to the tft screen
    // 除了在睡觉，静止的时候都不能打断。
    // 根据传感器信息判断该进入哪个表情，并给帧数赋值
    // TODO 帧数待定义


    if (mode_flag == 1 || mode_flag == 0)
    {
        if (being_shaked)
        {
            mode_flag = 2;
            play_record_flag = 42;
        }
        
        else if (Pin1_mode == 2)
        {
            mode_flag = 3;
            play_record_flag = 30;
        }
        else if (Pin1_mode == 1)
        {
            mode_flag = 4;
            play_record_flag = 18;
        }
        else if (Pin2_mode == 1 && Pin3_mode == 1)
        {
            mode_flag = 5;
            play_record_flag = 30;
        }
        else if (Pin2_mode == 1 && Pin3_mode == 0)
        {
            mode_flag = 7;
            play_record_flag = 30;
        }
        else if (Pin2_mode == 0 && Pin3_mode == 1)
        {
            mode_flag = 6;
            play_record_flag = 30;
        }


        // else if (falling)
        // {
        //     mode_flag = 8;
        //     play_record_flag = 10;
        // }
    }



    // being_shaked 最优先: 晕
    // Pin1_mode 优先级第二： 疼痛，舒服
    // Pin2_mode 和 Pin3_mode 优先级第三：捏脸/朝左看/朝右看
    // falling 优先级最低：害怕

    // 根据 mode_flag 的值来判断当的表情，根据 play_record_flag 的值来判断现在在第几帧，是否结束
    if (mode_flag != 0 && mode_flag != 1)
    {
        if (play_record_flag == 0)
        {
            mode_flag = 0;
            play_record_flag = 60;
            // 转移成待机模式
        }
        else
        {
            // 继续播放表情
        }
    }

    if (mode_flag == 0)
    {
        if (play_record_flag == 0)
        {
            mode_flag = 1;
            play_record_flag = 100;
        }
        else
        {
            // 继续播放表情
        }
    }

    if (mode_flag == 1)
    {
        // 根据传感器数据判断表情
        // 可能变化，也可能不变化
        if (play_record_flag == 0)
        {
            mode_flag = 0;
            play_record_flag = 60;
        }
        else {
            // 继续播放表情
        }
    }
    refresh();
}
void sumsensor::dataprint()
{
    Serial.println("acc:");
    Serial.print(sumacc[0]);
    Serial.print(" ");
    Serial.print(sumacc[1]);
    Serial.print(" ");
    Serial.print(sumacc[2]);
    Serial.println(" ");
    Serial.print("accnorm:");
    Serial.println(accnorm);
    Serial.println(" ");
    Serial.println("gyro:");
    Serial.print(sumgyro[0]);
    Serial.print(" ");
    Serial.print(sumgyro[1]);
    Serial.print(" ");
    Serial.print(sumgyro[2]);
    Serial.println(" ");
    Serial.println("press:");
    Serial.print(sumpress[0]);
    Serial.print(" ");
    Serial.print(sumpress[1]);
    Serial.print(" ");
    Serial.print(sumpress[2]);
    Serial.println(" ");
}