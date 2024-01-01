/**
 * EE/CSE 474: Lab3 Task1a main function
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

// NOTE: This code will now send the temperature over UART0 whenever it's temp is handled

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "Lab3_Inits.h"
#include "lab3.h"
#include "PLL_Header.h"

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  Button_Init();         // Initalizes on board switches
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  UART_Init();           // Initialize UART for reading

  GPIODATA_N = 0x2;

  while(1) {
    // potentiometer();
    temperature();
  }

  return EXIT_SUCCESS;
}

void potentiometer() {
  float resistance;
  // STEP 5: Change the pattern of LEDs based on the resistance.
  // 5.1: Convert ADC_value to resistance in kilo-ohm
  resistance = ADC_value/(4095.0) * 10.0;
  // 5.2: Change the pattern of LEDs based on the resistance
  if (resistance < 2.5) {
    GPIODATA_F = 0x0;
    GPIODATA_N = 0x2;
  } else if (resistance < 5.0) { 
    GPIODATA_F = 0x0;
    GPIODATA_N = 0x3;
  } else if (resistance < 7.5) {
    GPIODATA_F = 0x10;
    GPIODATA_N = 0x3;
  } else {
    GPIODATA_F = 0x11;
    GPIODATA_N = 0x03;
  }
}

void temperature() {
  float temperature = 147.5 - (247.5 * (ADC_value)) / 4096.0;
  printf("Temp: %f\n", temperature);
  GPIODATA_N ^= 0x3;
}

void ADC0SS3_Handler(void) {
   // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC_0 = 0x8;
  GPTMICR_0 |= 0x1;
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3_0;
  float temperature = 147.5 - (247.5 * (ADC_value)) / 4096.0;
  char uart[UARTMSG]; 
  sprintf(uart, "%.2f\n\r", temperature);    
  int i;
  for (i = 0; i < UARTMSG; i++) {
    while (UARTFR_0 & 0x8); // 0x8
    UARTDR_0 = uart[i];
  }
}

void Button_Handler(void) {
  // Turn timer off
  
  GPTMCTL_0 &= 0x0;
  if (GPIOMIS_J & 1) {
    GPIOICR_J = 0x1;
    GPTMCTL_0 &= ~0x1;
    PLL_Init(PRESET1);
  }
  if (GPIOMIS_J & 0x2) {
    GPIOICR_J = 0x2;
    PLL_Init(PRESET3);
  }
  // Set control to do timer a thing
  GPTMCTL_0 |= 0x21;
}
