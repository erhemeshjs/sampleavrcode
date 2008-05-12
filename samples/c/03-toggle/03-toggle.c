/*
 * Beispielprogramm 03-toggle.c
 *
 * Kleines Beispielprogramm das einen Taster an PD3 abfragt und eine LED an PD5 
 * umschaltet (ein,aus).
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
  // Hilfsvariable
  char toggled = 0;
  // Datenrichtung komplett auf Eingang
  DDR_TASTER &= ~(1 << P_TASTER);
  // PORTD.5 als Ausgang (LED)
  DDR_LED |= (1 << P_LED);

  // Verarbeitungsschleife
  while(1) {
    // Wenn Taster gedr�ckt
    if ( bit_is_set(PIN_TASTER, P_TASTER) ) {
      // Und nicht schon erkannt
      if (toggled == 0) {
        // Dann merken und Bit umschalten
        toggled = 1;
        PORT_LED ^= (1 << P_LED);
      }
    } else {
      // Erkennung zur�cksetzen
      toggled = 0;
    }
  }
  return 0;
}
