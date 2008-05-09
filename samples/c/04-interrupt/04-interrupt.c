#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void) {
  // Enablen der Interrupts an INT1 ( PD3)
  GIMSK = (1 << INT1);
  // Config INT1 steigende Flanke
  MCUCR = ( (1 << ISC11) | (1 << ISC10) );
  // Interrupts ein
  sei();
  // Data Direction Register
  DDRD = 0x00;
  // Port D5 auf Ausgang, LED
  DDRD = (1 << PD5);

  // Sinnlosschleife
  while(1) { }

  return 0;
}

// Einsprung Interrupt Service-Routine
ISR(INT1_vect) {
  // Toggle Bit an PD5 ( LED )
  PORTD = PORTD ^ ( 1 << PD5 );
}

