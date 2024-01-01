#ifndef __HEADER5_H__

#define __HEADER5_H__

#define BASEREG    (*((volatile uint32_t *)0x400FE000))
#define GPIOPUR    (*((volatile uint32_t *)0x400FE510))
#define RCGCGPIO   (*((volatile uint32_t *)0x400FE608))
#define RCGCPWM    (*((volatile uint32_t *)0x400FE640))
#define RCGCADC    (*((volatile uint32_t *)0x400FE638))
#define ALTCLKCFG  (*((volatile uint32_t *)0x400FE138))
#define RCGCTIMER  (*((volatile uint32_t *)0x400FE604))
#define RCGCUART   (*((volatile uint32_t *)0x400FE618))

// Configs for UART Port A
#define GPIODEN_A    (*((volatile uint32_t *)0x4005851C))
#define GPIODIR_A    (*((volatile uint32_t *)0x40058400))
#define GPIOAFSEL_A  (*((volatile uint32_t *)0x40058420))
#define GPIOAMSEL_A  (*((volatile uint32_t *)0x40058528))
#define GPIOPCTRL_A  (*((volatile uint32_t *)0x4005852C))

// Configs for Analog Port E
#define GPIOAFSEL_E  (*((volatile uint32_t *)0x4005C420))
#define GPIODEN_E    (*((volatile uint32_t *)0x4005C51C))
#define GPIOAMSEL_E  (*((volatile uint32_t *)0x4005C528))

// Configurations for PWM port F
#define GPIODIR_F    (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F    (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F   (*((volatile uint32_t *)0x4005D3FC))
#define GPIOAFSEL_F  (*((volatile uint32_t *)0x4005D420))
#define GPIOAMSEL_F  (*((volatile uint32_t *)0x4005D528))
#define GPIOPCTRL_F  (*((volatile uint32_t *)0x4005D52C))
#define GPIOPCTL_F   (*((volatile uint32_t *)0x4005D510))
#define GPIOPUR_F    (*((volatile uint32_t *)0x4005D510))

// Switch configurations for port J 
#define GPIODIR_J  (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J  (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))
#define GPIOPUR_J  (*((volatile uint32_t *)0x40060510))
#define GPIOLOCK_J (*((volatile uint32_t *)0x40060520))
#define GPIOCR_J   (*((volatile uint32_t *)0x40060524))   
// interrupt mask for port J
#define GPIOIM_J (*((volatile uint32_t *)0x40060410))
#define GPIOMIS_J (*((volatile uint32_t *)0x40060418))
#define GPIOICR_J (*((volatile uint32_t *)0x4006041C))

// Configs for ADC0
#define ADCACTSS_0    (*((volatile uint32_t *)0x40038000))
#define ADCIM_0       (*((volatile uint32_t *)0x40038008))
#define ADCISC_0      (*((volatile uint32_t *)0x4003800C))
#define ADCEMUX_0     (*((volatile uint32_t *)0x40038014))
#define ADCPSSI_0     (*((volatile uint32_t *)0x40038028))
#define ADCSSCTL3_0   (*((volatile uint32_t *)0x400380A4))
#define ADCSSFIFO3_0  (*((volatile uint32_t *)0x400380A8))
#define ADCSSEMUX3_0  (*((volatile uint32_t *)0x400380B8))
#define ADCCC_0       (*((volatile uint32_t *)0x40038FC8))

// Configs for Timer 0a
#define GPTMCFG_0    (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0   (*((volatile uint32_t *)0x40030004))
#define GPTMCTL_0    (*((volatile uint32_t *)0x4003000C))
#define GPTMIMR_0    (*((volatile uint32_t *)0x40030018))
#define GPTMRIS_0    (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0    (*((volatile uint32_t *)0x40030024))
#define GPTMTAILR_0  (*((volatile uint32_t *)0x40030028))
#define GPTMADCEV_0  (*((volatile uint32_t *)0x40030070))

// Nvic registers
#define NVIC_EN2 (*((volatile uint32_t *)0xE000E108))
#define NVIC_EN1 (*((volatile uint32_t *)0xE000E104))
#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100))

// Configs for PWM0
#define PWMEN  (*((volatile uint32_t *)0x40028008))
#define PWMCC  (*((volatile uint32_t *)0x40028FC8))
#define PWMCTL (*((volatile uint32_t *)0x40028000))

// Configs for PWM0 GEN 0
#define PWMCTL_0  (*((volatile uint32_t *)0x40028040))
#define PWMLOAD_0 (*((volatile uint32_t *)0x40028050))
#define PWMCMPA_0 (*((volatile uint32_t *)0x40028058))
#define PWMCMPB_0 (*((volatile uint32_t *)0x4002805C))
#define PWMGENA_0 (*((volatile uint32_t *)0x40028060))
#define PWMGENB_0 (*((volatile uint32_t *)0x40028064))

// Masks
#define SS3_INTR 0x8  // SS3 Inturrupt mask

// Switch states
#define SW1 0x1
#define SW2 0x2

// Period for the thing
#define PERIOD 1200

// Handler codes to support compatibility with CCS
void ADC0SS3_Handler(void);

// Code for different tasks
void potentiometer();

// Start the system
void begin();

// Delay
void delay(int ticks);

// Switch input
unsigned long switch_input(int iswitch);

#endif //__HEADER5_H__
