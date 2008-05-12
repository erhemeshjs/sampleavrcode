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

int main(void) {

  // PIN D5 auf Ausgang
  DDRD |= (1 << PD5);

  TCCR0A = (1 << WGM00) | (1 << WGM01);  // Fast PWM Mode
  TCCR0A |= (1 << COM0B1) | (1 << COM0B0);  // Set OC0B on Compare Match,
                                            // clear OC0B at TOP
  TCCR0B = (1 << CS00);  // Prescaler = CPU-Clock

  OCR0B = 0;	

//  TCCR0A = (1 << WGM00);  // Phase correct PWM Mode
//  TCCR0B = (1 << WGM02);  // Phase correct PWM Mode
//  TCCR0B |= (1 << CS01);
//  TCCR0A |= (1 << COM0B0) | (1 << COM0B1);  // 

//  TCCR0A = (1<<COM0A1)|(1<<COM0B1)|(1<<WGM10); 
//  TCCR0B = (1<<CS11); 
  int i;

  // Verarbeitungsschleife
  while(1) {
    for (i = 0; i < 255; i=i+1)
      {
        OCR0B = i;
        _delay_ms(50);
      }
  } 

  return 0;
}
