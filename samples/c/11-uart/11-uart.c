/*
 * Beispielprogramm 11-uart.c
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
#include <stdlib.h>
#include <util/delay.h>

#include "../define.h"
#include "../uart/uart.h"

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

/* 9600 baud */
#define UART_BAUD_RATE      9600

int main(void) {

  // Sekunden seit dem letzten Start des Programmes
  uint32_t sekunden = 0;

  // Platz f�r Umwandlung in String
  unsigned char timestring[11];

  // PORTD.5 als Ausgang (LED)
  DDR_LED |= (1 << P_LED);

  // Initialisieren des UArts
  uart_init( UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );  

  // Enablen der Interrupts
  sei();

  // Test-String
  uart_puts("Test UART\r\n");

  // Verarbeitungsschleife
  while(1) {
    // Sekunden in ASCII umwandel und ausgeben
    ltoa(sekunden++,timestring,10);
    uart_puts("Uptime in Sekunden: ");
    uart_puts(timestring);
    uart_puts("\r\n");

    // 1 Sekunde warte
    _delay_ms(1000);
    
    // LED toggle
    PORT_LED ^= 1 << P_LED;
  }
  // wird nie erreicht
  return 0;
}
