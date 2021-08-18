
void PortA_Init (void);
void WriteData_A (uint16_t distance);

void PortB_Init (void);
void WriteData_B (uint16_t distance);

void PortF_Init (void);
void RLed (void); 
void BLed (void);
uint8_t ReadSW(void);

void UART0_Init (void);
void UART7_Init (void);
uint8_t UART7_Available (void);
char UART7_Read (void);

float parseLatLon (char * gps);
float getX (float latf, float lonf);
float getY (float latf, float lonf);
