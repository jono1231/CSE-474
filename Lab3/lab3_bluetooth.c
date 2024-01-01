/*
 * Jonathan Wang, 2236141
 * Timothy Yi, 2065634
 * 11/17/2023
 * This code initializes a HC-06 bluetooth module
 * to read and send data from a HC-06 Bluetooth module
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lab3.h"

/**
 * main.c
 */
int main(void)
{
  UART_Init();

  while(1) {
     uart_send_recieve();
  }
}

void send_char(char ch) {
  // While waiting for data to be transmitted, do nothing
  while(UARTFR_2 & 0x8); 
  // Write the next data bit
  UARTDR_2 = ch;
}

char recieve_char() {
  char data;
  // While haven't recieved anything yet, wait
  while (UARTFR_2 & 0x10);
  // Copy data from register and return it
  data = UARTDR_2;
  return data;
}

void uart_send_recieve() {
  // Easier to use
  send_char(recieve_char());
}


void UART_Init(void) {
  int delay = 0;
  RCGCUART |= 0x4; // UART module 2
  RCGCGPIO |= 0x1; // Port A
  delay++;
  delay++;

  // Disable UARTS
  UARTCTL_2  = 0;

  // Init UARTS
  UARTIBRD_2 = 104;
  UARTFBRD_2 = 11;
  UARTCC_2   = 0x0;
  UARTLCRH_2 = 0x60;

  // Enable UART
  UARTCTL_2  = 0x301;

  // Init GPIO port A6/A7 for UART reading/writing
  GPIODEN_A   = 0x30;
  GPIOAFSEL_A = 0x30;
  GPIOAMSEL_A = 0x00;
  // Config PA6 and PA7 pins
  GPIOPCTRL_A = 0x11000000;
}

