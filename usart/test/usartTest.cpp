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
 *  Created on: 22-Dec 2020 latest modified: 16 jan 2021
 *      Author: jeppa & Viktor
 */

#include <cstring>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "usartImp.hpp"
#include "clockGeneratorMock.hpp"
#include "gpioMock.hpp"

TEST_GROUP( Usart  )
{
    typedef struct
    {
        volatile uint32_t status;                /* Base address + 0x0 */
        volatile uint32_t data;                  /* Base address + 0x4 */
        volatile uint32_t baudRate;              /* Base address + 0x8 */
        volatile uint32_t control1;              /* Base address + 0xC */
        volatile uint32_t control2;              /* Base address + 0x10 */
        volatile uint32_t control3;              /* Base address + 0x14 */
        volatile uint32_t guardTimeAndPrescaler; /* Base address + 0x18 */
    } usartRegisterType;

	const usartRegisterType resetRegister =
	{
	    0x00C00000, /* status Reset value */
	    0x00000000, /* data Reset value */
        0x00000000, /* baudRate Reset value */
        0x00000000, /* control1 Reset value */
        0x00000000, /* control2 Reset value */
        0x00000000, /* control3 Reset value */
        0x00000000, /* guardTimeAndPrescaler Reset value */
	};

	usartRegisterType expectedRegister;
	usartRegisterType actualRegister;

	PeripheralRccMock* rccMock;
	GpioMock*          rxPinMock;
	GpioMock*          txPinMock;
	PeripheralRcc*     rcc;
	Gpio* 	           txPin;
	Gpio* 	           rxPin;

	Usart*             usart;

	void vInitializeTestRegistersToResetValues()
	{
		memcpy( &expectedRegister, &resetRegister, sizeof( usartRegisterType ) );
		memcpy( &actualRegister, &resetRegister, sizeof( usartRegisterType ) );
	}

	void vCheckRegisters()
	{
	    CHECK_EQUAL( expectedRegister.status               , actualRegister.status                );
	    CHECK_EQUAL( expectedRegister.data                 , actualRegister.data                  );
	    CHECK_EQUAL( expectedRegister.baudRate             , actualRegister.baudRate              );
	    CHECK_EQUAL( expectedRegister.control1             , actualRegister.control1              );
	    CHECK_EQUAL( expectedRegister.control2             , actualRegister.control2              );
	    CHECK_EQUAL( expectedRegister.control3             , actualRegister.control3              );
	    CHECK_EQUAL( expectedRegister.guardTimeAndPrescaler, actualRegister.guardTimeAndPrescaler );
	}

	void setup()
	{
		vInitializeTestRegistersToResetValues();
		rccMock   = new PeripheralRccMock;
		rxPinMock = new GpioMock;
		txPinMock = new GpioMock;
		rcc   = static_cast <PeripheralRcc*>( rccMock );
		rxPin = static_cast <Gpio*> (rxPinMock);
		txPin = static_cast <Gpio*> (txPinMock);

	}

	void teardown()
	{
		mock().checkExpectations();
		mock().clear();
		delete rccMock;
		delete rxPinMock;
		delete txPinMock;
		rcc   = nullptr;
		rxPin = nullptr;
		txPin = nullptr;
	}

	uint32_t calculateUsartDiv( uint32_t phbClockInHz,
	                            uint32_t requestedBaudRate,
	                            bool     overSample16Times )
	{
	    uint32_t mantissa;
	    uint32_t  fraction;
	    uint32_t usartDiv;

	    if ( overSample16Times )
	    {
	        mantissa = phbClockInHz / ( 16*requestedBaudRate );
	        fraction = ( phbClockInHz % ( 16*requestedBaudRate ) )*16 ;
            fraction += 15*requestedBaudRate;
            fraction /= 16*requestedBaudRate;
            usartDiv = mantissa*16 +  fraction;
            printf("%X\n",usartDiv);
	    }
        return usartDiv;
	}

	Usart* pInstantiateUsart1_2()
    {
        mock().disable();
        expectedRegister.baudRate = calculateUsartDiv( /* apbClockInHz */      16000000U,
                                                       /* requestedBaudRate */ 115200,
                                                       /* overSample16Times */ true );
        Usart* pUsart = static_cast<Usart*>( new Usart1_2Imp( /* Usart Base address */ &actualRegister,
                                                              /* PeripheralRcc */      rcc,
                                                              /* rxPin */              rxPin,
                                                              /* txPin */              txPin ) );
        mock().enable();
        return pUsart;
    }
};

/*! Check that when Usart1_2 is instantiated:
 *   - The peripheralClock for the selected USART is enabled
 *   - The Rx and Tx pins are set to alternate function AF07.
 *   - The baudrate register is set so that the baudrate is as close
 *     as possible to 115200 with 16000000 APB clock and 16 times oversampling */
TEST( Usart, InstantiateUsart1_2 )
{
    rccMock->expectEnableClock();
    rccMock->expectGetClockFrequencyInHzAndReturn( /* clockFrequency */ 16000000U );
	txPinMock->expectSetToAlternateFunction( Gpio::AF07 );
	rxPinMock->expectSetToAlternateFunction( Gpio::AF07 );
    expectedRegister.baudRate = calculateUsartDiv( /* apbClockInHz */      16000000U,
                                                   /* requestedBaudRate */ 115200,
                                                   /* overSample16Times */ true );

	usart = static_cast<Usart*>( new Usart1_2Imp( /* Usart Base address */ &actualRegister,
	                                              /* PeripheralRcc */      rcc,
	                                              /* rxPin */			   rxPin,
												  /* txPin */			   txPin ) );

	vCheckRegisters();

	delete usart;
}

/*! Check that when the correct data is written to the baudrate register
 *  of Usart1_2 when the baudrate is set to 115200
 *  with 16000000 MHz clock and 16 times oversampling */
TEST( Usart, SetBaud115200ApbClk16OvSample16 )
{
    usart = pInstantiateUsart1_2();

    actualRegister.baudRate = 0;
    expectedRegister.baudRate = calculateUsartDiv( /* apbClockInHz */      16000000U,
                                                   /* requestedBaudRate */ 115200,
                                                   /* overSample16Times */ true );
    rccMock->expectGetClockFrequencyInHzAndReturn( /* clockFrequency */ 16000000U );

    usart->setBaudRate( 115200 );
    vCheckRegisters();

    delete usart;
}
/*! Check that when the baudrate is set on USART1_2, and the peripheral is 16 Mhz
 *   - The
 *   - The Rx and Tx pins are set to alternate function AF07. */
//TEST ( Usart, WriteToUsart1 )
//{
//	expectedRegister.data=0x00000041; //expect to set usart1 to "a"
//	usart = static_cast<Usart*>( new Usart1_2Imp( /* Usart Base address */ &actualRegister,
//												  /* rxPin */			   rxPin,
//												  /* txPin */			   txPin ) );
//	//data = write
//	usart->write('a');
//	CHECK_EQUAL( expectedRegister.data, actualRegister.data );
//	delete usart;
//}


int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}
