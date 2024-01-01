/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 10/26/2023
 * This is a header file that defines all needed registers
 * and macros to make a traffic light built on port L (Lab 1)
 * This also enables timer inputs for timer 0 and timer 1
 */

#ifndef __HEADER2_H__

#define __HEADER2_H__

// Base registers
#define BASEREG  (*((volatile uint32_t *)0x400FE000))
#define GPIOPUR  (*((volatile uint32_t *)0x400FE510))
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))

// LED Configurations for port F
#define GPIODIR_F  (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F  (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

// LED configurations for port N
#define GPIODIR_N  (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N  (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

// Port L (external) configs
#define GPIOAMSEL_L (*((volatile uint32_t *)0x40062528))
#define GPIODIR_L   (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L   (*((volatile uint32_t *)0x4006251C))
#define GPIOAFSEL_L (*((volatile uint32_t *)0x40062420))
#define GPIODATA_L  (*((volatile uint32_t *)0x400623FC))
#define GPIOPDR_L   (*((volatile uint32_t *)0x40062514))

// Switch configurations for port J - note PUR isntead of PDR
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

// Timer configs for timer 0
// Timer 0 - red/green/warn state timer
#define GPTMCTL_0   (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0   (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0  (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_0   (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0   (*((volatile uint32_t *)0x40030024))
#define GPTMIMR_0   (*((volatile uint32_t *)0x40030018))

// Timer configs for timer 1
// Timer 1 - on/off state press
#define GPTMCTL_1   (*((volatile uint32_t *)0x4003100C))
#define GPTMCFG_1   (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_1  (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_1 (*((volatile uint32_t *)0x40031028))
#define GPTMRIS_1   (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_1   (*((volatile uint32_t *)0x40031024))

// Enable interrupts
#define NVIC_EN1 (*((volatile uint32_t *)0xE000E104))
#define NVIC_EN0 (*((volatile uint32_t *)0xE000E100))
#define NVIC_EN2 (*((volatile uint32_t *)0xE000E108))

// Switch states
#define SW1 0x1
#define SW2 0x2

// Light colors
#define OFF 0x0
#define RED 0x4
#define YLW 0x8
#define GRN 0x10

// Number of seconds to press timer for
#define SECONDS 2
// Number of seconds to hold light states
#define SW_SECS 5

// Number of ticks in second
#define HZ 16000000

// Initializes the board, sets registers and starting state
void init();

// Starts the FSM
void begin();

// Initialize the timer
void timer_init();

// Waits for x time
void wait(int time);

// Sets LED lights configured to the correct macro defined above in header files
void set_light(int color);

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


#endif //__HEADER2_H__
