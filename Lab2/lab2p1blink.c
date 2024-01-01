/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 10/26/2023
 * This code turns a light on and off based on timer 0 input 
 */

#include "lab2p1.h"
#include <stdint.h>  // For int
#include <stdlib.h>  // For EXIT_SUCCESS


/**
 * main.c
 */
int main(void)
{
  init();
  begin();
  return EXIT_SUCCESS;
}

void begin() {
  GPIODATA_F = 0x10;
  GPIODATA_N = 0x1;

  while (1) {
    if (timer0()) {
      GPIODATA_F ^= 0x11;
      GPIODATA_N ^= 0x3;
    }
  }
}

unsigned long timer0() {
  if (GPTMRIS_0 & 0x1) {
    GPTMICR_0 = 0x1;
    return 1;
  }
  return 0;
}

void init() {
  volatile unsigned short delay = 0;

  // Init ports
  RCGCGPIO |=  0x1120;
  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info

  GPIODIR_F = 0x11; // Set PF0 and PF4 to the output
  GPIODEN_F = 0x11; // Set PF0 and PF4 digitally

  // Do the same but for PN0 and PN1 (other 2 leds)
  GPIODIR_N = 0x3;
  GPIODEN_N = 0x3;

  timer_init();
}

void timer_init() {
  int delay = 0;
  RCGCTIMER = 0x1;
  delay++;
  delay++;

  GPTMCTL_0   = 0x0; // control on/(off)
  GPTMCFG_0   = 0x0; // timer configuration
  GPTMTAMR_0  = 0x02; // timer mode (one-shot/periodic)
  GPTMTAILR_0 = 0xF42400; // load register 16 MHz
  GPTMICR_0   = 0x1; // clears flag
  GPTMCTL_0   = 0x1;
}
