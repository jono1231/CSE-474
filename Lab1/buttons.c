/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 10/10/2023
 * This code turns lights on and off when switches are pressed
 */

#include "lab1task1.h"  // For LEDs, registers, and switches
#include <stdint.h>     // For uint32_t

int main(void) {
  volatile unsigned short delay = 0;

  // Init ports
  RCGCGPIO |=  (1<<5 | 1<<8 | 1<<12);
  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info

  GPIODIR_F = 0x11; // Set PF0 and PF4 to the output
  GPIODEN_F = 0x11; // Set PF0 and PF4 digitally

  // Do the same but for PN0 and PN1 (other 2 leds)
  GPIODIR_N = 0x3;
  GPIODEN_N = 0x3;

  // Configure buttons
  // Set direction to input
  GPIODIR_J = 0xFC;
  GPIODEN_J = 0x3;

  // Set pull-up resistor since button is connected to ground
  GPIOPUR_J = 0x3;
  // Enable write permissions
  GPIOCR_J = 0x3;

  while (1) {
    // read PJ0 into SW1, PJ1 into SW2
    uint32_t SW1 = GPIODATA_J & 0x01;
    uint32_t SW2 = GPIODATA_J & 0x02;

    // Use button logic.
    // Button logic is wrong, not correct according to specs
    if (SW1 && SW2) {
      GPIODATA_F = 0x1;
      GPIODATA_N = 0x0;
    } else if (SW2) {
      GPIODATA_F = 0x10;
      GPIODATA_N = 0x0;
    } else if (SW1) {
      GPIODATA_N = 0x1;
      GPIODATA_F = 0x0;
    } else {
      GPIODATA_N = 0x2;
      GPIODATA_F = 0x0;
    }
  }
}
