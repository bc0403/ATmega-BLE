/*
A simple demo for Arduino UNO R3 (ATmega328p) + BLE communication.
Takes in a character at a time and sends it right back out.
if BLE send a character 'A' --> turn on the on board LED
if BLE send a character 'B' --> turn off the on board LED
*/

/*
hardware connections:
ATmega pins   |     BLE module pins
Rx (PD0)    <--->   Tx
Tx (PD1)    <--->   Rx
VCC         <--->   VCC
GND         <--->   GND
*/

/*
BLE module: LinkSprite, BLE4.0 Shield based on TICC2541
*/

/*
BLE app on mobile phone:
BLE debug app such as LightBlue on App store
*/

/*
reference:
[1] Williams E. AVR Programming: Learning to Write Software for Hardware[M]. Maker Media, Inc., 2014.
[2] ATmega328p datasheet
[3] http://learn.linksprite.com/arduino/shields/how-to-use-ble4-0-shield/ (BLE module)
[4] http://maxembedded.com/2015/06/setting-up-avr-gcc-toolchain-on-linux-and-mac-os-x/ (avr-gcc + avrdude toolchain)
*/


// ------- Preamble -------- //
#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"

// ------ global variables ------ //
volatile unsigned char c;

// ------ interrupt ISR & initialization ------ //
//ISR for Tx
// ISR(USART_UDRE_vect){
//   myTx(c);
// }

//ISR for Rx
ISR(USART_RX_vect){
  c = myRx();
  myTx(c);
}



// ------ main function ------ //
int main(void) {


  // -------- Inits --------- //

  // config on board LED (D13/PB5)as output
  DDRB |= (1 << PB5);

  // initialize USART and interrupts
  initUSART();
  myFlush();
  initInterruptUSART();

  // ------ Event loop ------ //
  while (1) {
    // // loopback for polling mode
    // c = myRx();
    // myTx(c);

    // loopback for interrupt mode
    // no code needed in while loop
    // using initInterruptUSART, 2 ISR

    // if receive 0x41('A'), turn on-board LED on
    if (c == 'A')
        PORTB |= (1 << PB5);
    // if receive 0x42('B'), turn on-board LED off
    if (c == 'B')
        PORTB &= ~(1 << PB5);
  }
  /* End event loop */
  return 0;
}
