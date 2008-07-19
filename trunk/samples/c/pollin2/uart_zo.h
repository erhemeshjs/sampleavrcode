/* 
 * File: uart_zo.h
 * Serielle Schnittstele über Hardware-UART
 *
 * zoli@augusta.de
 * last modified 2008-03-28
 *
*/

#define F_CPU 8000000UL         // CPU-Frequenz in Hz
#define UART_BAUD_RATE 9600UL   // Baudrate

// Bufferpointer auf 
struct buffer *get_bp, *put_bp;

// USART_Init für ATmegaXX
//void uart_init(void);


// Zeichen von Schnittstelle lesen
// gib 0 zurück wenn kein Zeichen vorhanden
//unsigned char uart_getc(void);

// Zeichen auf Schnittstelle ausgeben
//void uart_putc(char c);


// String auf UART ausgeben
//void uart_puts(char *s);
