// 
// Anpassungen im makefile:
//    ATMega8 => MCU=atmega8 im makefile einstellen
//    lcd-routines.c in SRC = ... Zeile anhängen
// 
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
