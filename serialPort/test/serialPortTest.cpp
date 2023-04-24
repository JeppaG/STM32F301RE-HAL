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
 * - The base address of the usart is fetched
 * - The peripheral address on both dma streams is set to the base address of the usart + 4
 * - The txDma stream is set to direction Memory to Peripheral.
 * - The rxDma stream is set to direction Peripheral to Memory.
 * - Both dma streams are set to memory incremental mode.
 * - txDma is enabled on the USART
 * - rxDma is enabled on the USART
 * - tx is enabled on the USART
 */
TEST( SerialPort, Instantiate )
{
    const void* usartBaseAddress = reinterpret_cast<const void*>( 0x40011000 );

    mock().expectOneCall( "getBaseAddress" ).onObject( usart ).andReturnValue( usartBaseAddress );
    mock().expectOneCall( "setPeripheralAddress" ).onObject( txDma ).withPointerParameter( "pvAddress", const_cast<void*>( usartBaseAddress ) + 4 );
    mock().expectOneCall( "setPeripheralAddress" ).onObject( rxDma ).withPointerParameter( "pvAddress", const_cast<void*>( usartBaseAddress ) + 4 );
    mock().expectOneCall( "setDirectionMemoryToPeripheral" ).onObject( txDma );
    mock().expectOneCall( "setDirectionPeripheralToMemory" ).onObject( rxDma );
    mock().expectOneCall( "setMemoryIncrementalMode" ).onObject( txDma );
    mock().expectOneCall( "setMemoryIncrementalMode" ).onObject( rxDma );
    mock().expectOneCall( "enableDmaTx" ).onObject( usart );
    mock().expectOneCall( "enableDmaRx" ).onObject( usart );
    mock().expectOneCall( "enable" ).onObject( usart );

	serialPort = static_cast<SerialPort*>( new SerialPortImp( /* Usart */            usart,
	                                                          /* txDma */            txDma,
												              /* rxDma */            rxDma ) );

	delete serialPort;
}


int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}
