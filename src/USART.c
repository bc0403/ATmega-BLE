#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>
#include "USART.h"

#ifndef BAUD
#define BAUD  9600
#endif

// USART initialization
void initUSART(void) {
// === step 1 ===, set Baud rate register
  UBRR0H = UBRRH_VALUE;                        /* defined in setbaud.h */
  UBRR0L = UBRRL_VALUE;

  #if USE_2X
    UCSR0A |= (1 << U2X0);
  #else
    UCSR0A &= ~(1 << U2X0);
  #endif

// === step 2 ===, Enable USART transmitter/receiver
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);

// === step 3 ===, set frame format
// 8-bit data, none parity mode, and 1-bit stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   /* 8 data bits, 1 stop bit, this is default */
}


//USART interrupt initialization
void initInterruptUSART(void){
  // === step 1 ===, enable USART interrupts:
  // RXC for Rx interrupt,
  // UDRE for Tx interrupt,
  // TXC for Tx interrupt when using half-duplex
  UCSR0B |= (1 << RXCIE0) ; // enable only RXC interrupt

  // === step 2 ===, enable global interrupts
  sei();
}


void myTx(unsigned char data)
{
  // wait for empty Tx buffer
  // if UDR0 is empty, then UDRE0 == 1
  while (!(UCSR0A & (1 << UDRE0))) {
    ;
  }

  // put data into buffer, send the data
  UDR0 = data;
}

unsigned char myRx(void)
{
  // wait for data to be received
  // if there are unread data reached in Rx buffer, then RXC0 == 1
  while (!(UCSR0A & (1 << RXC0))) {
    ;
  }

  // get and return data from buffer
  return UDR0;
}

void myFlush(void)
{
  unsigned char dummy;
  while (UCSR0A & (1 << RXC0)) {
    dummy = UDR0;
  }
}
