// 
// Anpassungen im makefile:
//    ATMega8 => MCU=atmega8 im makefile einstellen
//    lcd-routines.c in SRC = ... Zeile anhängen
// 
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
