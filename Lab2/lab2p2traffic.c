/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 11/2/2023
 * This class creates a working traffic light using timer inturrupts
 * There are two switches - SW1 and SW2 that act as an on/off switch
 * and a pedestrian switch respecitvely.
 * This code uses timers, and will only register these presses if they've been
 * pressed for over 2 seconds
 * SW1 can be pressed anytime to turn the system on and off.
 * SW2 can only be pressed when the traffic light is green, and it turns the light
 * briefly yellow before it turns red.
 * The light will oscillate between red and green when no buttons are pressed.
 */

#include "lab2p2.h"
#include <stdint.h>  // For int
#include <stdlib.h>  // For EXIT_SUCCESS

int main(void) {
  init();
  begin();
  return EXIT_SUCCESS;
}

void begin() {
  while (1) {
    switch (curState) {
      case off:
        set_light(OFF);
        off_check();
        break;
      case on_red:
        set_light(RED);
        on_check();
        break;
      case on_warn:
        set_light(YLW);
        on_check();
        break;
      case on_green:
        set_light(GRN);
        on_check();
        break;
      default:
    }
  }
}

void init() {
  system_init();
  timer_init();
  curState = off;
}

void system_init() {
  // activate clock for Port L
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x400;
  delay++;
  delay++;

  // Disable analog function for PL0-4
  GPIOAMSEL_L &= ~0x1F;
  
  // Select PL0-4 reg port function
  GPIOAFSEL_L &= ~0x1F;
  
  // Set PL2-4 to output, PL0-1 to input
  GPIODIR_L |= 0x1C;

  // Enable digital output for PL0-4
  GPIODEN_L |= 0x1F;

  GPIOPDR_L |= 0x03;

  curState = off;
}

void timer_init() {
  volatile int delay = 0;

  // enable timer
  RCGCTIMER = 0x03;
  delay++;
  delay++;

  // Set timer mode - off
  GPTMCTL_0 &= 0x0;
  GPTMCTL_1 &= 0x0;
  
  // 32 bit timer mode
  GPTMCFG_0 = 0x0;
  GPTMCFG_1 = 0x0;

  // Periodic mode, count down
  GPTMTAMR_0 = 0x2;
  GPTMTAMR_1 = 0x2;
  GPTMTAMR_0 &= ~0x10;
  GPTMTAMR_1 &= ~0x10;

  // Initial times for timers
  // Timer 0 is switch timer, timer 1 is second timers
  GPTMTAILR_0 = HZ * SECONDS;
  GPTMTAILR_1 = HZ * SW_SECS;
  
  // Clear timer vals
  GPTMICR_0 = 0x01;
  GPTMICR_1 = 0x01;

  GPTMIMR_0 = 0x1;
  GPTMIMR_1 = 0x1;

  // Init timer inturrupts
  NVIC_EN0 |= (1 << 19); // 19 - timer0a
  NVIC_EN0 |= (1 << 21); // 21 - timer1a
}

void set_light(int color) {
  GPIODATA_L |= color;
  GPIODATA_L &= (color | 0x3);
}

unsigned long switch_input(int iswitch) {
 return (GPIODATA_L & iswitch); // "truthy" if pressed, "falsy" if not
}

void off_check() {
  // Turn the timer on, clear flags
  GPTMTAILR_0 = HZ * SECONDS;
  GPTMCTL_0 |= 0x01;
  while (switch_input(SW1)) {
    if (curState != off) {
      // Only here if inturrupt went off
      break;
    }
  }
}

void on_check() {
  // Turn the timer on, clear flags
  GPTMTAILR_0 = HZ * SECONDS;
  GPTMCTL_0 |= 0x01;
  while (switch_input(SW1)) {
    if (curState == off) {
      return;
    }
  }

  // Switch 1 isnt being pressed, reset timer on timer 2
  GPTMTAILR_0 = HZ * SECONDS;
  while (curState == on_green && switch_input(SW2)) {
    // We want to prioritize the switch 1 press
    if (switch_input(SW1)) {
      // Turn the timer on, clear flags
      GPTMTAILR_0 = HZ * SECONDS;
      GPTMCTL_0 |= 0x01;
      while (switch_input(SW1)) {
        if (curState == off) {
          // only here because we turned off
          return;
        }
      }
    }
  }
}

void Timer0A_Handler(void) {
  GPTMICR_0 = 0x01;
  // Check states
  if (curState == off) {
    // Turning on, turn on the other timers
    GPTMTAILR_1 = HZ * SW_SECS;
    GPTMCTL_1 |= 0x01;
    curState = on_red;
  } else if (switch_input(SW1)) {
    // Turning off, turn off other timer
    GPTMCTL_1 &= ~(0x01);
    GPTMICR_1 = 0x01;
    curState = off;
  } else {
    // Only time we're here is in on_green.
    // Dont forget to reset timer 1 state
    GPTMICR_1 = 0x01;
    GPTMTAILR_1 = HZ * SW_SECS;
    curState = on_warn;
  }

  // Turn me off.
  GPTMCTL_0 &= ~(0x01);
  GPTMICR_0 = 0x01;
}

void Timer1A_Handler(void) {
  GPTMICR_1 = 0x01;
  // Check states
  if (curState == on_warn || curState == on_green) {
    curState = on_red;
  } else if (curState == on_red) {
    curState = on_green;
  }
}
