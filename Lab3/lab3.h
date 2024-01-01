/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 11/8/2023
 * This is a header file that defines all needed registers
 * and macros to read inputs from both a potentiometer 
 * and the on-board temperature, as well as support
 * UART and bluetooth interfacing with everything
 */

#ifndef __HEADER3_H__

#define __HEADER3_H__

#define BASEREG    (*((volatile uint32_t *)0x400FE000))
#define GPIOPUR    (*((volatile uint32_t *)0x400FE510))
#define RCGCGPIO   (*((volatile uint32_t *)0x400FE608))
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

// Configs for Analog Port K
#define GPIOAFSEL_K  (*((volatile uint32_t *)0x40061420))
#define GPIODEN_K    (*((volatile uint32_t *)0x4006151C))
#define GPIOAMSEL_K  (*((volatile uint32_t *)0x40061528))

// LED Configurations for port F
#define GPIODIR_F  (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F  (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

// LED configurations for port N
#define GPIODIR_N  (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N  (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

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

// Configs for UART 0
#define UARTDR_0    (*((volatile uint32_t *)0x4000C000))
#define UARTFR_0    (*((volatile uint32_t *)0x4000C018))
#define UARTCTL_0   (*((volatile uint32_t *)0x4000C030))
#define UARTIBRD_0  (*((volatile uint32_t *)0x4000C024))
#define UARTFBRD_0  (*((volatile uint32_t *)0x4000C028))
#define UARTLCRH_0  (*((volatile uint32_t *)0x4000C02C))
#define UARTCC_0    (*((volatile uint32_t *)0x4000CFC8))

// Configs for UART 2
#define UARTDR_2    (*((volatile uint32_t *)0x4000E000))
#define UARTFR_2    (*((volatile uint32_t *)0x4000E018))
#define UARTCTL_2   (*((volatile uint32_t *)0x4000E030))
#define UARTIBRD_2  (*((volatile uint32_t *)0x4000E024))
#define UARTFBRD_2  (*((volatile uint32_t *)0x4000E028))
#define UARTLCRH_2  (*((volatile uint32_t *)0x4000E02C))
#define UARTCC_2    (*((volatile uint32_t *)0x4000EFC8))

// Configs for UART 3
#define UARTDR_3    (*((volatile uint32_t *)0x4000F000))
#define UARTFR_3    (*((volatile uint32_t *)0x4000F018))
#define UARTCTL_3   (*((volatile uint32_t *)0x4000F030))
#define UARTIBRD_3  (*((volatile uint32_t *)0x4000F024))
#define UARTFBRD_3  (*((volatile uint32_t *)0x4000F028))
#define UARTLCRH_3  (*((volatile uint32_t *)0x4000F02C))
#define UARTCC_3    (*((volatile uint32_t *)0x4000FFC8))

// Nvic registers
#define NVIC_EN2 (*((volatile uint32_t *)0xE000E108))
#define NVIC_EN1 (*((volatile uint32_t *)0xE000E104))
#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100))


// Masks
#define SS3_INTR 0x8  // SS3 Inturrupt mask

// Number of ticks in second
#define HZ 16000000

// Switch states
#define SW1 0x1
#define SW2 0x2

// number of chars per uart msg
#define UARTMSG 7

// Handler codes to support compatibility with CCS
void ADC0SS3_Handler(void);
void ADC0SS3_Handler_UART(void);
void Button_Handler(void);

// Code for different tasks
void potentiometer();
void temperature();

// Reads temperature to uart
void uart_send_recieve();

// Sends a character from uart
void send_char(char ch);

// Recieves a character from uart2
char recieve_char();

#endif //__HEADER3_H__
