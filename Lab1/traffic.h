/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 10/18/2023
 * This is a header file that defines all needed registers
 * and macros to make a traffic light built on port L (Lab 1)
 */

#ifndef __HEADER1_H__

#define __HEADER1_H__

// Possible states for the finite state machine
enum states{off_off, off_temp, on_temp, on_red, on_warn, on_green} curState;

// Base registers
#define BASEREG  (*((volatile uint32_t *)0x400FE000))
#define GPIOPUR  (*((volatile uint32_t *)0x400FE510))
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

// Task 2 LED Configs
#define GPIOAMSEL_L (*((volatile uint32_t *)0x40062528))
#define GPIODIR_L   (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L   (*((volatile uint32_t *)0x4006251C))
#define GPIOAFSEL_L (*((volatile uint32_t *)0x40062420))
#define GPIODATA_L  (*((volatile uint32_t *)0x400623FC))
#define GPIOPDR_L   (*((volatile uint32_t *)0x40062514))

// Switch states
#define SW1 0x1
#define SW2 0x2

// Light colors
#define OFF 0x0
#define RED 0x4
#define YLW 0x8
#define GRN 0x10

// Sets LED lights configured to the correct macro defined above in header files
void set_light(int color);

// Gets the input of the switch according to macro defined in header
unsigned long switch_input(int iswitch);

// Initializes the board, sets registers and starting state
void init();

// Starts the FSM
void begin();

// Waits for x time
void wait(int time);

// Waits for x time, returns 1 if sw1 is pressed
// If we aren't yellow and SW2 is pressed, returns 2
// Returns 0 (false) otherwise.
int wait_on(int time, int isYellow);

#endif //__HEADER1_H__
