#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  // Port D komplett auf Eingang
  DDRD = 0x00;
  // Port D Ping 5 als Ausgang
  DDRD = (1 << PD5);

  // Verarbeitungsschleife
  while(1) {
    // Wenn Taster gedrückt
    if( PIND & (1 << PIND3) ) {
      // LED Einschalten
      PORTD |= (1 << PD5);
    } else {
      // Ansonsten LED aus
      PORTD &= ~(1 << PD5);
    }
  } 

  return 0;
}
