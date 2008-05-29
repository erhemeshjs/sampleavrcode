/*
 * Kleine Library zum Betreiben des UARTS auf Atmel Microcontrollern
 */

#include <stdio.h>
#include <avr/io.h>
#include "uart.h"

// Definition der Baud-Rate
#define BAUD_RATE 9600

// Define a stream for the printf function, using the UART
FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_RW);

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

    // Umlenken Stdout auf UART
    stdout = &uart_str;
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
 * Routine zum Schreiben der Daten auf std-out
 *
 * @param data das zu schreibende Zeichen
 * @param stream der Stream zum schreiben
 */
void uart_putchar(char data, FILE *stream)
{
    // Pruefung auf new-Line
    if (data == '\n')
    {
      uart_putchar('\r', stream);
    }
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

