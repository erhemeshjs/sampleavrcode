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
#include "../define.h"

int main(void) {
  // Port D Pin 3 als Eingang
  DDR_TASTER &= ~(1 << P_TASTER);
  // Port D Pin 5 als Ausgang
  DDR_LED |= (1 << P_LED);

  // Verarbeitungsschleife
  while(1) {
    // Wenn Taster gedrückt
    if( bit_is_set (PIN_TASTER, P_TASTER)  ) {
      // LED Einschalten
      PORT_LED |= (1 << P_LED);
    } else {
      // Ansonsten LED aus
      PORT_LED &= ~(1 << P_LED);
    }
  } 

  return 0;
}
