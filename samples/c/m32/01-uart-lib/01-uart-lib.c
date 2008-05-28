/*
 * Beispielprogramm 01-uart-lib.c
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

/**
 * Hauptverarbeitungsschleife
 */
int main(void) {

    // Init PORTD.5 als Ausgang
    DDRD |= (1 << PD5);

    // Init des UARTS
    uart_init(9600);

    // Senden String
    uart_puts("Start\r\n");

    // Verarbeitungsschleife
    while (1)
    {
      uart_puts("Hallo Welt\r\n");
      _delay_ms(1000);

      // PORTD.5 umschalten
      PORTD ^= (1 << PD5);
    }

    // wird nie erreicht
    return 0;
}

