/*
 * Beispielprogramm 04-interrupt.c
 *
 * Kleines Beispielprogramm das einen Taster an PD3 über den getriggerten Interrupt 
 * auswertet und eine LED an PD5 schaltet.
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
#include "../define.h"

int main(void) {
  // Enablen der Interrupts an INT1 ( PD3)
  GIMSK = (1 << INT1);
  // Config INT1 steigende Flanke
  MCUCR = ( (1 << ISC11) | (1 << ISC10) );
  // Interrupts ein
  sei();
  // Port D5 auf Ausgang, LED
  DDR_LED |= (1 << P_LED);

  // Sinnlosschleife
  while(1) { }

  return 0;
}

// Einsprung Interrupt Service-Routine
ISR(INT1_vect) {
  // Toggle Bit an PD5 ( LED )
  PORT_LED ^= ( 1 << P_LED );
}

