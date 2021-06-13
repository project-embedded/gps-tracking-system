#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include "Functions.h"

uint8_t i, flag, counter, idx;
uint16_t dist = 0, on=1;
char c, Lat[12], Lon[12];
float x1, y1, x2, y2, latValue, lonValue;

void getLatLon(void){
	while(1){
		while(UART7_Read() != '$');
		if(flag) break;
		for(i=0; i<3; i++) c = UART7_Read();
		if(c == 'R'){
			counter = 0;
			for(i=1; i<=5; i++){
				while(UART7_Read() != ',');
				counter++;
		    }
	    }
	}
}

uint16_t calcDist (float x1, float y1, float x2, float y2)
{
	return (uint16_t)(sqrt( pow(x1-x2, 2) + pow(y1-y2, 2) ) );
}


int main()
{
  PortA_Init ();
  PortB_Init ();	
  PortF_Init ();
  UART0_Init ();
  UART7_Init ();
	
  getLatLon();
  latValue = parseLatLon(Lat);
  lonValue = parseLatLon(Lon);
  x1 = getX (latValue, lonValue);
  y1 = getY (latValue, lonValue);
	
  while(ReadSW() != 0x00)
  {
    flag = 0;
    getLatLon();
    latValue = parseLatLon(Lat);
    lonValue = parseLatLon(Lon);
    x2 = getX (latValue, lonValue);
    y2 = getY (latValue, lonValue);
	  
    dist += calcDist(x1, y1, x2, y2);
    WriteData_B (dist);
    if (dist >= 100)
    {
	    WriteData_A (dist);
	    while(on){
		  RLed();
		  on=0;
	    } 
    }
    x1=x2, y1=y2;
  }
  BLed();
  return 0;
}
