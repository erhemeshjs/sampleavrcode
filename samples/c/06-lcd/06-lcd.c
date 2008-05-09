/*
 * Beispielprogramm 06-lcd.c
 *
 * Beispielprogramm, das ein LCD-Display, das an PORTA angeschlossen ist,
 * ansteuert.
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
// Include der speziellen lcd.h
#include "lcd.h"
 
int main(void)
{
  // Initialisieren des LCD-DISPLAYS
  lcd_init(LCD_DISP_ON);

  // Löschen des Textes auf dem Display
  lcd_clrscr();
        
  // Zeichnen des Strings auf das Display
  lcd_puts("LCD Test Line 1\n");

  // Der Cursor ist jetzt in der 2. Zeile (\n), jetzt der Inhalt der 2. Zeile
  lcd_puts("Line 2");
  
  // Verarbeitungsschleife      
  while(1)
    {
    }
 
  return 0;
}
