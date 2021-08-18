#include <stdint.h>
#include "tm4c123gh6pm.h"

void PortF_Init (void)
{ 
	SYSCTL_RCGCGPIO_R |= 0x20;
	while((SYSCTL_PRGPIO_R &0x20)==0);
	GPIO_PORTF_AMSEL_R &=~ 0x16;
	GPIO_PORTF_PCTL_R &=0xFFF0F00F;
	GPIO_PORTF_AFSEL_R &=~ 0x16;
	GPIO_PORTF_DIR_R = 0x0E;
	GPIO_PORTF_DEN_R |= 0x16;
	GPIO_PORTF_PUR_R = 0x10;
	GPIO_PORTF_DATA_R &=~ 0x06;
}
void RLed (void) 
{
  GPIO_PORTF_DATA_R = 0x02;
}

void BLed (void) 
{
  GPIO_PORTF_DATA_R = 0x04;
}

uint8_t ReadSW(void)
{
  return(GPIO_PORTF_DATA_R & 0x10);
}
