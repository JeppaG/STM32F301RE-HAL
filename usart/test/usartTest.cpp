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
//            printf("%X\n",usartDiv);
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

/*! Check that when the usart base address is requested, the base address that
 *  was assigned during instantiation is returned */
TEST( Usart, GetBaseAddress )
{
    usart = pInstantiateUsart1_2();

    CHECK_EQUAL( &actualRegister, usart->getBaseAddress() );

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

/*! Check that when the USART is enabled
 *   - The UE bit, bit 13 in CR1 is set
 *   - The TE bit, bit 3 in CR1 is set
 *   - The RE bit, bit 2 in CR1 is set. */
TEST ( Usart, EnableUsart )
{
    usart = pInstantiateUsart1_2();

    expectedRegister.control1 = 0x0000200C;
    usart->enable();

    vCheckRegisters();

    delete usart;
}

/*! Check that when a char is written to the USART, it is put in the data register */
TEST ( Usart, WriteChar )
{
    usart = pInstantiateUsart1_2();

    expectedRegister.data = 0x000000AB;
    usart->write( /* const uint8_t data */ 0xAB );

    vCheckRegisters();

    delete usart;
}

/*! Check that the data register is copied to the return value of the read method
 *  when it is called */
TEST ( Usart, ReadChar )
{
    usart = pInstantiateUsart1_2();

    actualRegister.data = 0x000000AB;

    CHECK_EQUAL( 0xAB, usart->read() );

    delete usart;
}

/*! Check that when DMA Transmit is enabled on the USART bit DMAT is set in the CR3 register */
TEST ( Usart, EnableDmaTransmit )
{
    usart = pInstantiateUsart1_2();

    expectedRegister.control3 = 0x00000080;
    usart->enableDmaTx();

    vCheckRegisters();

    delete usart;
}

/*! Check that when DMA Receive is enabled on the USART bit DMAR is set in the CR3 register */
TEST ( Usart, EnableDmaReceive )
{
    usart = pInstantiateUsart1_2();

    expectedRegister.control3 = 0x00000040;
    usart->enableDmaRx();

    vCheckRegisters();

    delete usart;
}

/*! Check that when DMA Transmit followed by DMA Receive is enabled on the USART
 *  bit DMAT and DMAR is set in the CR3 register */
TEST ( Usart, EnableDmaTransmitAndReceive )
{
    usart = pInstantiateUsart1_2();

    expectedRegister.control3 = 0x000000C0;
    usart->enableDmaTx();
    usart->enableDmaRx();

    vCheckRegisters();

    delete usart;
}

/*! Check that when DMA Receive followed by DMA Transmit is enabled on the USART
 *  bit DMAT and DMAR is set in the CR3 register */
TEST ( Usart, EnableDmaReceiveAndTransmit )
{
    usart = pInstantiateUsart1_2();

    expectedRegister.control3 = 0x000000C0;
    usart->enableDmaRx();
    usart->enableDmaTx();

    vCheckRegisters();

    delete usart;
}

/*! Check that when a manual Transmission Complete is issued the TC bit in the SR register is cleared */
TEST ( Usart, ClearTxComplete )
{
    usart = pInstantiateUsart1_2();

    actualRegister.status = 0x00C00040;
    usart->clearTxComplete();

    vCheckRegisters();

    delete usart;
}

/*! Check that when the the RXNE bit of the USART Status register is
 *  set the newRxData function returns true */
TEST ( Usart, returnNewRxDataTrue )
{
    usart = pInstantiateUsart1_2();

    actualRegister.status = 0x00C00020;
    CHECK_EQUAL( true, usart->newRxData() );



    delete usart;
}

/*! Check that when the the RXNE bit of the USART Status register is
 *  cleared the newRxData function returns false */
TEST ( Usart, returnNewRxDataFalse )
{
    usart = pInstantiateUsart1_2();

    actualRegister.status = 0x00C00000;
    CHECK_EQUAL( false, usart->newRxData() );



    delete usart;
}

int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}
