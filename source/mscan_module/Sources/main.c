#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "mc9s12c32.h"
#include "bit_fiddling.h"
#include "mscan.h"



void 
MSCAN_Init(void){
  // assert CANE - MSCAN module turn on
  SET_BITS(CANCTL1, CANCTL1_CANE_MASK);
  // request for MSCAN init mode
  SET_BITS(CANCTL0, CANCTL0_INITRQ_MASK);

  // wait for MSCAN module to enter init mode, checking for acknowledgement flag
  while((BIT_IS_CLR(CANCTL1, CANCTL1_INITAK_MASK)));

  // successfully entered init mode
  // configuring registers to control MSCAN operation

  CANCTL1 = CANCTL1_INIT
  CANBTR0 = CANBTR0_INIT
  CANBTR1 = CANBTR1_INIT
}


void CANInit(void)
{
  CANCTL0 = 0x01; /* Enter Initialization Mode */
  while (! (CANCTL1&0x01)) {}; /* Wait for Initialization Mode
                                  acknowledge (INITRQ bit = 1) */
  CANCTL1 = 0xC0;    // Enable CAN and 
  CANBTR0 = 0x07;    // Set prescaler K= 8
  CANBTR1 = 0x23;    // Set N= 8, TSEG1 = 4, TSEG2 = 3, TQ = 1
 
  
  /* Acceptance Filters  */

  CANIDAC = 0x10;                   // Set four 16-bit Filters
  
  CANIDAR0 = ACC_CODE_ID100_HIGH;   //|\    16-bit Filter 0
  CANIDMR0 = MASK_CODE_ST_ID_HIGH;  //| \__ Accepts Standard Data Frame Msg
  CANIDAR1 = ACC_CODE_ID100_LOW;    //| /   with ID 0x100
  CANIDMR1 = MASK_CODE_ST_ID_LOW;   //|/

  CANIDAR2 = 0x00;                  //|\    16-bit Filter 1
  CANIDMR2 = MASK_CODE_ST_ID_HIGH;  //| \__ Accepts Standard Data Frame Msg
  CANIDAR3 = 0x00;                  //| /   with ID 0x100
  CANIDMR3 = MASK_CODE_ST_ID_LOW;   //|/

  CANIDAR4 = 0x00;                  //|\    16-bit Filter 2
  CANIDMR4 = MASK_CODE_ST_ID_HIGH;  //| \__ Accepts Standard Data Frame Msg
  CANIDAR5 = 0x00;                  //| /   with ID 0x100
  CANIDMR5 = MASK_CODE_ST_ID_LOW;   //|/
  
  
  CANIDAR6 = 0x00;                  //|\    16-bit Filter 3
  CANIDMR6 = MASK_CODE_ST_ID_HIGH;  //| \__ Accepts Standard Data Frame Msg
  CANIDAR7 = 0x00;                  //| /   with ID 0x100
  CANIDMR7 = MASK_CODE_ST_ID_LOW;   //|/    
  
  CANCTL0 = 0x00;    // Exit Init Mode
  while(CANCTL1&0x01);  // Waiting for normal mode
}



void main()
{
  unsigned char errorflag = NO_ERR;
  unsigned char txbuff[] = "ABCDEFGH";
  
  CANInit();
  while(!(CANCTL0&0x10)); 
  
  //SET_BITS(CANRFLG,0xC3);
  //SET_BITS(CANRIER,0x01);
  CANRFLG = 0xC3;
  CANRIER = 0x01; 
  
  EnableInterrupts;
  

  errorflag = CANSendFrame(ST_ID_100, 0x00, (sizeof(txbuff)-1), txbuff);
  delay(1000);  
  for(;;)
  {
   if(CANRFLG&0x01){
    
      SET_BITS(CANRFLG,0x01); // Clear RXF, and check for new messages
   }
  }          
}

unsigned char CANSendFrame(unsigned long id, unsigned char priority, unsigned char length, unsigned char *txdata)
{ 
  unsigned char txbuffer;
  int index = 0;
   
  if (!CANTFLG)
  {
    return ERR_BUFFER_FULL;
  }/* Is Transmit Buffer full?? */
    
  
  CANTBSEL = CANTFLG; /* Select lowest empty buffer */
  txbuffer = CANTBSEL; /* Backup selected buffer */
  
  /* Load Id to IDR Register */
  *((unsigned long *) ((unsigned long)(&CANTXIDR0))) = id;
  
  for (index=0; index<length; index++) {
    *(&CANTXDSR0 + index) = txdata[index]; // Load data to Tx buffer
                                            // Data Segment Registers
  }
  
  CANTXDLR = length; // Set Data Length Code 
  CANTXTBPR = priority; // Set Priority 
  CANTFLG = txbuffer; // Start transmission 
  
  while ( (CANTFLG & txbuffer) != txbuffer); // Wait for Transmission completion
  
  return 0;
}


void delay(int milliseconds)  // Delay function
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

interrupt 38 void CANRxISR(void)
{
  unsigned char length, index;
  unsigned char rxdata[8];
  
  length = (CANRXDLR&0x0F);
  for (index=0; index<length; index++) 
  {
    rxdata[index] = *(&CANRXDSR0 + index); // Get received data
  }

  SET_BITS(CANRFLG,0x01); // Clear RXF, and check for new messages
  //CANRFLG =0x01;
}