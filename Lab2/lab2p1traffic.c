/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 10/26/2023
 * This class creates a traffic light using timer polling
 * There are two switches - SW1 and SW2 that act as an on/off switch
 * and a pedestrian switch respecitvely.
 * This code uses timers, and will only register these presses if they've been
 * pressed for over 2 seconds
 * SW1 can be pressed anytime to turn the system on and off.
 * SW2 can only be pressed when the traffic light is green, and it turns the light
 * briefly yellow before it turns red.
 * The light will oscillate between red and green when no buttons are pressed.
 */

#include "lab2p1.h"
#include <stdint.h>  // For int
#include <stdlib.h>  // For EXIT_SUCCESS

enum states{off, on_red, on_warn, on_green} curState;

int main(void) {
  init();
  timer_init();
  begin();
  return EXIT_SUCCESS;
}

void begin() {
  while (1) {
    switch (curState) {
      case off:
        // Default off case - sets the thing to off until we
        // we find a button input.
        set_light(OFF);
        // While switch isnt pressed just dont bother
        if (timer1_press(SW1, SECONDS)) {
          curState = on_red;
        }
        break;

      case on_red:
        set_light(RED);
        switch (timer0(SW_SECS)) {
          case 0:
            curState = off;
            break;
          case 1:
            curState = on_green;
            break;
          default:
            curState = on_red;
            break;
        }
        break;
              
      case on_green:
        set_light(GRN);
        switch (timer0(SW_SECS)) {
          case 0:
            curState = off;
            break;
          case 1:
            curState = on_red;
            break;
          case 2:
            curState = on_warn;
            break;
        }
        break;

      case on_warn:
        set_light(YLW);
        switch (timer0(SW_SECS)) {
          case 0:
            curState = off;
            break;
          case 1:
            curState = on_red;
            break;
        }
        break;
      
      default:
        curState = off;
    }
  }
}

void set_light(int color) {
  GPIODATA_L |= color;
  GPIODATA_L &= (color | 0x3);
}

unsigned long switch_input(int iswitch) {
 return (GPIODATA_L & iswitch); // "truthy" if pressed, "falsy" if not
}

void init() {
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
  // 0001 1100
  GPIODIR_L |= 0x1C;

  // Enable digital output for PL0-4
  GPIODEN_L |= 0x1F;

  GPIOPDR_L |= 0x03;

  curState = off;
}

void timer_init() {
  volatile unsigned short delay = 0;
  // Initialize timer as well here because im lazy
  RCGCTIMER = 0x03;
  delay++;
  delay++;
  
  // disable the timer. bit 0 GPTM Timer A enable
  GPTMCTL_0 &= 0x00000000;
  GPTMCTL_1 &= 0x00000000;

  GPTMCFG_0 = 0x0;
  GPTMCFG_1 = 0x0;

  // periodic timer mode
  GPTMTAMR_0 = 0x2;
  GPTMTAMR_1 = 0x2;

  // Count down periodic mode
  GPTMTAMR_0 &= ~0x10;
  GPTMTAMR_1 &= ~0x10;

  // Clear timer values 
  GPTMICR_0 = 0x1;
  GPTMICR_1 = 0x1;
}

int timer0(int sec) {
  clear_timer0();
  reset_timer0(sec);
  while (!timer1_press(SW1, SECONDS)) {
    if (curState == on_green) {
      // Only enter here if ped but is being pressed
      int override = timer0_press(SW2, SECONDS);
      if (override == 1) {
        // Signal a sw2 press
        return 2;
      } else if (override == 2) {
        // Signal a sw1 press
        return 0;
      }
    }
    if (GPTMRIS_0 & 0x1) {
      // Signal nothing happened
      clear_timer0();
      return 1;
    }
  }
  // signal a timer1 press.
  return 0;
}

int timer0_press(int sw, int sec) {
  if (!switch_input(sw)) {
    return 0;
  }
  clear_timer0();
  reset_timer0(sec);
  while (switch_input(sw)) {
    if (timer1_press(SW1, SECONDS)) {
      // On off switch overrides normal things
      return 2;
    }
    if (GPTMRIS_0 == 0x1){      
      clear_timer0();
      return 1;
    }
  }
  return 0;
}

int timer1_press(int sw, int sec) {
  if (!switch_input(sw)) {
    return 0;
  }
  clear_timer1();
  reset_timer1(sec);
  while (switch_input(sw)) {
    if (GPTMRIS_1 == 0x1){      
      clear_timer1();
      return 1;
    }
  }
  return 0;
}

void clear_timer0(){ 
 GPTMCTL_0 &= ~(0x01);
 GPTMICR_0 = 0x01;
}

void clear_timer1(){
  GPTMCTL_1 &= ~(0x01);
  GPTMICR_1 = 0x01;
}

void reset_timer0(int sec){
  GPTMTAILR_0 = HZ * sec;
  GPTMCTL_0 |= 0x01;
}

void reset_timer1(int sec){
  GPTMTAILR_1 = HZ * sec;
  GPTMCTL_1 |= 0x01;
}
