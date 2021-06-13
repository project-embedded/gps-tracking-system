#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Functions.h"

void PortA_Init (void)
{ 
	SYSCTL_RCGCGPIO_R |= 0x01;
	while (!(SYSCTL_PRGPIO_R & 0x01));
	GPIO_PORTA_AMSEL_R &= ~ 0x3C;
	GPIO_PORTA_PCTL_R &= 0xFF0000FF;
	GPIO_PORTA_AFSEL_R &= ~ 0x3C;
	GPIO_PORTA_DIR_R |= 0x3C;
	GPIO_PORTA_DEN_R |= 0x3C;
	GPIO_PORTA_DATA_R &= ~ 0x3C;
}

void WriteData_A (uint16_t distance){
   distance /= 100;
	 GPIO_PORTA_DATA_R = distance << 2;
}
