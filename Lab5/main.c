#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "lab5.h"
#include "Lab5_Inits.h"

uint32_t ADC_value;

int main() {
  PWM_Init();
  Button_Init();
  PLL_Init(PRESET2);
  ADCReadPot_Init();
  TimerADCTriger_Init();

  begin();

  return EXIT_SUCCESS;
}

void begin() {

  // Code to control 2 LEDs with buttons
  // int i = PERIOD - 1;
  // while(1) {
  //   // Check switch input
  //   if (switch_input(SW1)) {
  //     if (i > 2) {
  //       // Decrement if A val > 0
  //       i--;
  //       PWMCMPA_0 = i;
  //       PWMCMPB_0 = PERIOD - i;
  //     }
  //   } 
  //   if (switch_input(SW2)) {
  //     if (i < PERIOD-2) {
  //       // Increment if A val < Period
  //       i++;
  //       PWMCMPA_0 = i;
  //       PWMCMPB_0 = PERIOD - i;
  //     }
  //   }

  //   // Delay so it can be seen by people lol
  //   delay(2000);
  // }

  // Code to use a potentiometer to do this
  while (1) {
    // Configure resistence - scale of 1-10? - for every 1.0 res, have it equal to like... 100 potentiometer 
    float resistance = ADC_value/(4095.0) * 10;

    // 10 * 119 = 1190 < 1200 - so it doesnt trigger weird = 0 shenanigans
    PWMCMPA_0 = resistance * 119 + 2;
    PWMCMPB_0 = PERIOD - (resistance * 119) - 2;
  }
}

unsigned long switch_input(int iswitch) {
  return (GPIODATA_J & iswitch); // "truthy" if pressed, "falsy" if not
}

void delay(int ticks) {
  int i;
  for (i = 0; i < ticks; i++){
    // have fun :D
  }
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC_0 |= 0x1;
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3_0;
}
