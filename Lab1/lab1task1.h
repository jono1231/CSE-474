/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 10/10/2023
 * This is a header file that defines all needed registers
 * and macros to operate on board switches and led lights.
 */

#ifndef __HEADER1_H__

#define __HEADER1_H__

#define BASEREG  (*((volatile uint32_t *)0x400FE000))
#define GPIOPUR  (*((volatile uint32_t *)0x400FE510))
#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

// LED Configurations for port F
#define GPIODIR_F  (*((volatile uint32_t *)0x4005D400))
#define GPIODEN_F  (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))

// LED configurations for port N
#define GPIODIR_N  (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N  (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

// Creates a delay
void wait(int ticks);

#endif //__HEADER1_H__
