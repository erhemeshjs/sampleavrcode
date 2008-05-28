/*
 * Kleine Library zum Betreiben des UARTS auf Atmel Microcontrollern
 */

#include <avr/io.h>

// Definition der Baud-Rate
#define BAUD_RATE 9600

/*
 * Init des RS-232 (UART) Systemes
 *
 * @param baud Die Baudrate, mit der der UART betrieben werden soll
 */
void uart_init(void)
{
    // Enable TX und RX 
    UCSRB |= (1 << TXEN) | (1 << RXEN);
    // Asyncron, 8n1
    UCSRC |= (3 << UCSZ0);
#if  defined(__AVR_ATmega32__)
    UCSRC |= (1 << URSEL);
#endif
    // Setzen der BAUD-Rate
    UBRRH = (uint8_t) ((F_CPU / (BAUD_RATE * 16L) -1) >> 8);
    UBRRL = (uint8_t) (F_CPU / (BAUD_RATE * 16L) -1);
}

/*
 * Senden eines Zeichens ueber die UART Schnittstelle
 *
 * @param data Der Character, der an der Console ausgegeben werden soll
 */
void uart_putc(char data)
{
    // Warten bis Puffer leer
    while ( !( UCSRA & (1<<UDRE)) )
      ;
    // Stellen der Daten in den Sendepuffer
    UDR = data;
}

/*
 * Senden eines Zeichenarrays ueber die UArt Schnittstelle
 *
 * @param *s Der String, der ueber UART ausgegeben werden soll
 */
void uart_puts(const char *s )
{
    while (*s) 
      uart_putc(*s++);

}

