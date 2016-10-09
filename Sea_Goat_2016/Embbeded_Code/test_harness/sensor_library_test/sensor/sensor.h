#include "MPU6050.h"
#include "MS5803.h"
#include "MS5837.h"
#include "IMU.h"
#include "HMC5883L.h"

MPU6050 mpu6050;
HMC5883L compass(PB_4, PA_8);
MS5837 pressure_sensor_1 = MS5837(I2C_SDA, I2C_SCL, ms5837_addr_no_CS);
MS5837 pressure_sensor_2 = MS5837(PB_4, PA_8, ms5837_addr_no_CS);
float depth, depth1, depth2, heading;
float pressure1, pressure2;
int error_cnt = 0;
int16_t mag[3] = {0};


void sensor_init() {
    wait_ms(100);
    pressure_sensor_1.MS5837Init();
    wait_ms(100);
    pressure_sensor_2.MS5837Init();
    wait_ms(100);
    IMUinit(mpu6050);
    wait_ms(100);
    
    pc.printf("================================\n");
    pc.printf("Initialized begining readings\n");
    pc.printf("================================\n");
}

void sensor_update() {
    //IMU Update gets pitch and roll
    IMUUpdate(mpu6050);
    
    //Finds depth
    //pressure_sensor_1.Barometer_MS5837();
    pressure_sensor_2.Barometer_MS5837();
    //pressure1 = pressure_sensor_1.MS5837_Pressure();
    pressure2 = pressure_sensor_2.MS5837_Pressure();
    depth = pressure_sensor_2.depth();

        /*//Do some error checking
        if ((pressure1 > 900 && pressure1 < 3000) && (pressure2 > 900 && pressure2 < 3000)) {
            //depth1 = pressure_sensor_1.depth();
            depth2 = pressure_sensor_2.depth();
            
            depth = (depth1 + depth2) / 2;
            error_cnt = 0;
        } else if (pressure2 > 900 && pressure2 < 3000) {
            depth = pressure_sensor_2.depth();
            
            error_cnt = 0;
        } else if (pressure1 > 900 && pressure1 < 3000) {
            //depth = pressure_sensor_1.depth();
            error_cnt = 0;
        } else {
            error_cnt++;
            if (error_cnt > 50) {
                //do something
                pc.printf("Pressure sensor error");   
            }
        }*/
        
    //gets heading
    compass.getXYZ(mag);
    
    float xh, yh;
    xh = mag[0]*cos(pitch*PI/180) + mag[1]*sin(roll*PI/180)*sin(pitch*PI/180) - mag[2]*cos(roll*PI/180)*sin(pitch*PI/180);
    yh = mag[1]*cos(roll*PI/180) + mag[2]*sin(roll*PI/180);
    heading = atan2(yh, xh) * 180/PI;
}

void sensor_msg() {
    //yaw,pitch,roll,raw heading, corrected heading, depth
    pc.printf("%f,%f,%f,%f,%f,%f\r\n", yaw, pitch, roll, compass.getHeadingXYDeg(), heading, depth);
}

void print_data() {
    pc.printf("================================\n");
    pc.printf("Yaw, pitch, roll: %f, %f, %f\n", yaw, pitch, roll);
    pc.printf("Depth 1: %f\n", depth1);
    pc.printf("Depth 2: %f\n", depth2);
    pc.printf("Depth: %f\n", depth);
    pc.printf("Heading w.o. tilt correction: %f\n", compass.getHeadingXYDeg());
    pc.printf("Heading with tilt correction: %f\n", heading);

}
