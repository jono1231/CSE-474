/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 11/2/2023
 * This code blinks LED1 built-in the TIVA board at a rate of 1 Hz.
 * When SW1 is pressed, LED1 stops blinking and LED2 turns on.
 * When SW2 is pressed, LED2 turns off and LED1 starts blinking again.
 */

#include <stdint.h>
#include "lab2p2.h"

void timer_init();
void init_leds();
void sw_init();

int main(void)
{
  GPIODATA_N = 0x0;
  GPIODATA_F = 0x0;
  init_leds();
  timer_init();
  sw_init();
  while(1){}
}

// Handles interrupt for timer
void Timer0A_Handler() {
  GPTMICR_0 = 0x1;
  GPTMCTL_0 |= 0x1;
  GPIODATA_N ^= 0x2;
}

// Handles interrupt when SW's are pressed.
void PortJ_Handler() {
  // SW2
  if (GPIOMIS_J & 1) {
    GPIOICR_J = 0x1;
    GPTMCTL_0 &= ~0x1;
    GPIODATA_N = 0x1;
  }
  // SW1
  if (GPIOMIS_J & 0x2) {
    GPIOICR_J = 0x2;
    GPTMCTL_0 = 0x1;
    GPIODATA_N = 0x2;
  }
}

void init_leds() {
  volatile unsigned short delay = 0;
  RCGCGPIO |=  (1<<5 | 1<<12);
  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info
  
  GPIODIR_N = 0x3;
  GPIODEN_N = 0x3;
  
  NVIC_EN2 |= (1 << 9); // 73 - port N
}

void sw_init() {
  volatile unsigned short delay = 0;
  // Init ports
  RCGCGPIO |=  (1 << 8);
  delay++; // Delay 2 more cycles before access Timer registers
  delay++; // Refer to Page. 756 of Datasheet for info
  
  // Configure buttons
  // Set direction to input
  GPIODIR_J = 0xFC;
  GPIODEN_J = 0x3;

  // Set pull-up resistor since button is connected to ground
  GPIOPUR_J = 0x3;
  // Enable write permissions
  GPIOCR_J = 0x3;
  NVIC_EN1 |= (1 << 19); // 51 - port J
  // Enable interrupt mask
  GPIOIM_J = 0x3;
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