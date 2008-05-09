#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // Hilfsvariable
  char toggled = 0;
  // Datenrichtung komplett auf Eingang
  DDRD = 0x00;
  // PORTD.5 als Ausgang (LED)
  DDRD = (1 << PD5);

  // Verarbeitungsschleife
  while(1) {
    // Wenn Taster gedrückt
    if ( PIND & (1 << PIND3) ) {
      // Und nicht schon erkannt
      if (toggled == 0) {
        // Dann merken und Bit umschalten
        toggled = 1;
        PORTD = PORTD ^ ( 1 << PD5 );
      }
    } else {
      // Erkennung zurücksetzen
      toggled = 0;
    }
  }
  return 0;
}
