/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 10/18/2023
 * This is class creates a working traffic light
 * There are two switches - SW1 and SW2 that act as an on/off switch
 * and a pedestrian switch respecitvely.
 * SW1 can be pressed anytime to turn the system on and off.
 * SW2 can only be pressed when the traffic light is green, and it turns the light
 * briefly yellow before it turns red.
 * The light will oscillate between red and green when no buttons are pressed.
 */

#include "traffic.h"  // For registers, switches, LEDs, ect
#include <stdint.h>   // For int
#include <stdlib.h>   // For EXIT_SUCCESS

int main(void) {
  init();
  begin();
  return EXIT_SUCCESS;
}

void begin() {
  int temp; // Create a temp integer to store results.
  while (1) {
    switch (curState) {
      case off_temp:
        // This and on_temp are used to debounce buttons
        // A major problem we had was button signal still
        // existing even after we stopped pressing them.
        set_light(OFF);
        while (switch_input(SW1)) {} // Prevent any weird "holding the button" shenanigans
        wait(500000);
        curState = off_off;
        break;

      case off_off:
        // Default off case - sets the thing to off until we
        // we find a button input.
        set_light(OFF);
        if (switch_input(SW1)) {
          while (switch_input(SW1)) {} // Prevent any weird "holding the button" shenanigans
          curState = on_temp;
        }
        break;

      case on_temp:
        // This and off_temp are used to debounce buttons
        // A major problem we had was button signal still
        // existing even after we stopped pressing them.
        set_light(OFF);
        wait(500000);
        // Begin the loop
        curState = on_red;
        break;

      case on_red:
        set_light(RED);
        // Use wait_on to get any switch output values
        temp = wait_on(1000000, 0);
        if (temp == 1) {
          // Button was pressed, we go to the debounce state
          curState = off_temp;
        } else if (temp == 2) {
          // Pedestrian button was pressed, we will stay red.
          // Undocumented choice - we're not supposed to do anything.
          curState = on_red;
        } else {
          // Exited normally
          curState = on_green;
        }
        break;
              
      case on_green:
        set_light(GRN);
        // Use wait on to get results of button, same as on_red except 
        // for 1 case documented below
        temp = wait_on(1000000, 0);
        if (temp == 1) {
          curState = off_temp;
        } else if (temp == 2) {
          // If button 2 was pressed, we immediately go to warn state.
          curState = on_warn;
        } else {
          curState = on_red;
        }
        break;

      case on_warn:
        set_light(YLW);
        // Using wait_on, same cases as below
        if (wait_on(600000, 1) == 1) {
          curState = off_temp;
        } else {
          curState = on_red;
        }
        break;
      
      default:
        curState = off_off;
    }
  }
}

void wait(int time) {
  // Off state/debounce wait method
  int i = 0;
  for (; i < time; i++) {}
}

int wait_on(int time, int isYellow) {
  // On state waiting method
  int i = 0;
  for (; i < time; i++) {
    // If switch 1 pressed we get out immediately - inturrupt
    if (switch_input(SW1)) {
      return 1;
    }

    // If we're not yellow and switch 2 is pressed, we also can get out.
    if (!isYellow && switch_input(SW2)) {
      return 2;
    }
  }
  return 0;
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

  curState = off_off;
}
