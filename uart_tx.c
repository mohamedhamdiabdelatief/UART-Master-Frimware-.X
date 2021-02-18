/*
* File Name: UART Firmware For(Transmitter / Master) TX
* Author:mohamed hamdi abdulatief
* please visit my youtube channel:https://www.youtube.com/channel/UCzt_0MFbJiT93KSR74pW6Jw
*/
#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000
#define Baud 115200
//--------------------------------------------
// Functions Declarations
void UART_TX_Init(void);
void UART_Write(uint8_t);
void UART_Write_String(char *);
//--------------------------------------------
void main(void)
{
  UART_TX_Init(); // Initialize The UART in Master Mode  115200bps

  UART_Write_String("AT");
  __delay_ms(1000);
  UART_Write_String("AT+CWQAP");
  __delay_ms(1000);
  UART_Write_String("AT+RST");
  __delay_ms(1000);

  //------------------------------------------
  while (1)
  {
  }
  return;
}
//--------------------------------------------
// Functions Definitions to make ability to change baud rate
void UART_TX_Init(void)
{
  uint16_t x;
  x = (_XTAL_FREQ - Baud * 64) / (Baud * 64); // Low Baud Rate
  if (x > 255)
  {
    x = (_XTAL_FREQ - Baud * 16) / (Baud * 16); // High Baud Rate
    BRGH = 1;
  }
  if (x <= 255)
  {
    SPBRG = x; //Writing SPBRG Register
  }
  //--[ Enable The Ascynchronous Serial Port ]--
  SYNC = 0;
  SPEN = 1;
  // Set The RX-TX Pins to be in UART mode (not i/o)
  TRISC6 = 1; // As stated in the datasheet
  TRISC7 = 1; // As stated in the datasheet
  TXEN = 1;   // Enable UART Transmission
}
void UART_Write(uint8_t data) //function to write byte in uart Tx
{
  while (!TRMT)
    ;
  TXREG = data;
}
void UART_Write_String(char *text)
{
  uint16_t i;
  for (i = 0; text[i] != '\0'; i++)
    UART_Write(text[i]);
}