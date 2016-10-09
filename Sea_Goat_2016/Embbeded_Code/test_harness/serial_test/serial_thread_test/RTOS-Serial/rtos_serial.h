/*
 * Copyright (c) 2013 Tom Soulanille
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef RTOS_SERIAL_H
#define RTOS_SERIAL_H

#include "mbed.h"
#include "rtos.h"

#define MBED_RTOS_SERIAL_VERSION_MAJOR    0
#define MBED_RTOS_SERIAL_VERSION_MINOR    1
#define MBED_RTOS_SERIAL_VERSION_EDIT     6

#define RTOS_SERIAL_TX_THREAD 1
#define RTOS_SERIAL_TX_THREAD_STACK_SIZE 1024    /* FIXME: figure out good value */

/*
from Serial.h:
class Serial : public Stream {

public:
    Serial(PinName tx, PinName rx, const char *name=NULL);
    ...
protected:
    ...
    serial_t        _serial;

from serial_api.h:
typedef struct serial_s serial_t;

from objects.h:
struct serial_s {
    LPC_UART_TypeDef *uart;
    int index;
};

from LPC17xx.h:
typedef struct
{
  union {
  __I  uint8_t  RBR;
  __O  uint8_t  THR;
  __IO uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  __IO uint8_t  DLM;
  __IO uint32_t IER;
  };
  union {
  __I  uint32_t IIR;
  __O  uint8_t  FCR;
  };
  __IO uint8_t  LCR;
       uint8_t  RESERVED1[7];
  __I  uint8_t  LSR;
       uint8_t  RESERVED2[7];
  __IO uint8_t  SCR;
       uint8_t  RESERVED3[3];
  __IO uint32_t ACR;
  __IO uint8_t  ICR;
       uint8_t  RESERVED4[3];
  __IO uint8_t  FDR;
       uint8_t  RESERVED5[7];
  __IO uint8_t  TER;
       uint8_t  RESERVED6[39];
  __IO uint32_t FIFOLVL;
} LPC_UART_TypeDef;

*/

/** An RTOS-friendly serial port
 *
 * Example:
 * @code
 * // Bridge the USB serial interface to a uart
 * #include "mbed.h"
 * #include "rtos.h"
 * #include "rtos_serial.h"
 * 
 * DigitalOut myled(LED1);
 * 
 * void p_to_p(const void* arg) {
 *     RTOS_Serial** ports = (RTOS_Serial**) arg;
 *     while (true) ports[1]->putc(ports[0]->getc());
 * }
 * 
 * int main() {
 *     RTOS_Serial host(USBTX, USBRX);
 *     RTOS_Serial uart(p13, p14);
 *     RTOS_Serial *host_uart_ports[] = {&host, &uart};
 *     Thread host_to_port_thread(p_to_p, (void*) host_uart_ports);
 *     RTOS_Serial *uart_host_ports[] = {&uart, &host};
 *     Thread port_to_host_thread(p_to_p, (void*) uart_host_ports);
 * 
 *     while (true) {
 *         myled = !myled;
 *         Thread::wait(400);
 *     }
 * }
 * @endcode
 */
class RTOS_Serial : public RawSerial {
  public:

    /** Create an RTOS_Serial connected to the specified UART pins.
     *
     * @param tx PinName of the UART output (transmission) pin
     * @param rx PinName of the UART input (reception) pin
     * @param name (optional) A string to identify the object
     */
    RTOS_Serial(PinName tx, PinName rx, const char *name=NULL);
    
    /** Send a character.
     * If the output queue is full it yields until it can enqueue
     *
     * @param c character to queue for transmission
     * @returns c, or EOF on failure (which should never happen)
     */
    int putc(int c);
    
    /** Get a character.
     * Yields to other threads until a character is available
     *
     * @param timeout (optional) milliseconds to wait for a character (default forever)
     * @returns the next character, or EOF if none available within timeout
     */
    int getc(int timeout = osWaitForever);
    
    /** Put a null-terminated string of characters.
     *
     * @param s the string
     * @returns the number of characters enqueued for transmission, or EOF on error
     */
    int puts(const char *s);
//    int readable();
//    int writeable();
    int get_index();
    /** Obtain the baud rate of the UART.
     *
     * @returns the baud rate of the UART (tx and rx are the same)
     */
    int get_baud();
    
    Queue<int, 16> rx_q;
    const char *name;
 
  protected:
    DigitalOut *ledp;
    int uart_number;
    Queue<int, 16> tx_q;
    int parent_putc(int);
    
    static void threadStarter(void const *p);
    void tx_emitter();
    
    Thread _tx_thread;
    void rx_isr();
    void tx_isr();
};

#endif
