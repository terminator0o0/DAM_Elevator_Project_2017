#ifndef _UTILS_H_
#define _UTILS_H_

#include <hidef.h>
#include "mc9s12c32.h"
#include "bit_fiddling.h"

#pragma LINK_INFO DERIVATIVE "mc9s12c32"

// *** Macros specific to the HCS12 Timer Module

// Init value for TSCR1 to enable timer, freeze the timer while debugging, and use the fast-clear function
#define TSCR1_INIT            (TSCR1_TEN_MASK | TSCR1_TFFCA_MASK | TSCR1_TSFRZ_MASK)

// Macro and manifests to set the timer prescale value to one of 8 valid values
#define SET_TCNT_PRESCALE( value )  FORCE_BITS( TSCR2, TSCR2_PR_MASK, (value) )
#define TCNT_PRESCALE_1       0x00
#define TCNT_PRESCALE_2       0x01
#define TCNT_PRESCALE_4       0x02
#define TCNT_PRESCALE_8       0x03
#define TCNT_PRESCALE_16      0x04
#define TCNT_PRESCALE_32      0x05
#define TCNT_PRESCALE_64      0x06
#define TCNT_PRESCALE_128     0x07

// Macro to set the specified channel as output compare
#define MAKE_CHNL_OC( chnl )              SET_BITS( TIOS, 0x01 << (chnl) )

// Macro to set the specified channel as input capture
#define MAKE_CHNL_IC( chnl )              CLR_BITS( TIOS, 0x01 << (chnl) )

// Macro to allow the specified channel to generate interrupts
#define ENABLE_CHNL_INTERRUPT( chnl )     SET_BITS( TIE, 0x01 << (chnl) )

// Macros, variables, etc for the easy setup of channel OC action
// Name definition to access the timer control registers 1 and 2 as a 16-bit word  (used in following macro)
// 0x03 in macro is the mask for the action value (2 bits)
#define TCTL_1_2 (*(volatile word * const)&TCTL1)

#define SET_OC_ACTION( chnl, action )     FORCE_BITS( TCTL_1_2, (0x03 << ((chnl) * 2)), ((action) << ((chnl) * 2)) )
#define OC_OFF                0x00
#define OC_TOGGLE             0x01
#define OC_GO_LO              0x02
#define OC_GO_HI              0x03

// Macro to cause the OC action specifed for a channel to happen immediately
#define FORCE_OC_ACTION( chnl )           SET_BITS( CFORC, (0x01 << (chnl)) )

// Macros, variables, etc for the easy setup of channel IC edge sensitivity
// Name definition to access the timer control registers 3 and 4 as a 16-bit word  (used in following macro)
// 0x03 in macro is the mask for the action value (2 bits)
#define TCTL_3_4 (*(volatile word * const)&TCTL3)

#define SET_IC_EDGE( chnl, edge )         FORCE_BITS( TCTL_3_4, (0x03 << ((chnl) * 2)), ((edge) << ((chnl) * 2)) )
#define IC_OFF                0x00 
#define IC_DETECT_RISING      0x01
#define IC_DETECT_FALLING     0x02
#define IC_DETECT_BOTH        0x03

#define OC_1MS_DELAY            (125)                   // number of counts to 1 ms delay based on prescaler of 64 and 8 MHz E clock  

#define SCI_RCV_ERROR_MASK				((SCISR1_PF_MASK | SCISR1_FE_MASK | SCISR1_NF_MASK | SCISR1_OR_MASK))
#define SCI_HAS_RCV_ERRORS 				BIT_IS_SET( SCISR1,SCI_RCV_ERROR_MASK ) 

#define START_ADC_CHNL( chnl )    FORCE_BITS( ATDCTL5, ATDCTL5_Cx_MASK, (chnl) )


extern void Delay_ms( word delayTime );

#endif