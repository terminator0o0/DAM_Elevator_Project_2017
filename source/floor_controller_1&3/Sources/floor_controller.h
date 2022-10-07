#ifndef _FLOOR_CONTROLLER_H_
#define _FLOOR_CONTROLLER_H_

/* BUTTONS INIT */
#define PTAD_AS_GPIO_MASK 0x07
#define DDRAD_INIT  0x00
#define PTAD_INIT 0x07
#define READ_CAR_FLOOR_REQ (PTAD & 0x07)

/* DOOR STATUS */
#define LED_PORT_DDR DDRS
#define LED_PORT  PTS
#define DOOR_LEDS_ON  (PTS_PTS2_MASK | PTS_PTS3_MASK)
#define DOOR_LEDS_OFF (PTS_PTS2_MASK | PTS_PTS3_MASK)
#define LED_1_ON  PTS_PTS2_MASK
#define LED_2_ON  PTS_PTS3_MASK
#define READ_DOOR_STATE (PTS & 0x0C)

/* FLOOR REQUEST */
#define FLOOR_REQ_LEDS_DDR  DDRB
#define FLOOR_REQ_LEDS_PORT PORTB
#define DDRB_OUTPUT         0x07
#define FLOOR_REQ_LED_1     0x01
#define FLOOR_REQ_LED_2     0x02
#define FLOOR_REQ_LED_3     0x04
#define FLOOR_REQ_1         0x01
#define FLOOR_REQ_2         0x02
#define FLOOR_REQ_3         0x04
#define FLOOR_REQ_LEDS_ON   0x03
#define FLOOR_REQ_LEDS_OFF  0x03
#define FLOOR_REQ_LED_UP    0x01
#define FLOOR_REQ_LED_DOWN  0x02

/* ELEVATOR STATUS */
#define FLOOR_STATUS_LEDS_DDR  DDRA
#define FLOOR_STATUS_LEDS_PORT PORTA
#define DDRA_OUTPUT        0x07
#define FLOOR_STATUS_LED_1 0x01
#define FLOOR_STATUS_LED_2 0x02
#define FLOOR_STATUS_LED_3 0x04
#define FLOOR_STATUS_LEDS_ON  0x07
#define FLOOR_STATUS_LEDS_OFF  0x07

#define DOOR_STATE_DDR  DDRJ
#define DOOR_STATE_PORT PTJ
#define DDRJ_INIT       0xC0
#define OPEN            0x00
#define CLOSE           0x01
#define DOOR_BUTTON_OPEN 0x80
#define DOOR_BUTTON_CLOSE 0x40
#define CLOSE_STATUS    0x04

#define FLOOR_NONE  0x00
#define FLOOR_1     0x01
#define FLOOR_2     0x02
#define FLOOR_3     0x03
#define FLOOR_UP    0x01
#define FLOOR_DOWN  0x02  

#define FC_CAN_ID_3  0x203
#define FC_CAN_ID_2  0x202
#define FC_CAN_ID_1  0x201
#define EC_CAN_ID    0x101

#define RTR_VALUE  0

extern void Init_Floor_Controller(void);
extern void Write_C_LED(int led);

#endif