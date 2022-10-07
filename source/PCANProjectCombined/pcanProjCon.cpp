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
#include <string>

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
//int pcanWrite(int ID, int message, int cF);
void queueTable(int ID, int msg, string doorState, int cF);
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
    int curFloor = 0;
    string doorState = "";
    
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
        
        if ((int)Message.ID == 0x101){
            printf("Received ID 0x101: %x\n", Message.DATA[0]);
            if (Message.DATA[0] == 5 || Message.DATA[0] == 1){ 
                curFloor = 1; // F1
                printf("Current floor is 1\n");
            }
            else if (Message.DATA[0] == 6 || Message.DATA[0] == 2){
                curFloor = 2; //F2
                printf("Current floor is 2\n");
            }
            else if (Message.DATA[0] == 7 || Message.DATA[0] == 3){
                curFloor = 3; //F3
                printf("Current floor is 3\n");
            } 
            else {
                curFloor = 0; //moving
                printf("Currently moving\n");
            }
            // add current floor into table
            sql::Driver *driver;	// Pointer to MySQL driver object
            sql::Connection *con;	// Pointer to database connection object
            sql::PreparedStatement *prep_stmt;
            sql::ResultSet *res;	// Pointer to ResultSet object

            /* Create a connection */
            driver = get_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "root", ""); // IP and password of MySQL server database 
            con->setSchema("elevator_project_2017");	// Connect to the MySQL "test" database - replace with your database

            prep_stmt = con->prepareStatement("UPDATE cFloor_table SET currentFloor = ? WHERE ID = 1");
            prep_stmt->setInt(1, curFloor);
            prep_stmt->execute();

            /* Clean up pointers */
            delete prep_stmt;
            delete res;
            delete con;
        }
        
        if ((int)Message.ID == 0x200){
            printf("Received ID 0x200: %x\n", Message.DATA[0]);
            if (Message.DATA[7] == 4 || Message.DATA[7] == 5 || Message.DATA[7] == 6 || Message.DATA[7] == 7){ 
                doorState = "closed"; // closed
                printf("Door is closed\n");
            }
            else if(Message.DATA[7] == 1 || Message.DATA[7] == 2 || Message.DATA[7] == 3){
                doorState = "open"; //open
                printf("Door is open\n");
            }
            else {
                printf("Something is wrong with door state\n");
            }
                        // add current floor into table
            sql::Driver *driver;	// Pointer to MySQL driver object
            sql::Connection *con;	// Pointer to database connection object
            sql::PreparedStatement *prep_stmt;
            sql::ResultSet *res;	// Pointer to ResultSet object

            /* Create a connection */
            driver = get_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "root", ""); // IP and password of MySQL server database 
            con->setSchema("elevator_project_2017");	// Connect to the MySQL "test" database - replace with your database

            prep_stmt = con->prepareStatement("UPDATE dState_table SET doorState = ? WHERE ID = 1");
            prep_stmt->setString(1, doorState);
            prep_stmt->execute();

            /* Clean up pointers */
            delete prep_stmt;
            delete res;
            delete con;
        }
        
        if ((int)Message.ID == 0x200 || (int)Message.ID == 0x201 || (int)Message.ID == 0x202 || (int)Message.ID == 0x203)
        {
            printf("Received ID: %4x\n", (int)Message.ID);
            
            // LSByte contains data
            switch(Message.DATA[7]){
                case 1 :
                        //printf("Door OPEN Floor 1\n");
                        //pcanWrite(0x05);
                        break;
                case 2 :
                        //printf("Door OPEN Floor 2\n");
                        //pcanWrite(0x06);
                        break;
                case 3 :
                        //printf("Door OPEN Floor 3\n");
                        //pcanWrite(0x07);
                        break;
                case 5 :
                        printf("Requested Floor 1\n");
                        queueTable(Message.ID,0x05, doorState, curFloor);
                        break;
                case 6 :
                        printf("Request Floor 2\n");
                        queueTable(Message.ID,0x06, doorState, curFloor);
                        break;
                case 7 :
                        printf("Requested Floor 3\n");
                        queueTable(Message.ID,0x07, doorState, curFloor);
                        break;					
                default:
                        break;
            }

        }
    }


    return 0;
}


void queueTable(int ID, int message, string doorState, int cF)
{
    int nID = ID;
    int rF = 0;
    string dS;
    //int cF = 0;
    
    if (ID == 512){
        nID = 200;
    } 
    else if (ID == 513){
        nID = 201;
    }
    else if (ID == 514){
        nID = 202;
    }
    else if (ID == 515){
        nID = 203;
    }
    else {
        nID = 0;
    }
    
    if (message == 0x05){
            rF = 1;
            dS = doorState;
            //cF = 0
            printf("I'm going to floor 1\n");
    } else if (message == 0x06) {
            rF = 2;
            dS = doorState;
            //cF = 0;
            printf("I'm going to floor 2\n");
    } else if (message == 0x07) {
            rF = 3;
            dS = doorState;
            //cF = 0;
            printf("I'm going to floor 3\n");
    } else {
            printf("Something went wrong\n");
    }

    sql::Driver *driver;	// Pointer to MySQL driver object
    sql::Connection *con;	// Pointer to database connection object
    sql::PreparedStatement *prep_stmt;
    sql::ResultSet *res;	// Pointer to ResultSet object

    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", ""); // IP and password of MySQL server database 
    con->setSchema("elevator_project_2017");	// Connect to the MySQL "test" database - replace with your database

    /* Execute a query and wait for result */
    prep_stmt = con->prepareStatement("INSERT INTO CAN_network (CAN_ID, requestedFloor, doorState, currentFloor, dateID, timeID ) VALUES (?, ?, ?, ?, CURRENT_DATE(), CURRENT_TIME())");
    
    prep_stmt->setInt(1, nID);
    prep_stmt->setInt(2, rF);
    prep_stmt->setString(3, dS);
    prep_stmt->setInt(4,cF);
    prep_stmt->execute();
    
    prep_stmt = con->prepareStatement("INSERT INTO queue_table (nodeID, requestedFloor, doorState, currentFloor) VALUES (?, ?, ?, ?)");
    
    prep_stmt->setInt(1, nID);
    prep_stmt->setInt(2, rF);
    prep_stmt->setString(3, dS);
    prep_stmt->setInt(4,cF);
    prep_stmt->execute();

    /* Clean up pointers */
    delete prep_stmt;
    delete res;
//  delete stmt;
    delete con;

}