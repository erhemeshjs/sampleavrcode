/*
 * Beispielprogramm 10-led.c
 *
 * Beispielprogramm, das an PORTD angeschlossene LED's im
 * Binärtakt zum blinken bringt.
 *
 * (c) Robert Einsle <robert@einsle.de>
 * (c) Michael Hartmann <michael@speicherleck.de>
 * V 1.0, 09.05.2008
 *
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

#include "../uart/uart.h"

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

/* 9600 baud */
#define UART_BAUD_RATE      9600

int main(void) {

  // Initialisieren des UArts
  uart_init( UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );  

  // Enablen der Interrupts
  sei();

  // Test-String
  uart_puts("Test UART\r\n");

  // Verarbeitungsschleife
  while(1) {
    uart_puts("Test\r\n");
    _delay_ms(1000);
  }

  return 0;
}
