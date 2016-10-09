
#include "MPU6050.h"
Serial pc(USBTX, USBRX); // tx, rx

float sum = 0;
uint32_t sumCount = 0;

Timer t;

void IMUinit(MPU6050 &mpu6050)
{
    t.start();

// Read the WHO_AM_I register, this is a good test of communication
    uint8_t whoami = mpu6050.readByte(MPU6050_ADDRESS, WHO_AM_I_MPU6050);  // Read WHO_AM_I register for MPU-6050
    pc.printf("I AM 0x%x\n\r", whoami);
    pc.printf("I SHOULD BE 0x68\n\r");

    if (whoami == 0x68) { // WHO_AM_I should always be 0x68
        pc.printf("MPU6050 is online...");
        wait(1);
        //lcd.clear();
        //lcd.printString("MPU6050 OK", 0, 0);


        mpu6050.MPU6050SelfTest(SelfTest); // Start by performing self test and reporting values
        pc.printf("x-axis self test: acceleration trim within : ");
        pc.printf("%f", SelfTest[0]);
        pc.printf("% of factory value \n\r");
        pc.printf("y-axis self test: acceleration trim within : ");
        pc.printf("%f", SelfTest[1]);
        pc.printf("% of factory value \n\r");
        pc.printf("z-axis self test: acceleration trim within : ");
        pc.printf("%f", SelfTest[2]);
        pc.printf("% of factory value \n\r");
        pc.printf("x-axis self test: gyration trim within : ");
        pc.printf("%f", SelfTest[3]);
        pc.printf("% of factory value \n\r");
        pc.printf("y-axis self test: gyration trim within : ");
        pc.printf("%f", SelfTest[4]);
        pc.printf("% of factory value \n\r");
        pc.printf("z-axis self test: gyration trim within : ");
        pc.printf("%f", SelfTest[5]);
        pc.printf("% of factory value \n\r");
        wait(1);

        if(SelfTest[0] < 1.0f && SelfTest[1] < 1.0f && SelfTest[2] < 1.0f && SelfTest[3] < 1.0f && SelfTest[4] < 1.0f && SelfTest[5] < 1.0f) {
            mpu6050.resetMPU6050(); // Reset registers to default in preparation for device calibration
            mpu6050.calibrateMPU6050(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers
            mpu6050.initMPU6050();
            pc.printf("MPU6050 initialized for active data mode....\n\r"); // Initialize device for active mode read of acclerometer, gyroscope, and temperature
            wait(2);
        } else {
            pc.printf("Device did not the pass self-test!\n\r");
        }
    } else {
        pc.printf("Could not connect to MPU6050: \n\r");
        pc.printf("%#x \n",  whoami);

        while(1) ; // Loop forever if communication doesn't happen
    }
}


void IMUPrintData(MPU6050 &mpu6050)
{
    pc.printf("Beginning IMU read\n");
// If data ready bit set, all data registers have new data
    if(mpu6050.readByte(MPU6050_ADDRESS, INT_STATUS) & 0x01) {  // check if data ready interrupt
        mpu6050.readAccelData(accelCount);  // Read the x/y/z adc values
        mpu6050.getAres();

        // Now we'll calculate the accleration value into actual g's
        ax = (float)accelCount[0]*aRes - accelBias[0];  // get actual g value, this depends on scale being set
        ay = (float)accelCount[1]*aRes - accelBias[1];
        az = (float)accelCount[2]*aRes - accelBias[2];

        mpu6050.readGyroData(gyroCount);  // Read the x/y/z adc values
        mpu6050.getGres();

        // Calculate the gyro value into actual degrees per second
        gx = (float)gyroCount[0]*gRes; // - gyroBias[0];  // get actual gyro value, this depends on scale being set
        gy = (float)gyroCount[1]*gRes; // - gyroBias[1];
        gz = (float)gyroCount[2]*gRes; // - gyroBias[2];

        tempCount = mpu6050.readTempData();  // Read the x/y/z adc values
        temperature = (tempCount) / 340. + 36.53; // Temperature in degrees Centigrade
    }
    
    Now = t.read_us();
    deltat = (float)((Now - lastUpdate)/1000000.0f) ; // set integration time by time elapsed since last filter update
    lastUpdate = Now;

    sum += deltat;
    sumCount++;

    if(lastUpdate - firstUpdate > 10000000.0f) {
        beta = 0.04;  // decrease filter gain after stabilized
        zeta = 0.015; // increasey bias drift gain after stabilized
    }

    // Pass gyro rate as rad/s
    mpu6050.MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f);

    // Serial print and/or display at 0.5 s rate independent of data rates
    delt_t = t.read_ms() - count;
    if (delt_t > 500) { // update LCD once per half-second independent of read rate

        pc.printf("ax = %f", 1000*ax);
        pc.printf(" ay = %f", 1000*ay);
        pc.printf(" az = %f  mg\n\r", 1000*az);

        pc.printf("gx = %f", gx);
        pc.printf(" gy = %f", gy);
        pc.printf(" gz = %f  deg/s\n\r", gz);

        pc.printf(" temperature = %f  C\n\r", temperature);

        pc.printf("q0 = %f\n\r", q[0]);
        pc.printf("q1 = %f\n\r", q[1]);
        pc.printf("q2 = %f\n\r", q[2]);
        pc.printf("q3 = %f\n\r", q[3]);

        // Define output variables from updated quaternion---these are Tait-Bryan angles, commonly used in aircraft orientation.
        // In this coordinate system, the positive z-axis is down toward Earth.
        // Yaw is the angle between Sensor x-axis and Earth magnetic North (or true North if corrected for local declination, looking down on the sensor positive yaw is counterclockwise.
        // Pitch is angle between sensor x-axis and Earth ground plane, toward the Earth is positive, up toward the sky is negative.
        // Roll is angle between sensor y-axis and Earth ground plane, y-axis up is positive roll.
        // These arise from the definition of the homogeneous rotation matrix constructed from quaternions.
        // Tait-Bryan angles as well as Euler angles are non-commutative; that is, the get the correct orientation the rotations must be
        // applied in the correct order which for this configuration is yaw, pitch, and then roll.
        // For more see http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles which has additional links.
        yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);
        pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
        roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
        pitch *= 180.0f / PI;
        yaw   *= 180.0f / PI;
        roll  *= 180.0f / PI;

//    pc.printf("Yaw, Pitch, Roll: \n\r");
//    pc.printf("%f", yaw);
//    pc.printf(", ");
//    pc.printf("%f", pitch);
//    pc.printf(", ");
//    pc.printf("%f\n\r", roll);
//    pc.printf("average rate = "); pc.printf("%f", (sumCount/sum)); pc.printf(" Hz\n\r");

        pc.printf("Yaw, Pitch, Roll: %f %f %f\n\r", yaw, pitch, roll);
        pc.printf("average rate = %f\n\r", (float) sumCount/sum);

        //myled= !myled;
        count = t.read_ms();
        sum = 0;
        sumCount = 0;
    }
}

void IMUUpdate(MPU6050 &mpu6050)
{
    // If data ready bit set, all data registers have new data
    if(mpu6050.readByte(MPU6050_ADDRESS, INT_STATUS) & 0x01) {  // check if data ready interrupt
        mpu6050.readAccelData(accelCount);  // Read the x/y/z adc values
        mpu6050.getAres();

        // Now we'll calculate the accleration value into actual g's
        ax = (float)accelCount[0]*aRes - accelBias[0];  // get actual g value, this depends on scale being set
        ay = (float)accelCount[1]*aRes - accelBias[1];
        az = (float)accelCount[2]*aRes - accelBias[2];

        mpu6050.readGyroData(gyroCount);  // Read the x/y/z adc values
        mpu6050.getGres();

        // Calculate the gyro value into actual degrees per second
        gx = (float)gyroCount[0]*gRes; // - gyroBias[0];  // get actual gyro value, this depends on scale being set
        gy = (float)gyroCount[1]*gRes; // - gyroBias[1];
        gz = (float)gyroCount[2]*gRes; // - gyroBias[2];

        tempCount = mpu6050.readTempData();  // Read the x/y/z adc values
        temperature = (tempCount) / 340. + 36.53; // Temperature in degrees Centigrade
    }

    Now = t.read_us();
    deltat = (float)((Now - lastUpdate)/1000000.0f) ; // set integration time by time elapsed since last filter update
    lastUpdate = Now;

    sum += deltat;
    sumCount++;

    if(lastUpdate - firstUpdate > 10000000.0f) {
        beta = 0.04;  // decrease filter gain after stabilized
        zeta = 0.015; // increasey bias drift gain after stabilized
    }

    // Pass gyro rate as rad/s
    mpu6050.MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f);

    // Serial print and/or display at 0.5 s rate independent of data rates
    delt_t = t.read_ms() - count;

    // Define output variables from updated quaternion---these are Tait-Bryan angles, commonly used in aircraft orientation.
    // In this coordinate system, the positive z-axis is down toward Earth.
    // Yaw is the angle between Sensor x-axis and Earth magnetic North (or true North if corrected for local declination, looking down on the sensor positive yaw is counterclockwise.
    // Pitch is angle between sensor x-axis and Earth ground plane, toward the Earth is positive, up toward the sky is negative.
    // Roll is angle between sensor y-axis and Earth ground plane, y-axis up is positive roll.
    // These arise from the definition of the homogeneous rotation matrix constructed from quaternions.
    // Tait-Bryan angles as well as Euler angles are non-commutative; that is, the get the correct orientation the rotations must be
    // applied in the correct order which for this configuration is yaw, pitch, and then roll.
    // For more see http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles which has additional links.
    yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);
    pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
    roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
    pitch *= 180.0f / PI;
    yaw   *= 180.0f / PI;
    roll  *= 180.0f / PI;

    count = t.read_ms();
    sum = 0;
    sumCount = 0;

}
