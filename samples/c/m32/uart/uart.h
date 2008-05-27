/**
 * Schnittstellenbeschreibung der uart-Library
 */

/*
 * Init des RS-232 (UART) Systemes
 *
 * @param baud Die Baudrate, mit der der UART betrieben werden soll
 */
extern void uart_init(char baud);

/*
 * Senden eines Zeichens ueber die UART Schnittstelle
 *
 * @param data Der Character, der an der Console ausgegeben werden soll
 */
extern void uart_putc(char data);

/*
 * Senden eines Zeichenarrays ueber die UArt Schnittstelle
 *
 * @param *s Der String, der ueber UART ausgegeben werden soll
 */
extern void uart_puts(const char *s );

