/*
 * Copyright 2020 JG Mechatronics AB
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *****************************************************************************
 *
 *  usartTest.cpp
 *
 *  Created on: 04-Mar 2023 latest modified: 04 mar 2023
 *      Author: Jeppa
 */

#include <cstring>

#include "../../dma/mock/inc/dmaMock.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "serialPortImp.hpp"
#include "usartMock.hpp"
#include "dmaMock.hpp"

TEST_GROUP( SerialPort  )
{
	UsartMock*         usartMock;
	DmaMock*           txDmaMock;
	DmaMock*           rxDmaMock;
	Usart*             usart;
	Dma* 	           txDma;
	Dma* 	           rxDma;

	SerialPort*        serialPort;

	void setup()
	{
		usartMock = new UsartMock;
		txDmaMock = new DmaMock;
		rxDmaMock = new DmaMock;
		usart     = static_cast <Usart*>( usartMock );
		txDma     = static_cast <Dma*> (txDmaMock);
		rxDma     = static_cast <Dma*> (rxDmaMock);

	}

	void teardown()
	{
		mock().checkExpectations();
		mock().clear();
		delete usartMock;
		delete rxDmaMock;
		delete txDmaMock;
		usart = nullptr;
		rxDma = nullptr;
		txDma = nullptr;
	}

};

/*! Check that when a serial port is instantiated:
 * Things do happen.
 */
TEST( SerialPort, Instantiate )
{
	serialPort = static_cast<SerialPort*>( new SerialPortImp( /* Usart */ usart,
	                                                          /* txDma */ txDma,
												              /* rxDma */ rxDma ) );

	delete serialPort;
}


int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}
