/*
 * Beispielprogramm 02-taster.c
 *
 * Kleines Beispielprogramm das einen Taster auf PD3 abfragt und eine LED an PD5 schaltet.
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

int main(void) {
  // Port D komplett auf Eingang
  DDRD = 0x00;
  // Port D Ping 5 als Ausgang
  DDRD = (1 << PD5);

  // Verarbeitungsschleife
  while(1) {
    // Wenn Taster gedrückt
    if( PIND & (1 << PIND3) ) {
      // LED Einschalten
      PORTD |= (1 << PD5);
    } else {
      // Ansonsten LED aus
      PORTD &= ~(1 << PD5);
    }
  } 

  return 0;
}
