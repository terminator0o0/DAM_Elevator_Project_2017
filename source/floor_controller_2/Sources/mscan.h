#ifndef _MSCAN_H_
#define _MSCAN_H_
  

/*CANTCL1 register*
  Turn on MSCAN module
  Init mode request to enter init mode
  Enable bus clock = 8MHz*/
#define CANCTL1_INIT (CANCTL1_CANE_MASK | CANCTL1_CLKSRC_MASK)

/*CANBTR0 register
  CAN synchronization jump width = 1
  CAN prescaler value = 8*/
#define CANBTR0_INIT            0x07

/*CANBTR1 register
  CAN time segment 1 value = 4
  CAN time segment 2 value = 3
  CAN Tq = 1*/
#define CANBTR1_INIT            0x23

/*CANIDAC register*/
#define CANIDAC_INIT            0x10

#define NO_ERR                  0 

#define ERR_BUFFER_FULL         1

typedef struct CANmsg
{
  unsigned long id;
  unsigned char length;
  unsigned char rxdata[8];
  unsigned char rtr;
  unsigned char priority;
}CANmsg_t;

extern void MSCAN_Init(void);
extern void Init_CAN_Msg(CANmsg_t msgPtr);
extern void MSCAN_ListenForMsg( unsigned long id, unsigned char rtr); 
extern int MSCAN_GotMsg(void);
extern void MSCAN_Getd( CANmsg_t * thisMsg );
extern int MSCAN_Putd(unsigned long id, unsigned char * data, unsigned char length, unsigned char priority, unsigned char rtr);

#endif