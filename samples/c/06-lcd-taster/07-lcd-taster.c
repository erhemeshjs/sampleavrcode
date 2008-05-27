/*
 * Beispielprogramm 07-lcd-taster.c
 *
 * Erweitertes Beispielprogramm, das ein LCD-Display an PORTA ansteuert
 * und Informationen ausgibt. Zusätzlich wird an PD3 ein Taster abgefragt,
 * der eine Zähler auf dem Display hochzählt.
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
// Include der speziellen lcd.h
#include "lcd.h"

// Variablen
char changed = 0;
int count = 0x00;

// Einsprung Interrupt Service-Routine
ISR(INT1_vect) {
  // Toggle Bit an PD5 ( LED )
  count++;
  changed++;
}


int main(void)
{
  // Enablen der Interrupts an INT1 ( PD3)
  GIMSK = (1 << INT1);

  // Config INT1 steigende Flanke
  MCUCR = ( (1 << ISC11) | (1 << ISC10) );

  // Initialisieren des LCD-DISPLAYS
  lcd_init(LCD_DISP_ON);

  // Löschen des Textes auf dem Display
  lcd_clrscr();
        
  // Zeichnen des Strings auf das Display
  lcd_puts("LCD Test Line 1\n");

  // Der Cursor ist jetzt in der 2. Zeile (\n), jetzt der Inhalt der 2. Zeile
  lcd_puts("Line 2");

  // Interrupts ein
  sei();
  
  // Verarbeitungsschleife
  while(1)
  {
    // Schreiben ans Display nur bei Aenderung
    if ( changed ) {
      changed = 0;
      // Umwandeln der ZAhl in eine Zeichenkette
      char Buffer[20]; // in diesem {} lokal
      itoa( count, Buffer, 10 ); 

      // Gehe im LCD an Position 2, 8
      lcd_gotoxy(7,1);
      // Ausgabe der ZEichenkette auf dem Display
      lcd_puts(Buffer);
    }
  }
  return 0;
}
