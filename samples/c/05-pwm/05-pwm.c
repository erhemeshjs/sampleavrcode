#include <avr/io.h>
#include <util/delay.h>

int main(void) {

  DDRD |= (1<<PD4)|(1<<PD5);
  TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM10); 
  TCCR1B = (1<<CS11); 
  int i;

  // Verarbeitungsschleife
  while(1) {
    for (i = 0; i < 255; i=i+1)
      {
        OCR1A = i;
        _delay_ms(10);
      }
  } 

  return 0;
}
