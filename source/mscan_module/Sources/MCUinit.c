/*
** ###################################################################
**     This code is generated by the Device Initialization Tool.
**     It is overwritten during code generation.
**     USER MODIFICATION ARE PRESERVED ONLY INSIDE INTERRUPT SERVICE ROUTINES
**     OR EXPLICITLY MARKED SECTIONS
**
**     Project   : mscan_module
**     Processor : MC9S12C32CFU16
**     Version   : Component 02.001, Driver 01.05, CPU db: 2.87.410
**     Datasheet : MC9S12C128 Rev 01.23 05/2007
**     Date/Time : 17/05/2017, 1:47 PM
**     Abstract  :
**         This module contains device initialization code 
**         for selected on-chip peripherals.
**     Contents  :
**         Function "MCU_init" initializes selected peripherals
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################
*/
/* MODULE MCUinit */

#include <MC9S12C32.h>                 /* I/O map for MC9S12C32CFU16 */
#include "MCUinit.h"

/* Standard ANSI C types */
#ifndef int8_t
typedef signed char int8_t;
#endif
#ifndef int16_t
typedef signed int   int16_t;
#endif
#ifndef int32_t
typedef signed long int    int32_t;
#endif

#ifndef uint8_t
typedef unsigned char       uint8_t;
#endif
#ifndef uint16_t
typedef unsigned int  uint16_t;
#endif
#ifndef uint32_t
typedef unsigned long int   uint32_t;
#endif

#define CGM_DELAY  0x03FFU

/* User declarations and definitions */
/*   Code, declarations and definitions here will be preserved during code generation */
/* End of user declarations and definitions */

extern void near _Startup(void);

#pragma CODE_SEG __NEAR_SEG NON_BANKED

static void MCU_init_reset(void);
/*
** ===================================================================
**     Method      :  MCU_init_reset (component MC9S12C32_80)
**
**     Description :
**         Device initialization code for after reset initialization.
** ===================================================================
*/
static void MCU_init_reset(void)
{

  /*  Initialization of memory configuration */
/* Initialization of the registers INITRG, INITRM, INITEE is done to protect them to be written accidentally later by the application */
  /*lint -save  -e950 -e923 Disable MISRA rule (1.1,11.3) checking. */
*(byte*)(0x0011U) = 0x00U;             /* Set the register map position */
asm("nop");                            /* nop instruction */
  /*lint -restore Enable MISRA rule (1.1,11.3) checking. */
  /* INITRM: RAM15=0,RAM14=0,RAM13=0,RAM12=0,RAM11=1,RAMHAL=1 */
  INITRM = 0x09U;                      /* Set the RAM map position */
  /* MISC: EXSTR1=1,EXSTR0=1,ROMHM=0,ROMON=1 */
  MISC = 0x0DU;                                      
  /* PEAR: NOACCE=0,PIPOE=0,NECLK=0,LSTRE=0,RDWE=0 */
  PEAR = 0x00U;                                      
  /* Jump to the default entry point */
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
  asm jmp _Startup;
  /*lint -restore Enable MISRA rule (1.1) checking. */
} /*MCU_init*/

#pragma CODE_SEG DEFAULT
#pragma MESSAGE DISABLE C12056



/*
** ===================================================================
**     Method      :  MCU_init (component MC9S12C32_80)
**
**     Description :
**         Device initialization code for selected peripherals.
** ===================================================================
*/
void MCU_init(void)
{

  /* ### MC9S12C32_80 "Cpu" init code ... */
  /*  PE initialization code after reset */
  /*  System clock initialization */
  /* CLKSEL: PLLSEL=0,PSTP=0,SYSWAI=0,ROAWAI=0,PLLWAI=0,CWAI=0,RTIWAI=0,COPWAI=0 */
  CLKSEL = 0x00U;                      /* Select clock source from XTAL and set bits in CLKSEL reg. */
  /* PLLCTL: CME=1,PLLON=0,AUTO=1,ACQ=1,PRE=0,PCE=0,SCME=1 */
  PLLCTL = 0xB1U;                      /* Disable the PLL */
  /* Common initialization of the CPU registers */
  /* CRGINT: LOCKIE=0,SCMIE=0 */
  CRGINT &= (unsigned char)~(unsigned char)0x12U;                     
  /* VREGCTRL: LVIE=0 */
  VREGCTRL &= (unsigned char)~(unsigned char)0x02U;                     
  /* COPCTL: WCOP=0,RSBCK=0,CR2=0,CR1=0,CR0=0 */
  COPCTL = 0x00U;                                      
  /* RDRIV: RDPE=0,RDPB=0,RDPA=0 */
  RDRIV &= (unsigned char)~(unsigned char)0x13U;                     
  /* RDRAD: RDRAD7=0,RDRAD6=0,RDRAD5=0,RDRAD4=0,RDRAD3=0,RDRAD2=0,RDRAD1=0,RDRAD0=0 */
  RDRAD = 0x00U;                                      
  /* RDRJ: RDRJ7=0,RDRJ6=0 */
  RDRJ &= (unsigned char)~(unsigned char)0xC0U;                     
  /* RDRM: RDRM5=0,RDRM4=0,RDRM3=0,RDRM2=0,RDRM1=0,RDRM0=0 */
  RDRM &= (unsigned char)~(unsigned char)0x3FU;                     
  /* RDRP: RDRP7=0,RDRP6=0,RDRP5=0,RDRP4=0,RDRP3=0,RDRP2=0,RDRP1=0,RDRP0=0 */
  RDRP = 0x00U;                                      
  /* RDRS: RDRS3=0,RDRS2=0,RDRS1=0,RDRS0=0 */
  RDRS &= (unsigned char)~(unsigned char)0x0FU;                     
  /* RDRT: RDRT7=0,RDRT6=0,RDRT5=0,RDRT4=0,RDRT3=0,RDRT2=0,RDRT1=0,RDRT0=0 */
  RDRT = 0x00U;                                      
  /* INTCR: IRQEN=0 */
  INTCR &= (unsigned char)~(unsigned char)0x40U;                     
  /* ### */
  /* Initial interrupt priority */
  /*lint -save  -e950 Disable MISRA rule (1.1) checking. */
  asm CLI;                             /* Enable interrupts */
  /*lint -restore Enable MISRA rule (1.1) checking. */
} /*MCU_init*/

#pragma MESSAGE DEFAULT C12056

/*lint -save  -e765 Disable MISRA rule (8.10) checking. */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
/*
** ===================================================================
**     Interrupt handler : isr_default
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
__interrupt void isr_default(void)
{
  /* Write your interrupt code here ... */

}
/* end of isr_default */
#pragma CODE_SEG DEFAULT


/*lint -restore Enable MISRA rule (8.10) checking. */

/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
/* Initialization of the CPU registers in FLASH */
/*lint -restore Enable MISRA rule (1.1) checking. */




/* Interrupt vector table */


/* ISR prototype */
typedef void (*near tIsrFunc)(void);

#ifndef UNASSIGNED_ISR
  #define UNASSIGNED_ISR isr_default   /* unassigned interrupt service routine */
#endif
/*lint -save  -e950 Disable MISRA rule (1.1) checking. */
static const tIsrFunc _InterruptVectorTable[] @0xFF80U = { /* Interrupt vector table */
/*lint -restore Enable MISRA rule (1.1) checking. */
  /* ISR name                               No. Address Pri Name          Description */
  &UNASSIGNED_ISR,                     /* 0x3F  0xFF80   1  ivVReserved63 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x3E  0xFF82   1  ivVReserved62 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x3D  0xFF84   1  ivVReserved61 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x3C  0xFF86   1  ivVReserved60 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x3B  0xFF88   1  ivVReserved59 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x3A  0xFF8A   1  ivVvreglvi    unused by PE */
  &UNASSIGNED_ISR,                     /* 0x39  0xFF8C   1  ivVpwmesdn    unused by PE */
  &UNASSIGNED_ISR,                     /* 0x38  0xFF8E   1  ivVportp      unused by PE */
  &UNASSIGNED_ISR,                     /* 0x37  0xFF90   1  ivVReserved55 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x36  0xFF92   1  ivVReserved54 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x35  0xFF94   1  ivVReserved53 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x34  0xFF96   1  ivVReserved52 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x33  0xFF98   1  ivVReserved51 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x32  0xFF9A   1  ivVReserved50 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x31  0xFF9C   1  ivVReserved49 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x30  0xFF9E   1  ivVReserved48 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x2F  0xFFA0   1  ivVReserved47 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x2E  0xFFA2   1  ivVReserved46 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x2D  0xFFA4   1  ivVReserved45 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x2C  0xFFA6   1  ivVReserved44 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x2B  0xFFA8   1  ivVReserved43 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x2A  0xFFAA   1  ivVReserved42 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x29  0xFFAC   1  ivVReserved41 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x28  0xFFAE   1  ivVReserved40 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x27  0xFFB0   1  ivVcantx      unused by PE */
  &UNASSIGNED_ISR,                     /* 0x26  0xFFB2   1  ivVcanrx      unused by PE */
  &UNASSIGNED_ISR,                     /* 0x25  0xFFB4   1  ivVcanerr     unused by PE */
  &UNASSIGNED_ISR,                     /* 0x24  0xFFB6   1  ivVcanwkup    unused by PE */
  &UNASSIGNED_ISR,                     /* 0x23  0xFFB8   1  ivVflash      unused by PE */
  &UNASSIGNED_ISR,                     /* 0x22  0xFFBA   1  ivVReserved34 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x21  0xFFBC   1  ivVReserved33 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x20  0xFFBE   1  ivVReserved32 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x1F  0xFFC0   1  ivVReserved31 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x1E  0xFFC2   1  ivVReserved30 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x1D  0xFFC4   1  ivVcrgscm     unused by PE */
  &UNASSIGNED_ISR,                     /* 0x1C  0xFFC6   1  ivVcrgplllck  unused by PE */
  &UNASSIGNED_ISR,                     /* 0x1B  0xFFC8   1  ivVReserved27 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x1A  0xFFCA   1  ivVReserved26 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x19  0xFFCC   1  ivVReserved25 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x18  0xFFCE   1  ivVportj      unused by PE */
  &UNASSIGNED_ISR,                     /* 0x17  0xFFD0   1  ivVReserved23 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x16  0xFFD2   1  ivVatd0       unused by PE */
  &UNASSIGNED_ISR,                     /* 0x15  0xFFD4   1  ivVReserved21 unused by PE */
  &UNASSIGNED_ISR,                     /* 0x14  0xFFD6   1  ivVsci        unused by PE */
  &UNASSIGNED_ISR,                     /* 0x13  0xFFD8   1  ivVspi        unused by PE */
  &UNASSIGNED_ISR,                     /* 0x12  0xFFDA   1  ivVtimpaie    unused by PE */
  &UNASSIGNED_ISR,                     /* 0x11  0xFFDC   1  ivVtimpaovf   unused by PE */
  &UNASSIGNED_ISR,                     /* 0x10  0xFFDE   1  ivVtimovf     unused by PE */
  &UNASSIGNED_ISR,                     /* 0x0F  0xFFE0   1  ivVtimch7     unused by PE */
  &UNASSIGNED_ISR,                     /* 0x0E  0xFFE2   1  ivVtimch6     unused by PE */
  &UNASSIGNED_ISR,                     /* 0x0D  0xFFE4   1  ivVtimch5     unused by PE */
  &UNASSIGNED_ISR,                     /* 0x0C  0xFFE6   1  ivVtimch4     unused by PE */
  &UNASSIGNED_ISR,                     /* 0x0B  0xFFE8   1  ivVtimch3     unused by PE */
  &UNASSIGNED_ISR,                     /* 0x0A  0xFFEA   1  ivVtimch2     unused by PE */
  &UNASSIGNED_ISR,                     /* 0x09  0xFFEC   1  ivVtimch1     unused by PE */
  &UNASSIGNED_ISR,                     /* 0x08  0xFFEE   1  ivVtimch0     unused by PE */
  &UNASSIGNED_ISR,                     /* 0x07  0xFFF0   1  ivVrti        unused by PE */
  &UNASSIGNED_ISR,                     /* 0x06  0xFFF2   1  ivVirq        unused by PE */
  &UNASSIGNED_ISR,                     /* 0x05  0xFFF4   -  ivVxirq       unused by PE */
  &UNASSIGNED_ISR,                     /* 0x04  0xFFF6   -  ivVswi        unused by PE */
  &UNASSIGNED_ISR,                     /* 0x03  0xFFF8   -  ivVtrap       unused by PE */
  /* Reset handler name */
  &MCU_init_reset,                     /* 0x02  0xFFFA   -  ivVcop        unused by PE */
  &MCU_init_reset,                     /* 0x01  0xFFFC   -  ivVclkmon     unused by PE */
  &MCU_init_reset                      /* 0x00  0xFFFE   -  ivVreset      used by PE */
};


/* END MCUinit */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
