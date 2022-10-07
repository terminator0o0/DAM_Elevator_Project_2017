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
#include <PCANBasic.h>

#define PCAN_DEVICE		PCAN_USBBUS1

#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>  // Connector/C++ exceptions could be used 
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

/*********PROTOTYPES*********************/
int pcanWrite(int ID, int message);
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

int main(void) {
    TPCANMsg Message;
    TPCANStatus Status;
    //unsigned long ulIndex = 0;
   
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
                        printf("Door OPEN Floor 1\n");
                        //pcanWrite(0x05);
                        break;
                case 2 :
                        printf("Door OPEN Floor 2\n");
                        //pcanWrite(0x06);
                        break;
                case 3 :
                        printf("Door OPEN Floor 3\n");
                        //pcanWrite(0x07);
                        break;
                case 5 :
                        printf("Floor 1\n");
                        pcanWrite((int)Message.ID,0x05);
                        break;
                case 6 :
                        printf("Floor 2\n");
                        pcanWrite((int)Message.ID,0x06);
                        break;
                case 7 :
                        printf("Floor 3\n");
                        pcanWrite((int)Message.ID,0x07);
                        break;					
                default:
                        break;
            }
            //break;

        }
    }

    return 0;
}


int pcanWrite(int ID, int message)
{
    TPCANMsg TXMessage;
    TPCANStatus TXStatus;
    //unsigned long ulIndex = 0;
    int x = 0;

    //Status = CAN_Initialize(PCAN_DEVICE, PCAN_BAUD_125K, 0, 0, 0);
    //printf("Initialize CAN: %x\n",(int)Status);
    printf("test %2x\n\n", message);

    TXMessage.ID = 0x100;
    TXMessage.LEN = 8;
    TXMessage.MSGTYPE = PCAN_MESSAGE_STANDARD;
    for (x = 0; x<8; x++){
        TXMessage.DATA[x]= 0x00;
    }
    TXMessage.DATA[0]= message;
    printf("%2x", TXMessage.DATA[0]);

    //while(1)
    while ((TXStatus=CAN_Write(PCAN_DEVICE,&TXMessage)) == PCAN_ERROR_OK) {
        TXMessage.DATA[0];
        //ulIndex++;
        //if ((ulIndex % 1000) == 0)
              //  printf("  - T Message %i\n", (int)ulIndex);
    }

    //printf("STATUS %i\n", (int)Status);

    int nID = ID;
    int rF = 0;
    string dS;
    int cF = 0;

    if (message == 0x05){
            rF = 1;
            dS = "close";
            cF = 0;
            printf("I'm going to floor 1\n");
    } else if (message == 0x06) {
            rF = 2;
            dS = "close";
            cF = 0;
    } else if (message == 0x07) {
            rF = 3;
            dS = "close";
            cF = 0;
    } else {
            printf("Something went wrong\n");
    }

    sql::Driver *driver;	// Pointer to MySQL driver object
    sql::Connection *con;	// Pointer to database connection object
    //sql::Statement *stmt;	// Pointer to statement object
    sql::PreparedStatement *prep_stmt;
    sql::ResultSet *res;	// Pointer to ResultSet object

    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", ""); // IP and password of MySQL server database 
    con->setSchema("elevator_project_2017");	// Connect to the MySQL "test" database - replace with your database

    /* Execute a query and wait for result */
    prep_stmt = con->prepareStatement("INSERT INTO elevator_network (requestedFloor, doorState, currentFloor, dateID, timeID) VALUES (?, ?, ?, CURRENT_DATE(), CURRENT_TIME())");
    
    prep_stmt->setInt(1, rF);
    prep_stmt->setString(2, dS);
    prep_stmt->setInt(3,cF);
    prep_stmt->execute();
            
    //stmt = con->createStatement(); 
    //res = stmt->executeQuery("INSERT INTO elevator_network (requestedFloor, doorState, currentFloor, dateID, timeID) VALUES (:rF, :dS, :cF, CURRENT_DATE(), CURRENT_TIME())");  // Query (see previous lectures)
//	while (res->next()) {
//		cout << "\t.. MySQL replies:: ";
//		cout << res->getString(1) << endl;
//                cout << res->getString(2) << endl;
//                cout << res->getString(3) << endl;
//	}

    /* Clean up pointers */
    delete prep_stmt;
    delete res;
//  delete stmt;
    delete con;

    return 0;
}