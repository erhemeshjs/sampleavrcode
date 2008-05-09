#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU    16000000
#endif

int main(void)
{
  DDRD |= ( (1 << PD5) | (1 << PD6) );

  while(1)
  {        
    // LED ein
    PORTD |= (1 << PD5);
    PORTD &= ~(1 << PD6);

    // 1 Sekunde warten
    _delay_ms(1000);

    // LED aus
    PORTD &= ~(1 << PD5);
    PORTD |= ( 1 << PD6);

    // 1 Sekunde warten
    _delay_ms(1000);
  }
  return 0;
}
