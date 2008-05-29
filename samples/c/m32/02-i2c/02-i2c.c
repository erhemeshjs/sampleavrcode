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
#include <util/twi.h>

void error(void);

int main(void)
{
    DDRD = (1 << PD5);
  
    // Init des TWI-Bus
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  
    // Warten bis TW Start transmitted
    while (!(TWCR & (1 << TWINT)))
      ;
  
    // Ueberpruefung ob START-Condition
	if ((TWSR & 0xF8) != TW_START)
	  error();
	  
	// Setzen der Client-Address
	TWDR = 0xA1; // Client Address
	TWCR = (1 << TWINT) | (1 << TWEN);
	
    // Warten bis TW Start transmitted
    while (!(TWCR & (1 << TWINT)))
      ;
  
    // Ueberpruefung ob START-Condition
	if ((TWSR & 0xF8) != TW_START)
	  error();
	  
	// Schreiben der Daten an den Client
	TWDR = 0xFF;
	TWCR = (1 << TWINT) | (1 << TWEN);
	
    // Warten bis TW Start transmitted
    while (!(TWCR & (1 << TWINT)))
      ;
  
    // Ueberpruefung ob START-Condition
	if ((TWSR & 0xF8) != TW_START)
	  error();

    // Senden von Stop
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);	

    // Verarbeitungsschleife
    while(1)
    {
    }
    return 0;
}

void error(void)
{
}
