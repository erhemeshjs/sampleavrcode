/*
 * Beispielprogramm 08-i2c.c
 *
 * Beispielprogramm, das den I2C Bus ansteuert. Mit diesem wird ein 
 * Wert in den am Bus angeschlossenem EEProm gespeichert und 
 * ausgelesen.
 *
 * (c) Robert Einsle <robert@einsle.de>
 * (c) Michael Hartmann <michael@speicherleck.de>
 * V 1.0, 09.05.2008
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/twi.h>
#include "uart.h"

#define	TRUE	    1
#define	FALSE	    0

#define I2C_ADDR    0xA0

#define I2C_READ    1
#define I2C_WRITE   0

void twi_init(void);
char twi_start(void);
char twi_set_address(char data);
char twi_send(char data);
void twi_stop(void);
void twi_wait(void);
void twi_show_sr(void);

int main(void)
{
    DDRD = (1 << PD5);

    // Init des UArts
    uart_init();

    printf("Hallo Welt\r\n");
  
    // Init des TWI-Bus
    twi_init();

    if (twi_start())
    {
      if (twi_set_address(I2C_ADDR + I2C_WRITE))
      {
        if (twi_send(0xFF))
	{
	  uart_puts("Daten erfolgreich geschrieben\r\n");
	} else {
	  uart_puts("Daten nicht erfolgreich\r\n");
	}
      }
      else
      {
        uart_puts("Adresse nicht erfolgreich uebertragen\r\n");
      }
      twi_stop;
    } else {
      uart_puts("Start konnte nicht gesendet werden!\r\n");
      twi_stop();
    }

    // Setzen der Client-Adresse
    //twi_send(0xA1);

    // Senden der Daten an den Chip
    //twi_send(0xFF);

    // Stop des TWI-Busses
    //twi_stop();

    // Verarbeitungsschleife
    while(1)
    {
    }
    return 0;
}

void twi_init(void)
{
    // Init des TWI-Bus
    uart_puts("Init des TWI-Bus\r\n");
    //TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    TWCR = (1 << TWEN);
    TWSR = 0x00;

    // Setzen der Bitrate
    TWBR = 0x48;
}

char twi_start(void)
{
    // Senden der Start-Condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    twi_wait();

    twi_show_sr();

    // Ueberpruefung ob START-Condition
    if (TWSR & 0xF8  != TW_START)
      return FALSE;
    return TRUE;
}

void twi_wait(void) 
{
    while (!(TWCR & (1 << TWINT)))
      ;
}

char twi_set_address(char data)
{
    // Setzen der Daten
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
	
    // Warten bis TW Start transmitted
    while (!(TWCR & (1 << TWINT)))
      ;
  
    twi_show_sr();
    // Ueberpruefung ob START-Condition
    if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
    {
      printf("TW_START: %#x\r\n", TW_MT_SLA_ACK);
      return FALSE;
    }
    return TRUE;
}

char twi_send(char data)
{
    // Setzen der Daten
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
	
    // Warten bis TW Start transmitted
    while (!(TWCR & (1 << TWINT)))
      ;
  
    twi_show_sr();
    // Ueberpruefung ob START-Condition
    if ((TWSR & 0xF8) != TW_MT_DATA_ACK)
    {
      printf("TW_MT_DATA_ACK: %#x\r\n", TW_MT_DATA_ACK);
      return FALSE;
    }
    return TRUE;
}

void twi_stop(void)
{
    // Senden von Stop
    uart_puts("Stop der Übertragung\r\n");
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);	
}

void twi_show_sr(void)
{
    // Anzeige Inhalt des Status-Registers
    printf("TWSR: %#x\r\n", TWSR);
}
