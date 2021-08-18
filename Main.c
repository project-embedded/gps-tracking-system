#include <math.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Functions.h"

uint8_t i, flag, counter, idx, on=1;
uint16_t dist = 0;
char c, Lat[14], Lon[14];
float x1, y1, x2, y2, latValue, lonValue;

void getLatLon(void);
void getArray(char *L);

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
				if(counter == 2){
					c = UART7_Read();
					if(c == 'A') flag = 1;
				}
				if(counter == 3 && flag) getArray(Lat);
			 	if(counter == 5 && flag) getArray(Lon);
    		} }
} }


void getArray(char *L)
{
	for(idx=0; idx<14; idx++){
		c = UART7_Read();
		if(c != ',') 
			L[idx] = c;
		else{
			L[idx] = '\0';
			break;
		}
	}
}
