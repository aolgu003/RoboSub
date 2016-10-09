#ifndef COMMS_H
#define COMMS_H


#include <string>


// Packet constants

#define PKT_START_H 0xFF
#define PKT_START_L 0x15

#define PKT_TYPE_HELLO  0x00
#define PKT_TYPE_INIT   0x01

#define PKT_SIZE_NULL 0x00

#define PKT_END_H 0xFF
#define PKT_END_L 0x1A


// Packet functions

typedef struct packet {
    unsigned char type;
    unsigned size;
    std::string data;
} packet;


const char* make_packet(int *length, const packet *pkt);
const char* make_hello_packet(int *length);

#endif
