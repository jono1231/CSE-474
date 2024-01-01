/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 11/30/2023
 * This is a file that initializes and prints temperature data
 * from the board to a LCD screen.
 * Additionally, there is touchscreen functionality that
 * changes the frequency of which the board operates
 * 
 * NOTE: There is some commented out code - uncomment that code isntead for task 1a
 */

#include <stdint.h>
#include "SSD2119_Display.h"
#include "lab4.h"
#include "PLL_Header.h"
#include "Lab4_Inits.h"
#include "tm4c1294ncpdt.h"
#include "SSD2119_Touch.h"

uint32_t ADC_value;

enum frequency freq = PRESET2; // 60 MHz

int main(void) {
  LCD_Init();
  Touch_Init();
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();             // Initialize the 4 onboard LEDs (GPIO)
  Button_Init();         // Initalizes on board switches
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0


  while(1) {
    // UNCOMMENT BELOW CODE FOR Task 1a
    // LCD_ColorFill(((0x55>>3)<<11) | ((0xFF>>2)<<5) | (0xFF>>3));
    // LCD_ColorFill(((0xFF>>3)<<11) | ((0x55>>2)<<5) | (0x55>>3));
    // LCD_ColorFill(((0xFF>>3)<<11) | ((0x55>>2)<<5) | (0xFF>>3));

    // UNCOMMENT BELOW CODE FOR Task 1b
    // Read the position of the button press
    unsigned long Y_pos = Touch_ReadY() / 10;
    unsigned long X_pos = Touch_ReadX() / 10;

    // Poll button press (manually calculated with ADC lol)
    if (X_pos >= 100 && X_pos <= 150 &&
          Y_pos >= 70 && Y_pos <= 110) {
      // SW1 pressed
      PLL_Init(PRESET3);
      freq = PRESET3;
      GPIODATA_N = 0x1;
    } else if (X_pos >= 180 && X_pos <= 230 &&
          Y_pos >= 70 && Y_pos <= 110) {
      // SW2 pressed
      PLL_Init(PRESET1);
      freq = PRESET1;
      GPIODATA_N = 0x2;
    } else {
      // By default, do this
      PLL_Init(PRESET2);
      freq = PRESET2;
      GPIODATA_N = 0;
    }
    // UNCOMMENT TO COMPARE ON LCD INPUT WITH ON BOARD INPUT
    // temperature()
  }
  return 0;
}

// Read the temperature and print to the device
void temperature() {
  float temperature;
  temperature = 147.5 - (247.5 * (ADC_value)) / 4096.0;
  printf("Temp: %f\n", temperature);
}


void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC_0 = 0x8;
  GPTMICR_0 |= 0x1;
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3_0;
  // Draw the buttons
  // button 1 x = 135 - 140, button 2 x = 210 - 215, y = 90 - 95
  LCD_DrawFilledRect(50,  175, 50, 50,  Color4[7]);
  LCD_DrawFilledRect(225, 175, 50, 50,  Color4[7]);

  // Set the cursor to a set position
  LCD_SetCursor(0, 0);

  // Calculate temperature
  float temperature_C = 147.5 - (247.5 * (ADC_value)) / 4096.0;
  float temperature_F = (temperature_C * 9.0 / 5.0) + 32.0;
  char text[100];

  // Print to screen
  sprintf(text, "The current temperature is %.2f C, %.2f F.\n", temperature_C, temperature_F);
  LCD_PrintString(text);
  sprintf(text, "The current clock frequency is %d MHz.\n", freq);
  LCD_PrintString(text);
}

// DEPRICATED: USED TO MANUALLY TEST INPUTS
void PortJ_Handler(void) {
  // SW2 - 120 MHz
  if (GPIOMIS_J & 1) {
    GPIOICR_J |= 0x1;
    PLL_Init(PRESET1);
    freq = PRESET1;
    GPIODATA_N = 0x2;
  }
  // SW1 - 12 MHz
  if (GPIOMIS_J & 0x2) {
    GPIOICR_J |= 0x2;
    PLL_Init(PRESET3);
    freq = PRESET3;
    GPIODATA_N = 0x1;
  }
}

