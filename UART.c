#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Functions.h"


void UART7_Init (void)
{

    SYSCTL_RCGCUART_R |= 0x80;
    SYSCTL_RCGCGPIO_R |= 0x10;
    
    UART7_CTL_R &= ~0x01;
    UART7_IBRD_R = 104; //BR = 9600
    UART7_FBRD_R = 11;
    UART7_LCRH_R = 0x70; //8-bit length , no parity, 1 stop bit, fifo enable
    UART7_CTL_R |= 0x301;
    
    GPIO_PORTE_AFSEL_R |= 0x03;
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R &~ 0xFF)| (0x11);
    GPIO_PORTE_DEN_R |= 0x03;
    
}

uint8_t UART7_Available (void)
{
    return ((UART7_FR_R & 0x10) == 0x10) ? 0 : 1; //flag values and RxFE bits
}
uint8_t UART7_Read (void)
{
    while (UART7_Available() != 1); //zero means that fifo empty, no data available to read
    return (char)(UART7_DR_R & 0xFF);
}

//void UART7_Write (uint8_t data)
//{
//    while ((UART7_FR_R & 0x20) != 0); //FIFO full?
//    UART7_DR_R = data;
//}
