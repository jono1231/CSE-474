/**
 * EE/CSE 474: Lab3 drivers starter code
 */

#include "PLL_Header.h"
#include "Lab5_Inits.h"
#include "lab5.h"

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    } 

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet

  // YOUR CODE HERE
  volatile int delay = 0;

  // enable timer
  RCGCTIMER |= 0x01;
  delay++;
  delay++;

  // Turn timer off
  GPTMCTL_0 &= 0x0;
  
  // 32 bit timer mode
  GPTMCFG_0 |= 0x0;

  // Periodic mode, count down
  GPTMTAMR_0  |=  0x2;
  GPTMTAMR_0 &= ~0x10;

  // Initial times for timer
  GPTMTAILR_0 = HZ;
  
  // Clear timer vals + enable intr mask
  GPTMIMR_0 |= 0x1;
  GPTMICR_0 |= 0x1;

  // Set event send
  GPTMADCEV_0 |= 0x1;

  // Set control to do timer a thing
  GPTMCTL_0 |= 0x21;
}

void PWM_Init(void) {
  volatile uint32_t delay;
  RCGCPWM |= 0x1;
  delay++;
  delay++;
  RCGCGPIO |= (0x1 << 5);
  delay++;
  delay++;
  delay++;

  GPIOAFSEL_F |= 0x3;
  GPIOPCTRL_F |= 0x66;

  GPIODEN_F |= 0x3;
  GPIODIR_F |= 0x3;

  PWMCC &= 0x0;
  PWMCC |= 0x100;

  PWMCTL_0 &= 0x0;

  PWMGENA_0 = 0x8C;
  PWMGENB_0 = 0x80C;

  // System clock = 60 MHz
  // 60,000,000 / 2 = 30 MHz
  // PWM generator = 25 KHz
  // 1 / 25 KHz = 40 microseconds
  // 40*10^-6 * 30 M = 1200
  PWMLOAD_0 = PERIOD - 1;
  PWMCMPA_0 = PERIOD - 2;
  PWMCMPB_0 = 1;

  PWMCTL_0 |= 0x1;
  PWMEN |= 0x3;
}

void Button_Init(void) {
  volatile int delay = 0;
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
}

void ADCReadPot_Init(void) {
  volatile int delay = 0;
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= 1;
  // 2.2: Delay for RCGCADC (Refer to page 1073)
  // Stolen from edstem
  delay++;
  delay++;
  delay++;
  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you 
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC_0 |= 0x01;
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
  RCGCGPIO |= 0x10;
  // 2.7: Delay for RCGCGPIO
  delay++;
  delay++;
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  GPIOAFSEL_E |= 0x8;
  // 2.9: Clear the GPIODEN bits for the ADC input pins
  GPIODEN_E &= ~0x8;
  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIOAMSEL_E |= 0x8;
  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS_0 &= ~0x8;
  // 2.12: Select timer as the trigger for SS3
  ADCEMUX_0 = 0x5000;
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADCSSEMUX3_0 &= 0x0;
  // 2.14: Configure ADCSSCTL3 register
  // FOR TEMPERATURE
  // ADCSSCTL3_0 |= 0x0E;
  // FOR POTENTIOMETER:
  ADCSSCTL3_0 |= 0x06;

  // 2.15: Set the SS3 interrupt mask
  ADCIM_0 |= SS3_INTR;
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  NVIC_EN0 |= (1 << 17);
  // 2.17: Enable ADC0 SS3
  ADCACTSS_0 = 0x8;
  ADCPSSI_0 |= 0x8;
}
// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler
