#ifndef _MSCAN_H
#define _MSCAN_H

/*CANTCL0 register*/
#define CANCTL1_INITRQ_MASK     0x01  

/*CANTCL1 register*/
// turn on MSCAN module
#define CANCTL1_CANE_MASK       0x80
// init mode request to enter init mode
#define CANCTL1_INITAK_MASK     0x01
// enable bus clock = 8MHz
#define CANCTL1_CLKSRC_MASK     0x40
#define CANCTL1_INIT (CANCTL1_CANE_MASK & CANCTL1_CLKSRC_MASK)

/*CANBTR0 register*/
// CAN synchronization jump width = 1
// CAN prescaler value = 8
#define CANBTR0_INIT            0x07

/*CANBTR1 register*/
// CAN time segment 1 value = 4
// CAN time segment 2 value = 3
// CAN Tq = 1
#define CANBTR1_INIT            0x23

#define NO_ERR                  0 

#define ERR_BUFFER_FULL         1




typedef struct msgFrame
{
  unsigned long id;
  unsigned char priority;
  unsigned char length;
  unsigned char *txdata;
}*CANmsg_t;

#endif