 // Bridge the USB serial interface to a uart
#include "mbed.h"
#include "rtos.h"
#include "rtos_serial.h"
#include "string"
 
DigitalOut myled(LED1);
 
char* message[20];
 
typedef struct {
    float yaw;
    float pitch;
    float roll;

    float surge_vel;
    float depth;
    float pixel_x;
    float pixel_y;
 } vehicle;
 
 void serial_handler(const void* arg) {
    int i = 0;
    RTOS_Serial** ports = (RTOS_Serial**) arg;
    while (true) {
        message[i] = ports->getc();
        i++;
        if (ports->getc() == '\n') {
            
        }
    }
 }
 
 int main() {
    RTOS_Serial *host(USBTX, USBRX);
	//RTOS_Serial host_port
    Thread serial_handler(serial_handler, (void*) host);
        
    while (true) {
         myled = !myled;
         Thread::wait(400);
     }
 }
