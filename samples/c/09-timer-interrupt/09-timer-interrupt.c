/*
 * Beispielprogramm 09-timer-interrupt.c
 *
 * Beispielprogramm, das den internen Timer im AVR nutzt um eine LED
 * an PD5 blinken zu lassen.
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

int main(void) {
  // Port D als Ausgang
  DDRD = 0xFF;
  PORTD = 0;

  // Initialisieren des Timers
  TCCR0B = (1 << WGM02);  // CTC - Modus
  TCCR0B |= (1 << CS02) | (1 << CS00);  // Prescaler = CPU / 1024
  TIMSK = (1 << TOIE0);  // Interrupt enable

  // Interrupts global aktivieren
  sei();

  // Sinnlosschleife
  while(1) { }

  return 0;
}

ISR(TIMER0_OVF_vect) {
  PORTD++;
}

