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

/* TODO:
 *  - size the tx thread stack
 *  - make an rx buffer thread?
 *    - implement readable()
 *  - implement writeable() somehow
 */
#include "rtos_serial.h"

#define RTOS_SERIAL_START_THREAD 0x80
#define RTOS_SERIAL_USE_LED_INDICATOR   0

RTOS_Serial::RTOS_Serial(PinName tx, PinName rx, const char *name)
 : RawSerial(tx, rx),
   name(name),
   _tx_thread(&RTOS_Serial::threadStarter, (void *) this,
                    osPriorityNormal, RTOS_SERIAL_TX_THREAD_STACK_SIZE)
{
    uart_number = get_index();
#if RTOS_SERIAL_USE_LED_INDICATOR
    static const PinName leds[] = {LED1,LED2,LED3,LED4};
    ledp = new DigitalOut(leds[uart_number]);
    for (int i=0; i<1; i++) { *ledp=1; wait(0.1); *ledp=0; wait(0.1); }; wait(0.5);
#endif
    _tx_thread.signal_set(RTOS_SERIAL_START_THREAD);
}

#if 0
RTOS_Serial::~RTOS_Serial() {
    std::printf("[destroying RTOS_Serial 0x%x]", this); std::fflush(stdout);
    bool b;
    osDelay(200);   //DEBUG
#if 0
    std::printf("[remove rx handler 0x%x", rx_isr_pFP); std::fflush(stdout);
// returns false as expected:    b = remove_handler(NULL, RxIrq);
    b = remove_handler(rx_isr_pFP, RxIrq);
    std::printf("returned %d]", b); std::fflush(stdout);
    std::printf("[remove tx handler 0x%x", tx_isr_pFP); std::fflush(stdout);
    b = remove_handler(tx_isr_pFP, TxIrq);
    std::printf("returned %d]", b); std::fflush(stdout);
#endif
#ifdef RTOS_SERIAL_TX_THREAD
    _tx_thread.terminate();
    std::printf("[tx_emitter_thread 0x%x terminated]", &_tx_thread); std::fflush(stdout);
    delete tx_emitter_threadp;
    std::printf("[tx_emitter_threadp deleted]"); std::fflush(stdout);
#endif
}
#endif

int  RTOS_Serial::get_index() { return _serial.index; }

int  RTOS_Serial::get_baud() { return _baud; }

//int RTOS_Serial::writeable() { return true; } //FIXME: implement

int RTOS_Serial::putc(int c) {
    //return Serial::putc(c); //DEBUG
    //if (tx_q.put((int *)c, osWaitForever) == osOK) return c; else return EOF;
    int status;
    if ( (status = tx_q.put((int *)c, osWaitForever)) == osOK) return c; else {
        std::printf("\r\nRTOS_Serial::tx_q.put() returned %d\r\n", status);
        return EOF;
    }
}   

int RTOS_Serial::puts(const char *s) {
    int rv = 0;
    while (*s) {
        if (putc(*s++) == EOF) {
            rv = EOF;
            break;
        } else {
            rv++;
        }
    }
    return rv;
}

int RTOS_Serial::parent_putc(int c) {
    return RawSerial::putc(c);
}

//int RTOS_Serial::readable() { return true; } //FIXME: implement

int RTOS_Serial::getc(int timeout) {
    int rv;
    //return Serial::getc();  //FIXME: stand-in, which fails if we use our RX ISR
    osEvent evt = rx_q.get(timeout);
    if (evt.status == osEventMessage) {
        rv = (int) evt.value.v;
    } else if (evt.status == osOK) {
        rv = EOF;
    } else {    //FIXME: find appropriate error reporting if any
        std::printf("\r\nRTOS_Serial::getc() evt.status %d\n", evt.status);
        rv = EOF;
    }
    return rv;
}

void RTOS_Serial::rx_isr(){
    rx_q.put((int *) RawSerial::getc());  // returns immediately even if queue was full
}

void RTOS_Serial::tx_isr(){
    _tx_thread.signal_set(0x1);
}


void RTOS_Serial::threadStarter(void const *p) {
    RTOS_Serial *instance = (RTOS_Serial*)p;
    instance->tx_emitter();
}

void RTOS_Serial::tx_emitter(){
    osEvent evt;
    //osStatus status;
    _tx_thread.signal_wait(RTOS_SERIAL_START_THREAD);
#if RTOS_SERIAL_USE_LED_INDICATOR
    for (int i=0; i<2; i++) { *ledp=1; wait(0.1); *ledp=0; wait(0.1); }; wait(0.5);
#endif
    attach(this, &RTOS_Serial::rx_isr, RxIrq);
#if RTOS_SERIAL_USE_LED_INDICATOR
    for (int i=0; i<3; i++) { *ledp=1; wait(0.1); *ledp=0; wait(0.1); }; wait(0.5);
#endif
    attach(this, &RTOS_Serial::tx_isr, TxIrq);    
#if RTOS_SERIAL_USE_LED_INDICATOR
    for (int i=0; i<4; i++) { *ledp=1; wait(0.1); *ledp=0; wait(0.1); }; wait(0.5);
#endif
    _tx_thread.signal_set(0x01);   // "prime the pump" of the tx-ready signals
    
    while(true){
        evt = tx_q.get();
        if (evt.status == osEventMessage) {
            // There is no TX interrupt until the first byte is sent out the port,
            // so we use a timeout on the signal from the interrupt service routine
            // and just proceed to transmit the character. This should happen only
            // once at most, to "prime the pump", but the timeout provides some
            // safety in case something goes wrong.
            // A first signal is sent by the RTOS_Serial constructor when the thread
            // is created, so normally this will not come into effect.
            // DEBUG: timeout omitted to search for instabilities
            Thread::signal_wait(0x1/*, 10*/);   //FIXME: base the timeout on the baud rate
#if RTOS_SERIAL_USE_LED_INDICATOR
            *ledp = 1;
#endif
            parent_putc(evt.value.v);
#if RTOS_SERIAL_USE_LED_INDICATOR
            *ledp = 0;
#endif
        } else {
            std::printf("\r\nRTOS_Serial::tx_emitter() evt.status %d\n", evt.status);
        }
#if RTOS_SERIAL_USE_LED_INDICATOR
        *ledp = 0;
#endif
    }
}
