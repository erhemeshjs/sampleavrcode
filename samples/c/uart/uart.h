/**
 * Schnittstellenbeschreibung der uart-Library
 */

#include <stdio.h>

/*
 * Init des RS-232 (UART) Systemes
 *
 * @param baud Die Baudrate, mit der der UART betrieben werden soll
 */
extern void uart_init(void);

/*
 * Senden eines Zeichens ueber die UART Schnittstelle
 *
 * @param data Der Character, der an der Console ausgegeben werden soll
 */
extern void uart_putc(char data);

/*
 * Routine zum Schreiben der Daten auf std-out
 *
 * @param data das zu schreibende Zeichen
 * @param stream der Stream zum schreiben
 */
void uart_putchar(char data, FILE *stream);

/*
 * Senden eines Zeichenarrays ueber die UArt Schnittstelle
 *
 * @param *s Der String, der ueber UART ausgegeben werden soll
 */
extern void uart_puts(const char *s );

