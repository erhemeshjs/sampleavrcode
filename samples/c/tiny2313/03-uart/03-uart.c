/*
 * Beispielprogramm 01-uart.c
 *
 * Beispielprogramm, das im Sekundentackt die Zeit in Sekunden seit
 * dem Start des Programmes am seriellen PORT
 * (UART) mit 9600 Baud (8N1) ausgibt.
 * LED blinkt im Sekundenrythmus
 *
 * (c) Robert Einsle <robert@einsle.de>
 * (c) Wernfred Zolnhofer <zoli@augusta.de>
 * V 1.1, 19.05.2008
 *
 * Software:  AVR-GCC 4.2 
 * Target:    ATtiny2313 auf Pollin Entwicklungsboard

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#define BAUD_RATE 9600

// Definition der Funktionen
void uart_init(void);
void uart_putc(char c);
void uart_puts(const char *s);

/**
 * Hauptverarbeitungsschleife
 */
int main(void) {

    // Init des UARTS
    uart_init();

    // Senden String
    uart_puts("Start\r\n");

    // Verarbeitungsschleife
    while (1)
    {
      uart_puts("Hallo Welt\r\n");
      _delay_ms(1000);
    }

    // wird nie erreicht
    return 0;
}

/*
 * Init des RS-232 (UART) Systemes
 */
void uart_init(void)
{
    // Enable TX und RX 
    UCSRB = (1 << TXEN) | (1 << RXEN);
    // Asyncron, 8n1
    UCSRC = (3 << UCSZ0);
    // Setzen der BAUD-Rate
    UBRRH = (uint8_t) ((F_CPU / (BAUD_RATE * 16L) -1) >> 8);
    UBRRL = (uint8_t) (F_CPU / (BAUD_RATE * 16L) -1);
}

/*
 * Senden eines Zeichens ueber die UART Schnittstelle
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
 */
void uart_puts(const char *s )
{
    while (*s) 
      uart_putc(*s++);

}
