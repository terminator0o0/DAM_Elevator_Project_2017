//  pcanread.cpp
//
//  ~~~~~~~~~~~~
//
//  PCANBasic Example: Simple Read
//
//  ~~~~~~~~~~~~
//
//  ------------------------------------------------------------------
//  Author : Thomas Haber (thomas@toem.de)
//  Last change: 18.06.2010
//
//  Language: C++
//  ------------------------------------------------------------------
//
//  Copyright (C) 1999-2010  PEAK-System Technik GmbH, Darmstadt
//  more Info at http://www.peak-system.com
//  ------------------------------------------------------------------
//
// linux@peak-system.com
// www.peak-system.com
//
//  ------------------------------------------------------------------
//  History:
//  07-11-2013 Stephane Grosjean
//  - Move DWORD definition from "unsigned long" to "__u32" to run on 64-bits
//    Kernel
//  - Change initital bitrate from 250K to 500K (default pcan driver bitrate)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
#include <stdio.h>
#include <unistd.h>
#include <asm/types.h>

/*
#define DWORD  __u32
#define WORD   unsigned short
#define BYTE   unsigned char
#define LPSTR  char*
*/
#include "../pcanbasic/PCANBasic.h"

#define PCAN_DEVICE		PCAN_USBBUS1
/*********PROTOTYPES*********************/
int pcanWrite(int message);
/****************************************/	
	
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Main entry-point for this application. </summary>
///
/// <remarks>	 </remarks>
///
/// <param name="argc">	The argc. </param>
/// <param name="argv">	[in,out] If non-null, the argv. </param>
///
/// <returns>	. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	TPCANMsg Message;
	TPCANStatus Status;
	unsigned long ulIndex = 0;

	Status = CAN_Initialize(PCAN_DEVICE, PCAN_BAUD_125K, 0, 0, 0);
	printf("Initialize CAN: %i\n",(int)Status);


	while (1) {
		while ((Status=CAN_Read(PCAN_DEVICE,&Message,NULL)) == PCAN_ERROR_QRCVEMPTY)
			usleep(1000);
		if (Status != PCAN_ERROR_OK) {
			printf("Error 0x%x\n",(int)Status);
			break;
		}

		printf("  - R ID:%4x LEN:%1x DATA:%02x %02x %02x %02x %02x %02x %02x %02x\n",
			(int)Message.ID, (int)Message.LEN,
			(int)Message.DATA[0], (int)Message.DATA[1],
			(int)Message.DATA[2], (int)Message.DATA[3],
			(int)Message.DATA[4], (int)Message.DATA[5],
			(int)Message.DATA[6], (int)Message.DATA[7]);
		
		int i = sizeof(long);
		printf("Test: %d %4d\n", i, Message.ID);
		
		if ((int)Message.ID == 0x200 || (int)Message.ID == 0x201 || (int)Message.ID == 0x202 || (int)Message.ID == 0x203)
		{
			printf("Test2: %4x\n", (int)Message.ID);
			
			switch(Message.DATA[7]){
				case 1 :
					printf("Floor 1\n");
					pcanWrite(0x05);
					break;
				case 2 :
					printf("Floor 2\n");
					pcanWrite(0x06);
					break;
				case 4 :
					printf("Floor 3\n");
					pcanWrite(0x07);
					break;
				default:
					break;
			}
			//break;
					
		}
	}
	
	return 0;
}


int pcanWrite(int message)
{
	TPCANMsg TXMessage;
	TPCANStatus TXStatus;
	//unsigned long ulIndex = 0;

	//Status = CAN_Initialize(PCAN_DEVICE, PCAN_BAUD_125K, 0, 0, 0);
	//printf("Initialize CAN: %x\n",(int)Status);
	printf("test %2x\n\n", message);
	
	TXMessage.ID = 0x100;
	TXMessage.LEN = 8;
	TXMessage.MSGTYPE = PCAN_MESSAGE_STANDARD;
	for (int x = 0; x<8; x++){
		TXMessage.DATA[x]= 0x00;
	}
	TXMessage.DATA[0]= message;
	printf("%2x", TXMessage.DATA[0]);

	//while(1)
	    while ((TXStatus=CAN_Write(PCAN_DEVICE,&TXMessage)) == PCAN_ERROR_OK) {
		TXMessage.DATA[0]++;
	        //ulIndex++;
	        //if ((ulIndex % 1000) == 0)
		      //  printf("  - T Message %i\n", (int)ulIndex);
	    }

	//printf("STATUS %i\n", (int)Status);

	return 0;
}
