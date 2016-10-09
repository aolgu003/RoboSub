#include "mbed.h"
#include "rtos.h"

#define gyro_read_address_H (0x1D)
#define gyro_read_address_L (0x1E)


Serial pc(USBTX, USBRX); // tx, rx
DigitalOut led1(LED1);

void print_char(char c)
{
    printf("Hello world\n", c);
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
    float c = 0;
    while(1) {
        Thread::wait(1000);
		float c = c + .1;
		printf("vel,%5.1f,\n", c);
        /*if (pc.readable()) {
            c = read_char();
            print_char(c);
            
        } */ 
    }    
}

int main()
{
    printf("\n\n*** RTOS basic example ***\n");
    
    Thread thread2(echo_thread, NULL, osPriorityNormal, DEFAULT_STACK_SIZE);
    
    while (true) {
        //led1 = !led1;
        Thread::wait(500);
    }
}
