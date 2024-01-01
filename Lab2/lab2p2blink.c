/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 11/2/2023
 * This code blinks the LEDs built-in the TIVA board in the same
 * pattern as done in Lab 1 task 1a and Lab 2 task 1a using interrupts
 * rather than polling.
 */


#include <stdint.h>
#include "lab2p2.h"

void timer_init();
void init_leds();


int main(void)
{
  init_leds();
  timer_init();
  while(1){}
}

void init_leds() {
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x1120;
  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info

  GPIODIR_F = 0x11; // Set PF0 and PF4 to the output
  GPIODEN_F = 0x11; // Set PF0 and PF4 digitally
  
  // Do the same but for PN0 and PN1 (other 2 leds)
  GPIODIR_N = 0x3;
  GPIODEN_N = 0x3;
    
  NVIC_EN1 |= (1 << 30); // 30 - port F
  NVIC_EN2 |= (1 << 9); // 73 - Port N
  
  GPIODATA_F = 0x0;
  GPIODATA_N = 0x0;
  
  GPIODATA_F = 0x01;
  GPIODATA_N = 0x2;
}

// timer interrupt handler
void Timer0A_Handler() {
  GPTMICR_0 = 0x1;
  GPIODATA_F ^= 0x11;
  GPIODATA_N ^= 0x3;
}

void timer_init() {
  RCGCTIMER = 0x1;
  GPTMCTL_0 = 0x0; // control on/(off)
  GPTMCFG_0 = 0x0; // timer configuration
  GPTMTAMR_0 = 0x02; // timer mode (one-shot/periodic)
  GPTMTAILR_0 = 0xF42400; // load register 16 MHz
  GPTMIMR_0 = 0x1;
  GPTMICR_0 = 0x1; // clears flag
  NVIC_EN0 |= (1 << 19); // 19 - timer
  GPTMCTL_0 = 0x1;

}