/*********************************************************************************
* This code initializes the MS5803 and MS5837 pressure sensors on pins used
* during testing (in March 2016 version of fish, the Open ROV IMU/Pressure Sensor
* is connected to p28/p27, whereas this code uses both p28/p27 and p9/p10). It
* constantly prints out the pressure and temperature readings of the two sensors.
* It also establishes a QEI object on pins 25 and 24 from the encoder and
* constantly prints the revolutions.
*********************************************************************************/

#include "mbed.h"
using namespace std;

Serial pc(USBTX, USBRX);

// Motor Driver
//AnalogIn pot(p15);
//PwmOut enable(p26);

// Hall Sensor
//InterruptIn hallVoltage(p8);
DigitalOut led2(LED2);

// QEI
//QEI wheel(p25, p24, NC, 12); // 12=counts per revolution of motor shaft for the encoder

void flip() {
    led2 = !led2;
}

int main() {
    // set serial transfer rate
    pc.baud(9600);

    // Initialize big pressure sensor
    //MS5803 big_sensor = MS5803(p28, p27, ms5803_addrCH);
    //big_sensor.MS5803Init();
    //float pressure_big;
    //float temp_big;

    // Motor & QEI initialization
    /*wheel.reset();
    enable.period(.000001);
    int count = 0;
    int previousHallVoltage = 0;*/

    while(1) {
        //hallVoltage.rise(&flip);
        //hallVoltage.fall(&flip);
        
        // Update big pressure sensor
        /*big_sensor.Barometer_MS5803();
        pressure_big = big_sensor.MS5803_Pressure();
        temp_big = big_sensor.MS5803_Temperature();
        pc.printf("Big Sensor Pressure: %f\n", pressure_big);
        pc.printf("Big Sensor Temperature: %f\n", temp_big);*/
        
        // Update small pressure sensor   
//        // Simply feedback loop for speed, changing values every 5 revolutions as detected by hall sensor
//        if (count < 5) {
//            enable = pot; //PWM enable output is proportional to analog pot input
//        } else if (count < 10) {
//            enable = pot/2;
//        } else {
//            enable = pot;
//            count = 0;
//        }
//        if (previousHallVoltage==1 && hallVoltage==0) {
//            count += 1;
//            pc.printf("\n\n----END OF REVOLUTION----\nNumber of pulses: %i\n", wheel.getPulses());
//            wheel.reset();
//        }
//        if (hallVoltage) {
//            led2 = 1;
//            previousHallVoltage = 1;
//        } else {
//            led2 = 0;
//            previousHallVoltage = 0;
//        }

        //pc.printf("Pulses is: %i\n", wheel.getPulses());
    }
}
