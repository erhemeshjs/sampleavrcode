/* 
 * File: ringbuffer.h
 * Ringbuffer fester Länge
 *
 * zoli@augusta.de
 *
*/

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <inttypes.h>

#ifndef BUFFER_BITS
#define BUFFER_BITS 6   // default buffer size 2⁶= 64 bytes
#endif

// Datenstrucktur für Ringbuffer
struct buffer
{
   unsigned char data[1<<BUFFER_BITS];
   uint8_t head, tail;
};

// bufferindex initialisieren
#define buffer_init(b) b.head=b.tail=0

// ein Byte auf Ringbuffer schreiben
unsigned char buffer_write(struct buffer *bp, unsigned char c);

// string auf Ringbuffer schreiben
void buffer_write_s(struct buffer *bp, unsigned char *s);

// ein Byte von Ringbuffer lesen
unsigned char buffer_read(struct buffer *bp);

// Ringbuffer Fuellstand feststellen
uint8_t buffer_size(struct buffer *bp);

#endif
