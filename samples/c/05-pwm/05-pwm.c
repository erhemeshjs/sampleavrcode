/*
 * Beispielprogramm 05-pwm.c
 *
 * Kleines Beispielprogramm das eine LED an PD5 dimmt
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
#include <util/delay.h>
#include "../define.h"

int main(void) {

  DDR_LED |= (1 << P_LED);  // PIN D5 auf Ausgang

  TCCR0A = (1 << WGM00) | (1 << WGM01);  // Fast PWM Mode
  TCCR0A |= (1 << COM0B1) | (1 << COM0B0);  // Set OC0B on Compare Match,
  TCCR0B = (1 << CS00);  // Prescaler = CPU-Clock
  OCR0B = 0;  // Setzen Initial-Wert in Register

  char dir_up = 0;  // Merker für die Zählrichtung

  // Verarbeitungsschleife
  while(1) {
    // Steuerung, ob rauf- oder runtergezählt wird.
    if (dir_up) {
      OCR0B++;
    } else {
      OCR0B--;
    }
    // Wenn Grenzwert erreicht, umschalten der Richtung
    if (OCR0B < 1) {
      dir_up = 1;
    }
    if (OCR0B > 254) {
      dir_up = 0;
    }
    // Kleine Wartezeit
    _delay_ms(10);
  } 

  return 0;
}
