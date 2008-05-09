#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // Port D Pin 5 als Ausgang
  DDRD  = 255;
  PORTD = 0;

  // Verarbeitungsschleife
  while(1) {
    PORTD++;
    // Kurze Wartezeit
    _delay_ms(1000);
  }

  return 0;
}
