#include "mbed.h"
#include "rtos.h"
#include "MPU6050.h"

#define gyro_read_address_H (0x1D)
#define gyro_read_address_L (0x1E)


Serial pc(USBTX, USBRX); // tx, rx
MPU6050 imu;
DigitalOut led1(LED1);
//imu(I, PinName scl);

void print_char(char c)
{
    printf("Here is the char: %c\n", c);
    fflush(stdout);
	led1 = !led1;
}

char read_char() {
    char c;
    c = pc.getc();

	return c;
}



void echo_thread(void const *argument)
{
	char c = 0;
	while(1) {
        Thread::wait(1000);
		if (pc.readable()) {
			c = read_char();
			print_char(c);
			
		}  
	}    
}

void read_imu(void const *argumennt) {
    while (true) {
        Thread::wait(1000);
        uint8_t whoami = imu.readByte(MPU6050_ADDRESS, WHO_AM_I_MPU6050);  // Read WHO_AM_I register for MPU-6050
        pc.printf("I AM 0x%x\n\r", whoami); pc.printf("I SHOULD BE 0x68\n\r");
    }
}

int main()
{
    printf("\n\n*** RTOS basic example ***\n");
    
    //Thread thread1(read_imu, NULL, osPriorityNormal, DEFAULT_STACK_SIZE);
    Thread thread2(echo_thread, NULL, osPriorityNormal, DEFAULT_STACK_SIZE);
    
    //int gyro_val = 0;
    //char data_read[2];
    
    while (true) {
        //led1 = !led1;
        //imu.read(gyro_read_address_H, data_read, 0); // no stop
        //imu.read(gyro_read_address_L, data_read, 0); // 
        //gyro_val = gyro_val | (int) data_read[0];
        //gyro_val = gyro_val | ((int) data_read[0] << 8);
        //printf("Gyro Value: %d\n", data_read[0]);
        Thread::wait(500);
    }
}
