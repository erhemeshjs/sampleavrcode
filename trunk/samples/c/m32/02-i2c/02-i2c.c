/*
 * Beispielprogramm 08-i2c.c
 *
 * Beispielprogramm, das den I2C Bus ansteuert. Mit diesem wird ein 
 * Wert in den am Bus angeschlossenem EEProm gespeichert und 
 * ausgelesen.
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

int main(void)
{
  DDRD = (1 << PD5);

  // Verarbeitungsschleife
  while(1)
  {
  }
  return 0;
}
