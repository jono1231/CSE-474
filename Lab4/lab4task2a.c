/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 11/30/2023
 * This file is the implementation of a traffic light
 * using a timer and a LCD touchscreen.
 * There are two switches - SW1 and SW2 that act as an on/off switch
 * and a pedestrian switch respecitvely. The switches will be
 * drawn on the LCD screen, as well as 3 "lights" above them
 * This code uses timers, and will only register these presses if they've been
 * pressed for over 2 seconds
 * SW1 can be pressed anytime to turn the system on and off.
 * SW2 can only be pressed when the traffic light is green, and it turns the light
 * briefly yellow before it turns red.
 * The light will oscillate between red and green when no buttons are pressed 
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lab4.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
#include "PLL_Header.h"
#include "Lab4_Inits.h"

enum states{off, on_red, on_warn, on_green} traffic;

int main(void) {
  LCD_Init();
  Touch_Init();
  PLL_Init(PRESET2);
  timer_init();
  display_init();
  begin();
  return EXIT_SUCCESS;
}

void begin() {
  while (1) {
    switch (traffic) {
      case off:
        // Default off case - sets the thing to off until we
        // we find a button input.

        // Turn all lights off here
        LCD_DrawFilledCircle(30,  30, 25, Color4[7]);
        LCD_DrawFilledCircle(100, 30, 25, Color4[7]);
        LCD_DrawFilledCircle(170, 30, 25, Color4[7]);
        // While switch isnt pressed just dont bother

        if (timer1_press(SW1, SECONDS)) {
          traffic = on_red;
        }
        break;

      case on_red:
        // Red light on here
        LCD_DrawFilledCircle(30,  30, 25, Color4[4]);
        LCD_DrawFilledCircle(100, 30, 25, Color4[7]);
        LCD_DrawFilledCircle(170, 30, 25, Color4[7]);

        switch (timer0(SW_SECS)) {
          case 0:
            traffic = off;
            break;
          case 1:
            traffic = on_green;
            break;
          default:
            traffic = on_red;
            break;
        }
        break;
              
      case on_green:
        // Green light on here
        LCD_DrawFilledCircle(30,  30, 25, Color4[7]);
        LCD_DrawFilledCircle(100, 30, 25, Color4[7]);
        LCD_DrawFilledCircle(170, 30, 25, Color4[2]);

        switch (timer0(SW_SECS)) {
          case 0:
            traffic = off;
            break;
          case 1:
            traffic = on_red;
            break;
          case 2:
            traffic = on_warn;
            break;
        }
        break;

      case on_warn:
        // Yellow light on here
        LCD_DrawFilledCircle(30,  30, 25, Color4[7]);
        LCD_DrawFilledCircle(100, 30, 25, Color4[14]);
        LCD_DrawFilledCircle(170, 30, 25, Color4[7]);

        switch (timer0(SW_SECS)) {
          case 0:
            traffic = off;
            break;
          case 1:
            traffic = on_red;
            break;
        }
        break;
      
      default:
        traffic = off;
    }
  }
}

void display_init() {
  // TODO: Draw the drwaings here, add buttons too
  LCD_DrawFilledCircle(30,  30, 25, Color4[7]);
  LCD_DrawFilledCircle(100, 30, 25, Color4[7]);
  LCD_DrawFilledCircle(170, 30, 25, Color4[7]);

  // Draw the buttons
  LCD_DrawFilledRect(50,  175, 50, 50, Color4[1]);
  LCD_DrawFilledRect(225, 175, 50, 50, Color4[1]);
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
    if (traffic == on_green) {
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
  unsigned long Y_pos = Touch_ReadY() / 10;
  unsigned long X_pos = Touch_ReadX() / 10;
  printf("%lu %lu\n", X_pos, Y_pos);
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

int start_stop_pressed() {
  unsigned long Y_pos = Touch_ReadY() / 10;
  unsigned long X_pos = Touch_ReadX() / 10;

  return (X_pos >= 100 && X_pos <= 150 &&
          Y_pos >= 70 && Y_pos <= 110);
}

int pedestrian_pressed() {
  unsigned long Y_pos = Touch_ReadY() / 10;
  unsigned long X_pos = Touch_ReadX() / 10;

  return (X_pos >= 180 && X_pos <= 230 &&
          Y_pos >= 70 && Y_pos <= 110);
}

unsigned long switch_input(int iswitch) {
  if (iswitch == SW1) {
    return start_stop_pressed();
  } else if (iswitch == SW2) {
    return pedestrian_pressed();
  }
  return 0;
}
