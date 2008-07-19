/* 
 * File: ringbuffer.c
 * Ringbuffer fester Länge
 *
 * zoli@augusta.de
 * last modified 2007-04-31
 *
*/


#include "ringbuffer.h"
#include <avr/io.h>

void uart_putc(unsigned char);

// ein Byte auf Ringbuffer schreiben
unsigned char buffer_write(struct buffer *bp, unsigned char c){
  // Buffer ist voll wenn sich die Katze in den Schwanz beisst!
  if(((bp->head+1)==bp->tail) || 
    (bp->tail==0 && ((bp->head+1) & (1<<BUFFER_BITS)))){
    return 0;                // Error - buffer full
  }
  if((++(bp->head)) & (1<<BUFFER_BITS)){  // wenn Kopf am Bufferende
    bp->head=0x00;                        // dann wieder auf den Anfang setzen
  }
  bp->data[bp->head] = c;      // Zeichen in Buffer schreiben
  if(c=='\n' || c=='\r'){      // flush buffer wenn neue Zeile angefangen wird
    UCSRB |= 1<<UDRIE;         // enable UartDataRegisterEmptyInterupt
  }
  return c;
}


// String auf Ringbuffer schreiben
void buffer_write_s(struct buffer *bp, unsigned char *s){
  while (*s) {             // so lange s* != NULL
    buffer_write(bp,*s);   // Zeichen Ausgeben
    s++;                   // nächstes Zeichen
  }
}


// ein Byte von Ringbuffer lesen
unsigned char buffer_read(struct buffer *bp){
  if(bp->head==bp->tail)   // wenn Buffer ist leer
    return 0;              // nichts (0) zurückgeben
  if((++(bp->tail)) & (1<<BUFFER_BITS)) // wenn Schwanz am Bufferende
    bp->tail=0;                        // dann wieder auf den Anfang setzeb
  return bp->data[bp->tail];           // Zeichen aus Buffer zurueckgeben
}


// Ringbuffer Fuellstand
uint8_t buffer_size(struct buffer *bp){
  return bp->head >= bp->tail ? bp->head - bp->tail :
    (1<<BUFFER_BITS) + bp->head - bp->tail;
}

