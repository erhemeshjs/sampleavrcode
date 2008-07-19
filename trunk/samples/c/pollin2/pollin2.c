/*
 * Testprogram fuer Pollin Atmel Evulation-Board Verson 2.0
 * Bestell-Nr. 810 038
 *
 * zoli@augusta.de
 * 
*/
 
//#define F_CPU 8000000UL         // CPU-Frequenz in Hz
//#define UART_BAUD_RATE 9600UL   // Baudrate

#include "uart_zo.h"
#include "ringbuffer.h"
#include <avr/io.h>             // AVR Devicespezifische IO-Definitionen
#include <avr/interrupt.h>      // Interrupts
#include <util/delay.h>         // Zeitschleifen

unsigned char version[] = "Atmel Evulation-Board V2.0";	        // Startmeldung/Version
uint32_t sekunden = 0;                         // Sekunden seit 1970-01-01 UTC (siehe auch time.h)
uint32_t delay=500;                            // Zeitverzögerung im ms 
unsigned char status_ADC = '0';
uint8_t adn;                                   // Nr. (0..7) des AD-Wandlers
unsigned char status_LED2 = '0';	       // Status-Flag für LED2 0=aus, 1=ein, t=toggle, s=singleshot
unsigned char *int_to_ascii(uint32_t zahl, unsigned char *ascii_sp);


// Zeitschleife - Anzahl ms
void my_delay_ms(uint16_t ms){
  uint16_t i;
  for(i=0;i<=ms;i++) {
    _delay_ms(1);
  }
}


// Signalton über Summer ausgeben (Port D, Pin 7)
// Signaldauer im ms
void beep(uint16_t dauer){
   PORTD |= 1<<PD7;
   my_delay_ms(dauer);
   PORTD &= ~(1<<PD7);
}

// Signaltiöne ausgeben
void beeps(uint16_t dauer, uint8_t anzahl){
   uint8_t i;
   for(i=1;i<=anzahl;i++){
     beep(dauer);
     my_delay_ms(dauer);
   }
}

// Timer_0_Init für ATmegaXX
void tim0_init(void){
   TCCR0 = (1<<CS01);       // Timerbetrieb; Vorteiler fuer Timmer 0 auf 8 setzen (8MHz/8=1MHz)
   OCR0  = 100;             // 1MHz/100=10kHz (Timerinterrupt alle 0.1ms)
   SFIOR |= (1<<PSR10);     // Prescaler  Reset Timer/Counter 1 und 0
   TIMSK |= (1<<OCIE0);     // Timer0 compare match Interrupt enable
}

// Timer_1_Init für ATmegaXX
void tim1_init(void){
   TCCR1B = (1<<CS11);      // Timerbetrieb; Vorteiler fuer Timmer1 auf 8 setzen (8MHz/8=1MHz)
   OCR1A = 1000;            // 1MHz/1000 (Timerinterrupt alle 1ms)
   OCR1B = 10000;           // 1MHz/10000 (Timerinterrupt alle 10ms)
//   SFIOR |= (1<<PSR10);   // Prescaler  Reset Timer/Counter 1 und 0
//   TIMSK |= (1<<OCIE1A);  // Timer1 compareA match Interrupt enable
//   TIMSK |= (1<<OCIE1B);  // Timer1 compareB match Interrupt enable
}

// Timer_2_Init für ATmegaXX
void tim2_init(void){
   TCCR2 = (1<<CS22 | 1<<CS21);  // Timerbetrieb; Vorteiler fuer Timmer2 auf 256 setzen
                                 // (8MHz/256=31.25kHz)
   OCR2  = 250;                  // 31250Hz/250=125Hz (Timerinterrupt alle 8ms)
   SFIOR |= (1<<PSR2);           // Prescaler Reset Timer/Counter 2
   TIMSK |= (1<<OCIE2);          // Timer2 compare match Interrupt enable
}

// ADC_Init für ARmegaXX
void adc_init(void){
   // AVCC, AD0
   ADMUX = (1 <<REFS0);
   // ADPS: Teilerfaktor = 64 (ADPS1,ADPS2): 8MHz/64=125kHz
   // ADEN: ADC enable
   // ADIE: Interupt enable
   ADCSRA = (1 << ADEN | 1 << ADIE | 1 << ADPS2 | 1 << ADPS1); 
}

// Timer/Counter0 compare match Interuptservice
ISR(TIMER0_COMP_vect)
{
  ;//do nothing
}

// Timer/Counter1 compare A match Interuptservice
ISR(TIMER1_COMPA_vect)
{
  ;//do nothing
}

// Timer/Counter1 compare B match Interuptservice
ISR(TIMER1_COMPB_vect)
{
  ;//do nothing
}

// Timer/Counter2 compare match Interuptservice
ISR(TIMER2_COMP_vect)
{
  static uint8_t ms8;
  if (++ms8 == 125){   // wenn 1 Sekunde vergangen ist (125*8ms)
    sekunden++;        // Sekundenzähler erhöhen
    ms8 = 0;           // und Schleifenzähler zurücksetzen
    PORTD ^= 1<<PD5;   // toggle LED1 (test)
    if (status_ADC != '0')
      ADCSRA |= 1<<ADSC; // ADStartConversion
  }
}

// Interuptservice fuer Analog-Digitalwandler (ADC)
ISR(ADC_vect)
{
   unsigned char tmp_string[11];
   uint16_t adc_value;   // Wert aus Analog-Digital-Wandler
   uint8_t lowbyte, highbyte;
   lowbyte = ADCL;  // Hole zuerst low_Byte
   highbyte = ADCH; // danach high_Byte
   // fuege beide zusammen
   adc_value = highbyte;
   adc_value <<= 8;
   adc_value |= lowbyte;
   buffer_write_s(put_bp, int_to_ascii((uint32_t)adc_value, tmp_string));
   buffer_write_s(put_bp, (unsigned char*)" ");
   buffer_write_s(put_bp, int_to_ascii(sekunden, tmp_string));
   buffer_write_s(put_bp, (unsigned char*)"\n");
}

// System(Kalender)zeit ermitteln; time() siehe time.h
// damit später sekunden als Globalvariable entfallen kann ???
uint32_t get_time(void)
{
  return sekunden;   // Sekunden seit 1970-01-01 UTC (siehe auch time.h)
}

// System(Kalender)zeit setzen; time() siehe time.h
// damit später sekunden als Globalvariable entfallen kann ???

void set_time(uint32_t time)
{
  sekunden = time;   // Sekunden seit 1970-01-01 UTC)
}


// Umwandlung einer 32Bit int to ascii (max. 10 Zeichen)
// Der uebergebene Puffer (ascii_sp) muß mindestens 11 Zeichen lang sein
unsigned char *int_to_ascii(uint32_t zahl, unsigned char *ascii_sp)
{
  int8_t i = 10;                           // index auf letztes Zeichen setzen
    *(ascii_sp + i--) = 0x00;              // mit Null (Stringende) vorbestzen
  while(i>=0){                             // Dezimalstellen nacheinander abarbeiten
    *(ascii_sp + i--) = zahl%10 + 0x30;    // Dezimalziffer in ASCII umwandeln
    zahl /= 10;                            // nächste Dezimalstelle
  }
  return ascii_sp;                         // gib Stringpointer zurück
}


// Umwandlung einer ascii-Zahl (max. 10 Zeichen) in eine 32Bit int
uint32_t ascii_to_int(unsigned char *ascii_sp)
{
  uint32_t zahl=0;
  while(*ascii_sp != 0x00){		   // bis Stringende erreicht ist
    zahl = zahl*10 + *ascii_sp - 0x30;     // 10er Potenz erhöhen und nächste Stelle addieren
    ascii_sp++;
  }
  return zahl;                         	   // gib Zahl zurück
}


// Parser fuer Komandoeingabe
// Syntax: <Befehl><Geraet>:[Subbefehl]<Parameter>
// Befehl "!" setzt Parameter
// Befehl "?" liest Parameter
// Ausgaben des mc werden mit "#" eingeleitet
// Gerät "An" ADC An (n=0..7)
// Gerät "S" Systemzeit, "Ln" LEDn, "V" Version
// !A0:1 --> ADC0 gibt im Sekundenrythmus Werte aus; !A0:0 stopped den ADC0
// !L2:t100 --> LED2 blinkt im 100ms Rhytmus
void parser(unsigned char* p_p)
{
   switch(*p_p) {

      // Parameter setzen mit "!"
      case '!':
      switch(*(++p_p)){    

         case 'A':                   // ADC Analog Digitalwandler *******************************
	 ++p_p;
	 if('0'<=*p_p && *p_p<='7'){                 // 0 <= n <=7
            ADMUX &= 0xF0;                           // MUX0..3 loeschen
            ADMUX |= (*p_p - 0x30);                  // AD-Wandler Nr. n (0..7) wählen
	    ++p_p;		                     // nächste Zeichen (:) ignorieren
            switch(*(++p_p)){
               case '0':
	       status_ADC='0';                       // ADC sperren
	       break;
               case '1':
               status_ADC='1';                       // ADC freigeben
               break;
	       default:
               buffer_write_s(put_bp, (unsigned char*)"#!:Error\n> ");
               beeps(100,2);
            }
	    buffer_write_s(put_bp, (unsigned char*)"#!:OK\n");
            beeps(100,1);
	 }
	 else{   
            buffer_write_s(put_bp, (unsigned char*)"#!:Error\n> ");
            beeps(100,2);
         }
	 break;                       // ende ADC

	 // LED setzen *********************************************
         case 'L':
           switch(*(++p_p)){
             case '2':                // LED2 -->
             ++p_p;                   // nächste Zeichen (:) ignorieren
             switch(*(++p_p)){

                case '0':
                PORTD &= ~(1<<PD6);   // LED2 aus
                status_LED2='0';
                break;

                case '1':
                PORTD |= 1<<PD6;      // LED2 an
                status_LED2='1';
                break;

                case 's':
                PORTD |= 1<<PD6;      // LED2 singleshot
                status_LED2='s';
                delay = ascii_to_int(++p_p);
                break;

                case 't':
                PORTD |= 1<<PD6;      // LED2 toggle
                status_LED2='t';
                delay = ascii_to_int(++p_p);
                break;

                default:
                buffer_write_s(put_bp, (unsigned char*)"#?:Error\n> ");
                beeps(100,2);
                break;
             }
             buffer_write_s(put_bp, (unsigned char*)"#!:OK\n> ");
             beeps(100,1);
	  }
	  break;
	  
	  // Systemzeit setzen *************************************
	  case 's':
          sekunden = ascii_to_int(++p_p);
          buffer_write_s(put_bp, (unsigned char*)"#!:OK\n> ");
          beeps(100,1);
          break;
          default:
          buffer_write_s(put_bp, (unsigned char*)"#: Error\n> ");
          beeps(100,2);
       }
       break;

       // Parameter abfragen
       case '?': switch(*(++p_p)){

	  // Systemzeit auslesen ***********************************
          case 's':
          buffer_write_s(put_bp, (unsigned char*)"#s: ");
	  unsigned char timestring[11];
          buffer_write_s(put_bp, int_to_ascii(sekunden, timestring));
          buffer_write_s(put_bp, (unsigned char*)"\n> ");
          beeps(100,1);
	  break;
             
	  // Soft- Hardwareversion auslesen
          case 'v':
          buffer_write_s(put_bp, (unsigned char*)"#v: ");
          buffer_write_s(put_bp, version);
          buffer_write_s(put_bp, (unsigned char*)"\n> ");
          beeps(100,1);
	  break;

	  // Hilfe ausgeben
	  case 'h':
          buffer_write_s(put_bp, (unsigned char*)"#h: <command><device><number>:<subcommand>[parameter]\n> ");
          beeps(100,1);
	  break;

	  default:
          buffer_write_s(put_bp, (unsigned char*)"#: Error\n> ");
          beeps(100,2);
       }
       break;

       case '0': buffer_write_s(put_bp, (unsigned char*)"Taste 0 wurde gedrückt - LED2 1000ms\n> ");
       beep(100);
       buffer_write_s(put_bp, (unsigned char*)"Ausgabe über Interruptserviceroutine\n> ");
       break;
       
       case '1': buffer_write_s(put_bp, (unsigned char*)"Taste 1 wurde gedrückt - LED2 100ms\n> ");
       beep(100);
       delay=100;
       break;
       
       // Hilfe ausgeben (mit ?h zusammenführen)
       case 'h':
       case 0:
       buffer_write_s(put_bp, (unsigned char*)"#h: <command><device><number>:<subcommand>[parameter]\n> ");
       beeps(100,2);
       break;
       
       default:
       buffer_write_s(put_bp, (unsigned char*)"#: unbekantes Zeichen: ");
       buffer_write(put_bp,*p_p);
       buffer_write_s(put_bp, (unsigned char*)"\n");
       beeps(100,2);
    }
}

int main (void) {
   unsigned char kommando[32];                    		// Kommandozeilenbuffer
   unsigned char* k_sp = kommando;		  		// und dazugehöriger Pointer
   volatile struct buffer put_buffer, get_buffer; 		// Sende- u. Empfangsbuffer

   buffer_init(put_buffer);
   buffer_init(get_buffer);
   put_bp=&put_buffer;
   get_bp=&get_buffer;

   DDRD  = 0xE0;         // Port D, Pin 6,7,8 als Ausgang

   tim0_init();          // Initialisiere Timer_0
   tim1_init();          // Initialisiere Timer_1
   tim2_init();          // Initialisiere Timer_2
   uart_init();          // Initialisiere serielle Schnittstelle
   adc_init();		 // Initialisiere Analog-Digitalwandler ADC

   uart_puts(version);	 // Startmeldung/Version ausgeben
   beep(1000);
   uart_puts("\n> ");    // newline und prompt
   UCSRB |= (1<<RXCIE);  // Empfaenger-Interrupts freigeben
   sei();                // Interrupts global freigeben


   while(1) {

     while(buffer_size(get_bp)){
       *k_sp = buffer_read(get_bp);
       uart_putc(*k_sp);
       if(*k_sp == '\n' || *k_sp == '\r'){
         *k_sp = 0x00;
         k_sp=kommando;
         uart_putc('\n');
//         uart_puts(k_sp);   // Ausgabe für Testwecke
	 parser(k_sp);
       }
       else
         k_sp++;
	 // hier noch Bufferoverflow abfangen
     }
           
     if(status_LED2 == 's'){
       PORTD ^= 1<<PD6;       // toggle LED2
       my_delay_ms(delay);    // warte delay ms
       PORTD ^= 1<<PD6;       // toggle LED2
       status_LED2 = '0';     // Status_Flag auf Aus
     }
     if(status_LED2 == 't'){
       my_delay_ms(delay);    // warte delay ms
       PORTD ^= 1<<PD6;       // toggle LED2
     }
   } 
   /* wird nie erreicht */
   return 0;
}
