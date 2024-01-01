/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 11/30/2023
 * This is a header file that defines all needed registers
 * and macros to:
 * read inputs from both a potentiometer 
 * read data from on-board temperature
 * support UART and bluetooth interfacing
 * Run a timed traffic light system over an LCD screen
 */

#ifndef __HEADER4_H__

#define __HEADER4_H__

#define BASEREG    (*((volatile uint32_t *)0x400FE000))
#define GPIOPUR    (*((volatile uint32_t *)0x400FE510))
#define RCGCGPIO   (*((volatile uint32_t *)0x400FE608))
#define RCGCADC    (*((volatile uint32_t *)0x400FE638))
#define ALTCLKCFG  (*((volatile uint32_t *)0x400FE138))
#define RCGCTIMER  (*((volatile uint32_t *)0x400FE604))
#define RCGCUART   (*((volatile uint32_t *)0x400FE618))

// LED Configurations for port F
#define GPIODIR_F  (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F  (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

// LED configurations for port N
#define GPIODIR_N  (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N  (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))
#define GPIOAFSEL_N (*((volatile uint32_t *)0x40064420))

// Configs for Analog Port E
#define GPIOAFSEL_E  (*((volatile uint32_t *)0x4005C420))
#define GPIODEN_E    (*((volatile uint32_t *)0x4005C51C))
#define GPIOAMSEL_E  (*((volatile uint32_t *)0x4005C528))

// Port D
#define GPIODIR_D (*((volatile uint32_t *)0x4005B400))
#define GPIOAFSEL_D (*((volatile uint32_t *)0x4005B420))
#define GPIODEN_D (*((volatile uint32_t *)0x4005B51C))

// Port K
#define GPIODIR_K (*((volatile uint32_t *)0x40061400))
#define GPIOAFSEL_K (*((volatile uint32_t *)0x40061420))
#define GPIODEN_K (*((volatile uint32_t *)0x4006151C))

// Port M
#define GPIODIR_M (*((volatile uint32_t *)0x40063400))
#define GPIOAFSEL_M (*((volatile uint32_t *)0x40063420))
#define GPIODEN_M (*((volatile uint32_t *)0x4006351C))

// Port P
#define GPIODIR_P (*((volatile uint32_t *)0x40065400))
#define GPIOAFSEL_P (*((volatile uint32_t *)0x40065420))
#define GPIODEN_P (*((volatile uint32_t *)0x4006551C))

// Port Q
#define GPIODIR_Q (*((volatile uint32_t *)0x40066400))
#define GPIOAFSEL_Q (*((volatile uint32_t *)0x40066420))
#define GPIODEN_Q (*((volatile uint32_t *)0x4006651C))


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
#define ADCEMUX_0     (*((volatile uint32_t *)0x40038014))
#define ADCSSCTL3_0   (*((volatile uint32_t *)0x400380A4))
#define ADCIM_0       (*((volatile uint32_t *)0x40038008))
#define ADCISC_0      (*((volatile uint32_t *)0x4003800C))
#define ADCSSFIFO3_0  (*((volatile uint32_t *)0x400380A8))
#define ADCSSEMUX3_0  (*((volatile uint32_t *)0x400380B8))
#define ADCPSSI_0     (*((volatile uint32_t *)0x40038028))
#define ADCCC_0       (*((volatile uint32_t *)0x40038FC8))

// Timer configs for timer 0 - 0a
#define GPTMCTL_0    (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0    (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0   (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0  (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_0    (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0    (*((volatile uint32_t *)0x40030024))
#define GPTMIMR_0    (*((volatile uint32_t *)0x40030018))
#define GPTMADCEV_0  (*((volatile uint32_t *)0x40030070))

// Timer configs for timer 1
// Timer 1 - on/off state press
#define GPTMCTL_1   (*((volatile uint32_t *)0x4003100C))
#define GPTMCFG_1   (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_1  (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_1 (*((volatile uint32_t *)0x40031028))
#define GPTMRIS_1   (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_1   (*((volatile uint32_t *)0x40031024))

// Nvic registers
#define NVIC_EN2 (*((volatile uint32_t *)0xE000E108))
#define NVIC_EN1 (*((volatile uint32_t *)0xE000E104))
#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100))

// UART 0 configs
#define GPIOAFSEL_A (*((volatile uint32_t *)0x40058420))
#define GPIOPCTL_A (*((volatile uint32_t *)0x4005852C))
#define UARTCTL_0 (*((volatile uint32_t *)0x4000C030))
#define UARTIBRD_0 (*((volatile uint32_t *)0x4000C024))
#define UARTFBRD_0 (*((volatile uint32_t *)0x4000C028))
#define UARTLCRH_0 (*((volatile uint32_t *)0x4000C02C))   
#define UARTCC_0 (*((volatile uint32_t *)0x4000CFC8)) 
#define UARTDR_0 (*((volatile uint32_t *)0x4000C000))   
#define UARTFR_0 (*((volatile uint32_t *)0x4000C018))
#define GPIODEN_A (*((volatile uint32_t *)0x4005851C))
#define GPIOAMSEL_A (*((volatile uint32_t *)0x40058528))

// UART 2 configs
#define UARTCTL_2 (*((volatile uint32_t *)0x4000E030))
#define UARTIBRD_2 (*((volatile uint32_t *)0x4000E024))
#define UARTFBRD_2 (*((volatile uint32_t *)0x4000E028))
#define UARTLCRH_2 (*((volatile uint32_t *)0x4000E02C))   
#define UARTCC_2 (*((volatile uint32_t *)0x4000EFC8)) 
#define UARTDR_2 (*((volatile uint32_t *)0x4000E000))   
#define UARTFR_2 (*((volatile uint32_t *)0x4000E018))
   
// Masks
#define SS3_INTR 0x8  // SS3 Inturrupt mask

// Switch states
#define SW1 0x1
#define SW2 0x2

// Number of seconds to press timer for
#define SECONDS 2
// Number of seconds to hold light states
#define SW_SECS 5

// Number of ticks in second
// 60 MHZ so this number
#define HZ 60000000

// Code for different tasks
void potentiometer();
void temperature();

// Button press checks
int start_stop_pressed();
int pedestrian_pressed();

// Starts the FSM
void begin();

// Initialize the timer
void timer_init();

// Initialize the display drawing
void display_init();

// Waits for x time
void wait(int time);

// Gets the input of the switch according to macro defined in header
unsigned long switch_input(int iswitch);

// Checks timer 0's state
int timer0();

// Checks timer 0's state, and if a switch is pressed or not
int timer0_press(int sw, int sec);

// Checks timer 1's state
int timer1();

// Checks timer 0's state, and if a switch is pressed or not
int timer1_press(int sw, int sec);

// Reset timer 0's state, makes it count down from x seconds
void reset_timer0(int sec);

// Same as above, but for timer 1
void reset_timer1(int sec);

// Clears timer0's states
void clear_timer0();

// Clears timer1's states
void clear_timer1();

#endif //__HEADER4_H__
