/*
 * usart.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Evan Tchelepi
 */


// This code waits for a character and transmits the character back (with interrupts)


// This code waits for a character and transmits the character back (with interrupts)

#include <avr/io.h>
#include <stdint.h>                     // needed for uint8_t

#include <avr/interrupt.h>

#define UBRR0H _SFR_MEM8(0xC5)
#define UBRR0L _SFR_MEM8(0xC4)
#define UCSR0B _SFR_MEM8(0xC1)
#define UCSR0C _SFR_MEM8(0xC2)
#define UDR0 _SFR_MEM8(0xC6)
#define UCSR0A _SFR_MEM8(0xC0)
#define RXEN0 4
#define RXCIE0 7
#define TXEN0 3
#define UCSZ01 2
#define UCSZ00 1
#define RXC0 7
#define UDRE0 5
#define FOSC 16000000                       // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD -1


volatile char ReceivedChar;

void USART_print(char* string, char len)
{
	char i;
	/*We want to print each char in the string*/
	for(i = 0; i<len;i++)
	{
		/*If it's not empty wait*/
		while ( !(UCSR0A & (1 << UDRE0)) );
		UDR0 = string[i];
	}
}

int main( void )
{
    /*Set baud rate */
    UBRR0H = ((MYUBRR) >> 8);
    UBRR0L = MYUBRR;

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp

    //while(1){
    	USART_print("hello", 5);
    //}

}
