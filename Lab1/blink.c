/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 10/10/2023
 *  This code blinks lights on and off in a pattern
 */

#include "lab1task1.h"  // For LEDs and switches
#include <stdint.h>     // For uint32_t

void wait(int ticks) {
  // I cannot for the life of me get a for loop working here we gooooo
  int i = 0;
  while (i < ticks) {
    i++;
  }
}

int main(void) {
  volatile unsigned short delay = 0;

  // Init ports
  RCGCGPIO |=  (1<<5 | 1<<8);
  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info

  GPIODIR_F = 0x11; // Set PF0 and PF4 to the output
  GPIODEN_F = 0x11; // Set PF0 and PF4 digitally

  // Do the same but for PN0 and PN1 (other 2 leds)
  GPIODIR_N = 0x3;
  GPIODEN_N = 0x3;

  while (1) {
    // Turn on lights
    GPIODATA_F = 0x10;
    GPIODATA_N = 0x1;

    wait(400000);
    // Turn on different lights woah so cool
    GPIODATA_F = 0x1;
    GPIODATA_N = 0x2;

    wait(400000);
  }
}
