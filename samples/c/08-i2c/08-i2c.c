// 
// Anpassungen im makefile:
//    ATMega8 => MCU=atmega8 im makefile einstellen
//    lcd-routines.c in SRC = ... Zeile anh�ngen
// 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
// Include der speziellen i2cmaster.h
#include "lcd.h"
#include "uart.h"
#include "i2cmaster.h"

#define UART_BAUD_RATE      9600 
#define DEV_24C128          0xA0

char buffer[20];

int main(void)
{
  DDRD = (1 << PD5);

  // Init des UArts
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );
  sei();
  uart_puts("Init des Uarts\r\n");

  uart_puts("Init des Displays\r\n");
  lcd_init(LCD_DISP_ON_BLINK);
  lcd_clrscr();

  unsigned char ret;

  // Initialisieren des i2c Busses
  uart_puts("Init des i2c Bus\r\n");
  i2c_init();
  ret = i2c_start(0xA2);
  uart_puts("Start auf Device\r\n");
  itoa(ret, buffer, 10);
  uart_puts(buffer);
  uart_puts("Wert in EEPROM schreiben\r\n");
  if ( ret ) {
    i2c_stop();
    PORTD |= ( 1 << PD5);
  }else {
    i2c_write(0x05);
    i2c_write(0x0F);
    i2c_stop();
  }

  PORTD |= ( 1 << PD5);

  // Verarbeitungsschleife
  while(1)
  {
    i2c_start_wait(DEV_24C128 + I2C_READ);
    i2c_write(0x05);
    ret = i2c_readNak();
    i2c_stop();

    char Buffer[20];
    itoa( ret, Buffer, 10);
    lcd_gotoxy(1, 1);
    lcd_puts(Buffer);

    PORTD ^= (1 << PD5);
    _delay_ms(2000);
  }
  return 0;
}