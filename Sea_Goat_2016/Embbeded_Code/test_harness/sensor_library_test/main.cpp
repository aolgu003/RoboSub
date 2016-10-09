
/* 
Connections information:
MPU to stm32F401RE NUCLEO Connection information
VCC -> 3.3V
SCL -> D15
SDA -> D14
AD0 -> high

HMC5883L
VCC -> 3.3V
SCL -> D7
SDA -> D5

MS5803
VCC -> 3.3V
SCL -> D7
SDA -> D5

All grounds go to common ground
 */
 
#include "mbed.h"
#include "sensor.h"

int main() {
    sensor_init();
    while (1) {
        sensor_update();
        //print_data();
        sensor_msg();    
    }
}

/*#include "MPU6050.h"
#include "MS5803.h"
#include "MS5837.h"
#include "IMU.h"
#include "HMC5883L.h"

MPU6050 mpu6050;
DigitalOut led1(LED1);
//MS5837 pressure_sensor_1 = MS5803(I2C_SDA, I2C_SCL);
//MS5837 pressure_sensor_2 = MS5803(PB_4, PA_8);

HMC5883L compass(PB_4, PA_8);
MS5837 pressure_sensor_1 = MS5837(I2C_SDA, I2C_SCL, ms5837_addr_no_CS);
MS5837 pressure_sensor_2 = MS5837(PB_4, PA_8, ms5837_addr_no_CS);

//Serial pc(USBTX, USBRX);

int main()
{
    //Test Compass
    //pc.printf("Compass mode: %b\n", compass.getMode());
    int16_t mag[3] = {0};
    
    printf("Begining Initialization\n");
    
    int error_cnt = 0;
    
    float depth;
    float pressure1, depth1;
    float pressure2, depth2;
    
    pressure_sensor_1.MS5837Init();
    pressure_sensor_2.MS5837Init();
    pc.printf("Initialized begining readings\n");

    IMUinit(mpu6050);
    
    while(1) {
        pressure_sensor_1.Barometer_MS5837();
        pressure_sensor_2.Barometer_MS5837();
        pressure1 = pressure_sensor_1.MS5837_Pressure();
        pressure2 = pressure_sensor_2.MS5837_Pressure();
        
        //Do some error checking
        if ((pressure1 > 900 && pressure1 < 3000) && (pressure2 > 900 && pressure2 < 3000)) {
            depth1 = pressure_sensor_1.depth();
            depth2 = pressure_sensor_2.depth();
            
            depth = (depth1 + depth2) / 2;
            error_cnt = 0;
        } else if (pressure2 > 900 && pressure2 < 3000) {
            depth = pressure_sensor_2.depth();
            
            error_cnt = 0;
        } else if (pressure1 > 900 && pressure1 < 3000) {
            depth = pressure_sensor_1.depth();
            error_cnt = 0;
        } else {
            error_cnt++;
            if (error_cnt > 50) {
                //do something
                pc.printf("Pressure sensor error");   
            }
        }
        pc.printf("Depth is: %f\n", depth);
        
        //IMU Read
        IMUUpdate(mpu6050);

        //Compass read
        compass.getXYZ(mag);
        pc.printf("Mag values: %d, %d, %d\n", mag[0], mag[1], mag[2]); 
        pc.printf("Heading: %f\n",compass.getHeadingXYDeg());  
        
        led1 = !led1;
        //Thread::wait(500);
    }
}*/