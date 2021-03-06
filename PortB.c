#include <stdint.h>
#include "tm4c123gh6pm.h"

void PortB_Init (void)
{ 
	SYSCTL_RCGCGPIO_R |= 0x02;
	while (!(SYSCTL_PRGPIO_R & 0x02));
	GPIO_PORTB_AMSEL_R = 0x00;
	GPIO_PORTB_PCTL_R = 0x00000000;
	GPIO_PORTB_AFSEL_R = 0x00;
	GPIO_PORTB_DIR_R = 0xFF;
	GPIO_PORTB_DEN_R = 0xFF;
	GPIO_PORTB_DATA_R = 0x00;
}

uint8_t number;
void WriteData_B (uint16_t distance)
{
   if (distance >= 100){
		 distance %= 100;
	 }
	 number = (distance / 10) << 4;
	 number |= distance % 10;
	 GPIO_PORTB_DATA_R = number; 
}
