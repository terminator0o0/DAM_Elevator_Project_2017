#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "mc9s12c32.h"
#include "mscan.h"
#include "bit_fiddling.h"

unsigned long myIdBfr = 0;

void
MSCAN_Init(void) {
  // assert CANE - MSCAN module turn on
  SET_BITS(CANCTL1, CANCTL1_CANE_MASK);
  // request for MSCAN init mode
  SET_BITS(CANCTL0, CANCTL0_INITRQ_MASK);

  // wait for MSCAN module to enter init mode, checking for acknowledgement flag
  while ((BIT_IS_CLR(CANCTL1, CANCTL1_INITAK_MASK)));

  // successfully entered init mode
  // configuring registers to control MSCAN operation

  CANCTL1 = CANCTL1_INIT;
  CANBTR0 = CANBTR0_INIT;
  CANBTR1 = CANBTR1_INIT;

  // exit init mode and enter normal operation
  CLR_BITS(CANCTL0, CANCTL0_INITRQ_MASK);
  // wait for module to exit init mode
  while ((BIT_IS_SET(CANCTL1, CANCTL1_INITAK_MASK)));
}

void 
MSCAN_ListenForMsg( unsigned long id, unsigned char rtr ) {
	// local copy of 32 bit message ID - msg ID built here and then copied to acceptance register
unsigned long *idaRegPtr;

// Force module into init mode via sleep mode (to ensure xmit/rcv complete
SET_BITS( CANCTL0, CANCTL0_SLPRQ_MASK );		// put module into sleep mode
while( BIT_IS_CLR( CANCTL1, CANCTL1_SLPAK_MASK ) );	// wait for module to fall asleep
SET_BITS( CANCTL0, CANCTL0_INITRQ_MASK );		// put module into init mode
while( BIT_IS_CLR( CANCTL1, CANCTL1_INITAK_MASK ) );	// wait for module to enter init mode

// now in init mode
// set up acceptance filter registers

CANIDAC = 0;	// setup for 2 32-bit filters - all bits significant


// filter 0 - standard identifier
myIdBfr = (id & 0x07ff) << (32-11) 	
          | (((unsigned long)rtr & 0x01) << (32 - 11 - 1));

idaRegPtr = (unsigned long *)(&CANIDAR0);
*idaRegPtr = myIdBfr;

// all done - leave init mode and enter normal mode
CLR_BITS( CANCTL0, CANCTL0_INITRQ_MASK );		// turn off the init mode request flag
while( BIT_IS_SET( CANCTL1, CANCTL1_INITAK_MASK ) );	// wait for module to exit init mode
CLR_BITS( CANCTL0, CANCTL0_SLPRQ_MASK );		// turn off sleep mode flag
while( BIT_IS_SET( CANCTL1, CANCTL1_SLPAK_MASK ) );	// wait for module to wake up
	
}

int MSCAN_GotMsg( void ) {

return ( BIT_IS_SET( CANRFLG, CANRFLG_RXF_MASK ) );
	
} // MSCAN_GotMsg()


void MSCAN_Getd( CANmsg_t * thisMsg ) {

int i;
unsigned char * dataPtr;

thisMsg->id = *(unsigned long *)(&CANRXIDR0);
thisMsg->id >>= 21;

thisMsg->length = CANRXDLR;
dataPtr = (unsigned char *)(&CANRXDSR0);

for (i = 0; i < thisMsg->length; i++)
	thisMsg->rxdata[i] = *dataPtr++;
	
SET_BITS( CANRFLG, CANRFLG_RXF_MASK );
	
} // MSCAN_Getd()

int MSCAN_Putd( unsigned long id, unsigned char * data, unsigned char length, unsigned char priority, unsigned char rtr) {

unsigned char myBfrFlg;		// copy of CANTBSEL with selected tx register set
int retCode;		// return value from this function - 0 - success, -1 = failure
int i;			// loop counter for copying tx data to outptu buffer
unsigned long myIdBfr = 0;	// local copy of 32 bit message ID - msg ID built here and then copied to outpu buffer
unsigned char *txDataRegPtr;	// treating output data registers as array of 8 bytes - using this pointer to access
unsigned long *txIdRegPtr;	// treating 4 bytes of message ID register as single 32-bit unsigned value - using this pointer to access


// acquire a transmit register - this function will return error if no buffers available
CANTBSEL = CANTFLG;	// get copy of flag register with available buffers and write to CANTBSEL to acquire one
myBfrFlg = CANTBSEL;	// if a buffer was available, CANTBSEL will indicate it with a set bit - save in myBfrFlg to use later to mark buffer for xmit

if (myBfrFlg != 0) {    // if myBfrFlg = 0, no buffer available, else buffer was acquired and we can do the write
// success - buffer acquired - fill with data

	// build 32 bit identifier and copy to transmit data ID registers
// !!! must be a cleaner way to build ID - maybe use same 11-bit mask for bot and do after shift
  
	// case 2 - standard identifier
	myIdBfr = ((id & 0x07ff) << (32-11)) 
			| (((unsigned long)rtr & 0x01) << (32 - 11 - 1));


  txIdRegPtr = (unsigned long *)(&CANTXIDR0);
  *txIdRegPtr = myIdBfr;

		
	// copy data to transmit data buffer registers
	txDataRegPtr = &CANTXDSR0;
	for (i = 0; i < length; i++)
		*txDataRegPtr++ = *data++;
		
	// load the data buffer size into tx size register
	CANTXDLR = length;
	
	// load the local message priority into tx local priority register
	CANTXTBPR = priority;

	// mark buffer for transmission		
	CANTFLG = myBfrFlg;
	
	retCode = 0;
	
} // end success
else {
// failure - no buffers available

	retCode = -1;
	
} // end fail


return( retCode );

	
}