
uint8_t i, flag, counter, idx;
char c, Lat[12], Lon[12];

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
