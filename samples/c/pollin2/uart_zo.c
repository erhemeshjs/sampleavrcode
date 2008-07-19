/* 
 * File: uart_zo.c
 * Serielle Schnittstele über Hardware-UART
 *
 * zoli@augusta.de
 * last modified 2008-03-28
 *
*/


#include "uart_zo.h"
#include <avr/io.h>
#include <avr/interrupt.h>      // Interrupts

// USART_Init für ATmegaXX
void uart_init(void){
   uint16_t ubrr = (uint16_t) ((uint32_t) F_CPU/(16*UART_BAUD_RATE) - 1);
   UBRRH = (uint8_t) (ubrr>>8);                      //  0 für 9600 Baud bei 8 Mhz
   UBRRL = (uint8_t) (ubrr);                         // 51 für 9600 Baud bei 8 Mhz
   UCSRB |= (1<<TXEN) | (1<<RXEN);                   // UART TX u. RX einschalten
   UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);    // Asynchron 8N1
   // Flush Receive-Buffer (entfernen evtl. vorhandener ungültiger Werte) 
   do{
     UDR;
   } while (UCSRA & (1 << RXC));
}


// Zeichen von Schnittstelle lesen
// gib 0 zurück wenn kein Zeichen vorhanden
unsigned char uart_getc(void){
   if (UCSRA & (1 << RXC)){
     return UDR;
   }
   else return 0;
}


// Zeichen auf Schnittstelle ausgeben
void uart_putc(unsigned char c){
   if(c==0x00) c='\n';			// ACHTUNG nicht für Binärübertragung
   if (c=='\n') uart_putc('\r');	// ACHTUNG !!! \r MUSS für Binärübertragung abgeschaltet werden !!!
   while(!(UCSRA & (1 << UDRE)))
     ;                                  // warte bis Senderegister bereit ist
   UDR = c;                             // sende Zeichen
}


// String auf UART ausgeben
void uart_puts(unsigned char *s){
  while (*s) {		           	// so lange s* != NULL
    uart_putc(*s);     			// Zeichen Ausgeben
    s++;                   		// nächstes Zeichen
  }
}


// Receive Interuptservice fuer USART-Schnittstelle
// todo: Fehler abfangen
ISR(USART_RXC_vect)
{
   cli();                                // IRQs global sperren
   buffer_write(get_bp, uart_getc());    // hole Zeichen von UART in buffer
   sei();                                // Interrupts global wieder freigeben
}

// Transmit Interuptservice fuer USART-Schnittstelle
ISR(USART_UDRE_vect)
{
  if(buffer_size(put_bp) > 0)             // wenn sich noch Zeichen im buffer befinden
    uart_putc(buffer_read(put_bp));       // diese ausgeben
  if(buffer_size(put_bp) == 0)            // wenn buffer leer ist IRQ sperren
    UCSRB &= ~(1<<UDRIE);                 // disable UartDataRegisterEmptyInterupt
}
