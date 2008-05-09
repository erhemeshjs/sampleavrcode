/*
 * Beispielprogramm 09-timer-interrupt.c
 * (c) Robert Einsle <robert@einsle.de>
 * (c) Michael Hartmann <michael@speicherleck.de>
 * V 0.1, 01-05-2008
 * ATtiny 2313
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
  TCCR0 |= (1 << CS00) | (1 << CS02);
  TIMSK |= (1 << TOV0);

  // Interrupts global aktivieren
  sei();

  // Sinnlosschleife
  while(1) { }

  return 0;
}

ISR(TIMER1_CAPT_vect) {
  PORTD++;
}
