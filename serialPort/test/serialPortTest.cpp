/*
 * Copyright 2023 JG Mechatronics AB
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
 *  serialTest.cpp
 *
 *  Created on: 04-Mar 2023 latest modified: 04 mar 2023
 *      Author: Jeppa
 */

#include <cstring>

#include "../../dma/mock/inc/dmaMock.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTest/TestRegistry.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTestExt/MockSupportPlugin.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "serialPortImp.hpp"
#include "usartMock.hpp"
#include "dmaMock.hpp"

class Uint16Comparator : public MockNamedValueComparator
{
public:
    virtual bool isEqual(const void* object1, const void* object2)
    {
        return *static_cast<const uint16_t*>( object1 ) == *static_cast<const uint16_t*>( object2 );
    }
    virtual SimpleString valueToString(const void* object)
    {
        return StringFrom( *static_cast<const uint16_t*>( object) );
    }
};

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
		mock().removeAllComparatorsAndCopiers();
	}

	SerialPort* pInstantiateSerialPort()
	{
	    mock().disable();
	    SerialPort* pSerialPort = static_cast<SerialPort*>( new SerialPortImp( /* Usart */ usart,
                                                                               /* txDma */ txDma,
                                                                               /* rxDma */ rxDma ) );
        mock().enable();
	    return pSerialPort;
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

/*! Check that when a tx buffer is handed to an instantiated serial port:
 *  - The address of the first object in the buffer is handed to the txDma object using the
 *    setMemory0Address method.
 *  - The number of data is written to the txDma object using the setNumberOfData method.
 *  - The clearTxComplete method of the usart is called
 *  - The enable method of the txDma object is called
 */
TEST( SerialPort, TransmitBuffer )
{

    const char* helloStr = "Hello World";
    void* hello = const_cast<void*>( static_cast<const void*>( helloStr ) );
    uint16_t size = 11;

    serialPort = pInstantiateSerialPort();

    mock().expectOneCall( "setMemory0Address" ).onObject( txDma ).withPointerParameter( "pvAddress", hello );
    mock().expectOneCall( "setNumberOfData" ).onObject( txDma ).withParameterOfType( "uint16_t", "ui16NumberOfData", &size );
    mock().expectOneCall( "clearTxComplete" ).onObject( usart );
    mock().expectOneCall( "enable" ).onObject( txDma );

    serialPort->transmit( hello, 11 );

    delete serialPort;
}

/*! Check that when an Rx buffer is handed to a newly instantiated serial port:
 *  - The rxDma buffer is disabled
 *  - The DMA buffer is polled for the number of data remaining - 0 is returned
 *  - The address of the first object in the buffer is handed to the rxDma object using the
 *    setMemory0Address method.
 *  - The rxBuffer size is written to the rxDma object using the setNumberOfData method.
 *  - The enable method of the rxDma object is called
 *  - zero is returned
 */
TEST( SerialPort, ReceiveFirstBuffer )
{

    const char* rxStr = "\0\0\0\0\0\0";
    void* rxBuffer = const_cast<void*>( static_cast<const void*>( rxStr ) );
    uint16_t size = 6;
    uint16_t numberOfRxData = 0;

    serialPort = pInstantiateSerialPort();

    mock().expectOneCall( "disable" ).onObject( rxDma );
    rxDmaMock->expectGetNumberOfData( 0 );
    mock().expectOneCall( "setMemory0Address" ).onObject( rxDma ).withPointerParameter( "pvAddress", rxBuffer );
    mock().expectOneCall( "setNumberOfData" ).onObject( rxDma ).withParameterOfType( "uint16_t", "ui16NumberOfData", &size );
    mock().expectOneCall( "enable" ).onObject( rxDma );

    CHECK_EQUAL( serialPort->receive( rxBuffer, size ), numberOfRxData );

    delete serialPort;
}

/*! Check that when a second Rx buffer is handed to a newly instantiated serial port
 *  when no bytes have been written to the first buffer:
 *  - The rxDma buffer is disabled
 *  - The DMA buffer is polled for the number of data remaining - The same number as was written to the
 *    rxDma when the first buffer was handed to it is returned.
 *  - The address of the first object in the buffer is handed to the rxDma object using the
 *    setMemory0Address method.
 *  - The rxBuffer size is written to the rxDma object using the setNumberOfData method.
 *  - The enable method of the rxDma object is called
 *  - zero is returned
 */
TEST( SerialPort, ReceiveSecondBufferNoBytesRead )
{

    const char* rxStr1 = "\0\0\0\0\0\0";
    const char* rxStr2 = "\0\0\0\0\0\0";
    void* rxBuffer1 = const_cast<void*>( static_cast<const void*>( rxStr1 ) );
    void* rxBuffer2 = const_cast<void*>( static_cast<const void*>( rxStr2 ) );
    uint16_t size = 6;
    uint16_t numberOfRxData1 = 0;
    uint16_t numberOfRxData2 = size; // means that no data was read to the buffer

    serialPort = pInstantiateSerialPort();

    /* Hand the first buffer to the rxDma Object */
    mock().expectOneCall( "disable" ).onObject( rxDma );
    rxDmaMock->expectGetNumberOfData( numberOfRxData1 );
    mock().expectOneCall( "setMemory0Address" ).onObject( rxDma ).withPointerParameter( "pvAddress", rxBuffer1 );
    mock().expectOneCall( "setNumberOfData" ).onObject( rxDma ).withParameterOfType( "uint16_t", "ui16NumberOfData", &size );
    mock().expectOneCall( "enable" ).onObject( rxDma );

    CHECK_EQUAL( serialPort->receive( rxBuffer1, size ), 0 );

    /* Hand a second buffer to the rxDma object - No data has been read into the first buffer */
    mock().expectOneCall( "disable" ).onObject( rxDma );
    rxDmaMock->expectGetNumberOfData( numberOfRxData2 );
    mock().expectOneCall( "setMemory0Address" ).onObject( rxDma ).withPointerParameter( "pvAddress", rxBuffer2 );
    mock().expectOneCall( "setNumberOfData" ).onObject( rxDma ).withParameterOfType( "uint16_t", "ui16NumberOfData", &size );
    mock().expectOneCall( "enable" ).onObject( rxDma );

    CHECK_EQUAL( serialPort->receive( rxBuffer2, size ), 0 );

    delete serialPort;
}

/*! Check that when a second Rx buffer is handed to a newly instantiated serial port
 *  when spome bytes have been written to the first buffer:
 *  - The rxDma buffer is disabled
 *  - The DMA buffer is polled for the number of data remaining - A smaller number than the number written
 *    to the rxDma when the first buffer was handed to it is returned.
 *  - The address of the first object in the buffer is handed to the rxDma object using the
 *    setMemory0Address method.
 *  - The rxBuffer size is written to the rxDma object using the setNumberOfData method.
 *  - The enable method of the rxDma object is called
 *  - The difference between  the buffer size and the remaining number of data in rxBuffer1,
 *    i.e the number of received data since the first buffer was initiated is returned
 */
TEST( SerialPort, ReceiveSecondBufferSomeBytesRead )
{

    const char* rxStr1 = "\0\0\0\0\0\0";
    const char* rxStr2 = "\0\0\0\0\0\0";
    void* rxBuffer1 = const_cast<void*>( static_cast<const void*>( rxStr1 ) );
    void* rxBuffer2 = const_cast<void*>( static_cast<const void*>( rxStr2 ) );
    uint16_t size = 6;
    uint16_t numberOfRxData1 = 0;
    uint16_t numberOfReadBytes = 2;
    uint16_t numberOfRxData2 = size - numberOfReadBytes; // means that 3 bytes were read to the buffer

    serialPort = pInstantiateSerialPort();

    /* Hand the first buffer to the rxDma Object */
    mock().expectOneCall( "disable" ).onObject( rxDma );
    rxDmaMock->expectGetNumberOfData( numberOfRxData1 );
    mock().expectOneCall( "setMemory0Address" ).onObject( rxDma ).withPointerParameter( "pvAddress", rxBuffer1 );
    mock().expectOneCall( "setNumberOfData" ).onObject( rxDma ).withParameterOfType( "uint16_t", "ui16NumberOfData", &size );
    mock().expectOneCall( "enable" ).onObject( rxDma );

    CHECK_EQUAL( serialPort->receive( rxBuffer1, size ), 0 );

    /* Hand a second buffer to the rxDma object - Some bytes have been read into the first buffer */
    mock().expectOneCall( "disable" ).onObject( rxDma );
    rxDmaMock->expectGetNumberOfData( numberOfRxData2 );
    mock().expectOneCall( "setMemory0Address" ).onObject( rxDma ).withPointerParameter( "pvAddress", rxBuffer2 );
    mock().expectOneCall( "setNumberOfData" ).onObject( rxDma ).withParameterOfType( "uint16_t", "ui16NumberOfData", &size );
    mock().expectOneCall( "enable" ).onObject( rxDma );

    CHECK_EQUAL( serialPort->receive( rxBuffer2, size ), numberOfReadBytes );

    delete serialPort;
}

int main( int ac, char** av )
{
    Uint16Comparator uint16Comparator;
    MockSupportPlugin mockPlugin;

    mockPlugin.installComparator("uint16_t", uint16Comparator);
    TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);
    return CommandLineTestRunner::RunAllTests( ac, av );
}
