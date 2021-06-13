#include <stdint.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include "Functions.h"

uint8_t digitCount;
uint16_t I;
float X, Y, num, F, P;

float parseLatLon (char * gps)
{
	P = 0;
	digitCount = ( gps[4] == '.' ? 2 : 3); 
	num = atof(gps);
	
  if ( digitCount == 2 ){
	I = num / 100;
  F = num - I*100;
	}
	 
  else{
	I = num / 1000;
  F = num - I*1000;
	}
	
	P = I + F/ 60;
	return P; 
}
