#include <stdio.h>
#include <stdlib.h>
#include <hidef.h>           /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "mc9s12c32.h"
#include "mscan.h"
#include "floor_controller.h"
#include "bit_fiddling.h"
#include "utils.h"

/*#define FLOOR_CONTROLLER_2


#ifdef FLOOR_CONTROLLER_1
#define PTAD_AS_GPIO_MASK 0x01
#define READ_CAR_FLOOR_REQ (PTAD & 0x01)
#define DDRB_OUTPUT 0x01
#endif

#ifdef  FLOOR_CONTROLLER_2
#define PTAD_AS_GPIO_MASK   0x03
#define READ_CAR_FLOOR_REQ (PTAD & 0x03)
#define FLOOR_REQ_LED_UP    FLOOR_REQ_LED_1     
#define FLOOR_REQ_LED_DOWN  FLOOR_REQ_LED_2
#endif

#ifdef FLOOR_CONTROLLER_3
#define PTAD_AS_GPIO_MASK 0x01
#define READ_CAR_FLOOR_REQ (PTAD & 0x01)
#define DDRB_OUTPUT 0x01
#endif*/

int retCode = 1;
unsigned char floorSelected = FALSE;
CANmsg_t rxMsg;
volatile unsigned char currentFloor;
unsigned char txdata[8];
//volatile unsigned char data[8];
volatile unsigned char doorState;

// Delay_ms()
// wait for specified # of ms, then return
// uses channel 0 of the timer module in polling mode
void 
Delay_ms( word delayTime ) 
{
   	
    // initialize the timer module - set prescaler and enable
    SET_TCNT_PRESCALE( TCNT_PRESCALE_64 );
    TSCR1 = TSCR1_INIT;

 	// configure timer channel 0 as OC, no output pin action, prime for 1ms initial delay
    MAKE_CHNL_OC( 0 );
    SET_OC_ACTION( 0, OC_OFF );  	
    TC0 = TCNT + OC_1MS_DELAY;
    
	
	// loop for the specified # of ms
	while (delayTime--) {
		while( BIT_IS_CLR( TFLG1, TFLG1_C0F_MASK ) );
        TC0 += OC_1MS_DELAY;                         // rearm the OC register for the next delay - clears TFLG1
   	}

} // Delay_ms()

/*
/ Function: Init_Car_Controller()
/ Input: Void
/ Output: Void
/ Purpose: Initializes the DDR and ports required to enable buttons and LEDs associated with the 
/          car controller.
*/
/*void
Init_CAN_Msg(CANmsg_t msgPtr)
{
  int index = 0;
  msgPtr->id = CC_CAN_ID;
  msgPtr->length = 8;
  msgPtr->rtr = 0;
  msgPtr->priority = 0;
  msgPtr->txdata = 0;
} */

/*
/ Function: Init_Car_Controller()
/ Input: Void
/ Output: Void
/ Purpose: Initializes the DDR and ports required to enable buttons and LEDs associated with the 
/          car controller.
*/
void 
Init_Floor_Controller()
{
  // configure button DDR
  // configure PTAD to PIM module/as a GPIO
  SET_BITS(ATDDIEN, PTAD_AS_GPIO_MASK);
  //configure digital input for limit switches  
  DDRAD   = DDRAD_INIT;
  
  // configure door state DDR to input
  CLR_BITS(DOOR_STATE_DDR,DDRJ_INIT);   
   
  // configure floor request LED port data direction to output
  SET_BITS(LED_PORT_DDR, DOOR_LEDS_ON);
  // turn on both LEDs
  SET_BITS(LED_PORT,DOOR_LEDS_ON);
  Delay_ms(1000);
  // turn off both LEDs
  CLR_BITS(LED_PORT, DOOR_LEDS_OFF);
  
  // configure floor request LEDs DDR to output
  SET_BITS(FLOOR_REQ_LEDS_DDR, DDRB_OUTPUT);
  // turn on red LEDs for 1 second
  SET_BITS(FLOOR_REQ_LEDS_PORT, FLOOR_REQ_LEDS_ON);
  Delay_ms(1000);
  // turn off red LEDs
  CLR_BITS(FLOOR_REQ_LEDS_PORT, FLOOR_REQ_LEDS_OFF);
  
  // configure floor status LED DDR to output
  SET_BITS(FLOOR_STATUS_LEDS_DDR, DDRA_OUTPUT);
  // turn on green LEDs for 1 second
  SET_BITS(FLOOR_STATUS_LEDS_PORT, FLOOR_STATUS_LEDS_ON);
  Delay_ms(1000);
  // turn off green LEDs
  CLR_BITS(FLOOR_STATUS_LEDS_PORT, FLOOR_STATUS_LEDS_OFF);
 
  SET_BITS(LED_PORT,LED_1_ON); 
}

void 
main()
{
  Init_Floor_Controller();
  MSCAN_Init();
  MSCAN_ListenForMsg(EC_CAN_ID, 0);
  //txdata[0] |= 0x00;
  doorState = OPEN;

  for(;;)
  {  
    // poll for valid message flag
    while(!MSCAN_GotMsg());
    // if valid message, read message
    MSCAN_Getd(&rxMsg);
    
    // check for message from elevator controller 
    if(rxMsg.id == EC_CAN_ID)
    {
      // reset id for next message
      rxMsg.id = 0;
      
      // copy data to local variable
      currentFloor = (rxMsg.rxdata[0] & 0x03);

      // elevator is on the first floor
      if(currentFloor == FLOOR_1)
      {
        SET_BITS(FLOOR_STATUS_LEDS_PORT, FLOOR_STATUS_LED_1);
        CLR_BITS(FLOOR_STATUS_LEDS_PORT,(FLOOR_STATUS_LED_2|FLOOR_STATUS_LED_3));
        CLR_BITS(FLOOR_REQ_LEDS_PORT,FLOOR_REQ_LED_1);   
      } 
      // elevator is on the second floor
      else if(currentFloor == FLOOR_2)
      {
        SET_BITS(FLOOR_STATUS_LEDS_PORT, FLOOR_STATUS_LED_2);
        CLR_BITS(FLOOR_STATUS_LEDS_PORT,(FLOOR_STATUS_LED_1|FLOOR_STATUS_LED_3)); 
      }
      // elevator is on the third floor
      else if(currentFloor == FLOOR_3)
      {
        // turn on floor 3 status LED and turn off the other floor LEDs
        SET_BITS(FLOOR_STATUS_LEDS_PORT, FLOOR_STATUS_LED_3);
        CLR_BITS(FLOOR_STATUS_LEDS_PORT,(FLOOR_STATUS_LED_1|FLOOR_STATUS_LED_2));
        CLR_BITS(FLOOR_REQ_LEDS_PORT,FLOOR_REQ_LED_3);    
      } 
      else
      {
       // elevator is moving
       continue;
      }
    }

    // poll for a valid floor selection
    switch(READ_CAR_FLOOR_REQ)
    {
      case FLOOR_REQ_1:
      txdata[7] |= 0x01;
      SET_BITS(FLOOR_REQ_LEDS_PORT, FLOOR_REQ_LED_1);  
      floorSelected = TRUE; 
      break;

     case FLOOR_REQ_2:
      txdata[7] |= FLOOR_2;
      SET_BITS(FLOOR_REQ_LEDS_PORT, FLOOR_REQ_LED_2);
      floorSelected = TRUE;
      break;

     case FLOOR_REQ_3:
      txdata[7] |= 0x03;
      SET_BITS(FLOOR_REQ_LEDS_PORT, FLOOR_REQ_LED_3);
        
      floorSelected = TRUE; 
      break;

    default:
      txdata[7] |= FLOOR_NONE;
      
      break;
    }
    
    SET_BITS(txdata[7], CLOSE_STATUS);
    
    // if floor requested, send CAN message 
    if(floorSelected)
    {
     /* Delay_ms(1000);
      // LED 1 is on and LED 2 is off, door is open
      if(READ_DOOR_STATE == LED_1_ON)
      {
        // Checking for door close button (SW2)
        if(BIT_IS_CLR(DOOR_STATE_PORT, 0x80))
        {
          doorState = CLOSE;
          CLR_BITS(LED_PORT, LED_1_ON);
          SET_BITS(LED_PORT, LED_2_ON); 
        }
      } 
      else 
      {
         Delay_ms(1000);
         doorState = CLOSE;
         CLR_BITS(LED_PORT, LED_1_ON);
         SET_BITS(LED_PORT, LED_2_ON);
      } */
      
  
      retCode = MSCAN_Putd(FC_CAN_ID_1, &(txdata[0]), 8, 0, 0);
      currentFloor = 0;
      txdata[7] = 0;
      floorSelected = FALSE;          
    }
    Delay_ms(100);
   }
}


//  WILL IMPLEMENT LATER
/*interrupt VectorNumber_Vcanrx void CAN_Receive(void)
{
  unsigned char length, index;
  unsigned char data[8];
  
  length = (CANRXDLR & 0x0F);
  
  for(index = 0; index < length; index++)
  {
    data[index] = *(&CANRXDSR0 + index);
  }
  
  CANRFLG = 0x01;
  
}     */