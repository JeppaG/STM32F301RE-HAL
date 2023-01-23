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
#include "dmaImp.hpp"
#include "clockGeneratorMock.hpp"

TEST_GROUP( Dma )
{
    typedef struct
    {
        volatile uint32_t lowInterruptStatus;       /* Base address + 0x0 */
        volatile uint32_t highInterruptStatus;      /* Base address + 0x4 */
        volatile uint32_t lowInterruptFlagClear;    /* Base address + 0x8 */
        volatile uint32_t highInterruptFlagClear;   /* Base address + 0xC */
        volatile uint32_t stream0Configuration;     /* Base address + 0x10 */
        volatile uint32_t stream0NumberOfData;      /* Base address + 0x14 */
        volatile uint32_t stream0PeripheralAddress; /* Base address + 0x18 */
        volatile uint32_t stream0Memory0Address;    /* Base address + 0x1C */
        volatile uint32_t stream0Memory1Address;    /* Base address + 0x20 */
        volatile uint32_t stream0FifoControl   ;    /* Base address + 0x24 */
        volatile uint32_t stream1Configuration;     /* Base address + 0x28 */
        volatile uint32_t stream1NumberOfData;      /* Base address + 0x2C */
        volatile uint32_t stream1PeripheralAddress; /* Base address + 0x30 */
        volatile uint32_t stream1Memory0Address;    /* Base address + 0x34 */
        volatile uint32_t stream1Memory1Address;    /* Base address + 0x38 */
        volatile uint32_t stream1FifoControl   ;    /* Base address + 0x3C */
        volatile uint32_t stream2Configuration;     /* Base address + 0x40 */
        volatile uint32_t stream2NumberOfData;      /* Base address + 0x44 */
        volatile uint32_t stream2PeripheralAddress; /* Base address + 0x48 */
        volatile uint32_t stream2Memory0Address;    /* Base address + 0x4C */
        volatile uint32_t stream2Memory1Address;    /* Base address + 0x50 */
        volatile uint32_t stream2FifoControl   ;    /* Base address + 0x54 */
        volatile uint32_t stream3Configuration;     /* Base address + 0x58 */
        volatile uint32_t stream3NumberOfData;      /* Base address + 0x5C */
        volatile uint32_t stream3PeripheralAddress; /* Base address + 0x60 */
        volatile uint32_t stream3Memory0Address;    /* Base address + 0x64 */
        volatile uint32_t stream3Memory1Address;    /* Base address + 0x68 */
        volatile uint32_t stream3FifoControl   ;    /* Base address + 0x6C */
        volatile uint32_t stream4Configuration;     /* Base address + 0x70 */
        volatile uint32_t stream4NumberOfData;      /* Base address + 0x74 */
        volatile uint32_t stream4PeripheralAddress; /* Base address + 0x78 */
        volatile uint32_t stream4Memory0Address;    /* Base address + 0x7C */
        volatile uint32_t stream4Memory1Address;    /* Base address + 0x80 */
        volatile uint32_t stream4FifoControl   ;    /* Base address + 0x84 */
        volatile uint32_t stream5Configuration;     /* Base address + 0x88 */
        volatile uint32_t stream5NumberOfData;      /* Base address + 0x8C */
        volatile uint32_t stream5PeripheralAddress; /* Base address + 0x90 */
        volatile uint32_t stream5Memory0Address;    /* Base address + 0x94 */
        volatile uint32_t stream5Memory1Address;    /* Base address + 0x98 */
        volatile uint32_t stream5FifoControl   ;    /* Base address + 0x9C */
        volatile uint32_t stream6Configuration;     /* Base address + 0xA0 */
        volatile uint32_t stream6NumberOfData;      /* Base address + 0xA4 */
        volatile uint32_t stream6PeripheralAddress; /* Base address + 0xA8 */
        volatile uint32_t stream6Memory0Address;    /* Base address + 0xAC */
        volatile uint32_t stream6Memory1Address;    /* Base address + 0xB0 */
        volatile uint32_t stream6FifoControl   ;    /* Base address + 0xB4 */
        volatile uint32_t stream7Configuration;     /* Base address + 0xB8 */
        volatile uint32_t stream7NumberOfData;      /* Base address + 0xBC */
        volatile uint32_t stream7PeripheralAddress; /* Base address + 0xC0 */
        volatile uint32_t stream7Memory0Address;    /* Base address + 0xC4 */
        volatile uint32_t stream7Memory1Address;    /* Base address + 0xC8 */
        volatile uint32_t stream7FifoControl   ;    /* Base address + 0xCC */
    } dmaRegisterType;

	const dmaRegisterType resetRegister =
	{
	    0x00000000, /* lowInterruptStatus       */
	    0x00000000, /* highInterruptStatus      */
	    0x00000000, /* lowInterruptFlagClear    */
	    0x00000000, /* highInterruptFlagClear   */
	    0x00000000, /* stream0Configuration     */
	    0x00000000, /* stream0NumberOfData      */
	    0x00000000, /* stream0PeripheralAddress */
	    0x00000000, /* stream0Memory0Address    */
	    0x00000000, /* stream0Memory1Address    */
	    0x00000021, /* stream0FifoControl       */
	    0x00000000, /* stream1Configuration     */
	    0x00000000, /* stream1NumberOfData      */
	    0x00000000, /* stream1PeripheralAddress */
	    0x00000000, /* stream1Memory0Address    */
	    0x00000000, /* stream1Memory1Address    */
	    0x00000021, /* stream1FifoControl       */
	    0x00000000, /* stream2Configuration     */
	    0x00000000, /* stream2NumberOfData      */
	    0x00000000, /* stream2PeripheralAddress */
	    0x00000000, /* stream2Memory0Address    */
	    0x00000000, /* stream2Memory1Address    */
	    0x00000021, /* stream2FifoControl       */
	    0x00000000, /* stream3Configuration     */
	    0x00000000, /* stream3NumberOfData      */
	    0x00000000, /* stream3PeripheralAddress */
	    0x00000000, /* stream3Memory0Address    */
	    0x00000000, /* stream3Memory1Address    */
	    0x00000021, /* stream3FifoControl       */
	    0x00000000, /* stream4Configuration     */
	    0x00000000, /* stream4NumberOfData      */
	    0x00000000, /* stream4PeripheralAddress */
	    0x00000000, /* stream4Memory0Address    */
	    0x00000000, /* stream4Memory1Address    */
	    0x00000021, /* stream4FifoControl       */
	    0x00000000, /* stream5Configuration     */
	    0x00000000, /* stream5NumberOfData      */
	    0x00000000, /* stream5PeripheralAddress */
	    0x00000000, /* stream5Memory0Address    */
	    0x00000000, /* stream5Memory1Address    */
	    0x00000021, /* stream5FifoControl       */
	    0x00000000, /* stream6Configuration     */
	    0x00000000, /* stream6NumberOfData      */
	    0x00000000, /* stream6PeripheralAddress */
	    0x00000000, /* stream6Memory0Address    */
	    0x00000000, /* stream6Memory1Address    */
	    0x00000021, /* stream6FifoControl       */
	    0x00000000, /* stream7Configuration     */
	    0x00000000, /* stream7NumberOfData      */
	    0x00000000, /* stream7PeripheralAddress */
	    0x00000000, /* stream7Memory0Address    */
	    0x00000000, /* stream7Memory1Address    */
	    0x00000021  /* stream7FifoControl       */
	};

	dmaRegisterType expectedRegister;
	dmaRegisterType actualRegister;

	PeripheralRccMock* rccMock;
	PeripheralRcc*     rcc;

	Dma*               dma;

	void vInitializeTestRegistersToResetValues()
	{
		memcpy( &expectedRegister, &resetRegister, sizeof( dmaRegisterType ) );
		memcpy( &actualRegister, &resetRegister, sizeof( dmaRegisterType ) );
	}

	void vCheckRegisters()
	{

	    CHECK_EQUAL( expectedRegister.lowInterruptStatus       , actualRegister.lowInterruptStatus       );
	    CHECK_EQUAL( expectedRegister.highInterruptStatus      , actualRegister.highInterruptStatus      );
	    CHECK_EQUAL( expectedRegister.lowInterruptFlagClear    , actualRegister.lowInterruptFlagClear    );
	    CHECK_EQUAL( expectedRegister.highInterruptFlagClear   , actualRegister.highInterruptFlagClear   );
	    CHECK_EQUAL( expectedRegister.stream0Configuration     , actualRegister.stream0Configuration     );
	    CHECK_EQUAL( expectedRegister.stream0NumberOfData      , actualRegister.stream0NumberOfData      );
	    CHECK_EQUAL( expectedRegister.stream0PeripheralAddress , actualRegister.stream0PeripheralAddress );
	    CHECK_EQUAL( expectedRegister.stream0Memory0Address    , actualRegister.stream0Memory0Address    );
        CHECK_EQUAL( expectedRegister.stream0Memory1Address    , actualRegister.stream0Memory1Address    );
        CHECK_EQUAL( expectedRegister.stream0FifoControl       , actualRegister.stream0FifoControl       );
        CHECK_EQUAL( expectedRegister.stream1Configuration     , actualRegister.stream1Configuration     );
        CHECK_EQUAL( expectedRegister.stream1NumberOfData      , actualRegister.stream1NumberOfData      );
        CHECK_EQUAL( expectedRegister.stream1PeripheralAddress , actualRegister.stream1PeripheralAddress );
        CHECK_EQUAL( expectedRegister.stream1Memory0Address    , actualRegister.stream1Memory0Address    );
        CHECK_EQUAL( expectedRegister.stream1Memory1Address    , actualRegister.stream1Memory1Address    );
        CHECK_EQUAL( expectedRegister.stream1FifoControl       , actualRegister.stream1FifoControl       );
        CHECK_EQUAL( expectedRegister.stream2Configuration     , actualRegister.stream2Configuration     );
        CHECK_EQUAL( expectedRegister.stream2NumberOfData      , actualRegister.stream2NumberOfData      );
        CHECK_EQUAL( expectedRegister.stream2PeripheralAddress , actualRegister.stream2PeripheralAddress );
        CHECK_EQUAL( expectedRegister.stream2Memory0Address    , actualRegister.stream2Memory0Address    );
        CHECK_EQUAL( expectedRegister.stream2Memory1Address    , actualRegister.stream2Memory1Address    );
        CHECK_EQUAL( expectedRegister.stream2FifoControl       , actualRegister.stream2FifoControl       );
        CHECK_EQUAL( expectedRegister.stream3Configuration     , actualRegister.stream3Configuration     );
        CHECK_EQUAL( expectedRegister.stream3NumberOfData      , actualRegister.stream3NumberOfData      );
        CHECK_EQUAL( expectedRegister.stream3PeripheralAddress , actualRegister.stream3PeripheralAddress );
        CHECK_EQUAL( expectedRegister.stream3Memory0Address    , actualRegister.stream3Memory0Address    );
        CHECK_EQUAL( expectedRegister.stream3Memory1Address    , actualRegister.stream3Memory1Address    );
        CHECK_EQUAL( expectedRegister.stream3FifoControl       , actualRegister.stream3FifoControl       );
        CHECK_EQUAL( expectedRegister.stream4Configuration     , actualRegister.stream4Configuration     );
        CHECK_EQUAL( expectedRegister.stream4NumberOfData      , actualRegister.stream4NumberOfData      );
        CHECK_EQUAL( expectedRegister.stream4PeripheralAddress , actualRegister.stream4PeripheralAddress );
        CHECK_EQUAL( expectedRegister.stream4Memory0Address    , actualRegister.stream4Memory0Address    );
        CHECK_EQUAL( expectedRegister.stream4Memory1Address    , actualRegister.stream4Memory1Address    );
        CHECK_EQUAL( expectedRegister.stream4FifoControl       , actualRegister.stream4FifoControl       );
        CHECK_EQUAL( expectedRegister.stream5Configuration     , actualRegister.stream5Configuration     );
        CHECK_EQUAL( expectedRegister.stream5NumberOfData      , actualRegister.stream5NumberOfData      );
        CHECK_EQUAL( expectedRegister.stream5PeripheralAddress , actualRegister.stream5PeripheralAddress );
        CHECK_EQUAL( expectedRegister.stream5Memory0Address    , actualRegister.stream5Memory0Address    );
        CHECK_EQUAL( expectedRegister.stream5Memory1Address    , actualRegister.stream5Memory1Address    );
        CHECK_EQUAL( expectedRegister.stream5FifoControl       , actualRegister.stream5FifoControl       );
        CHECK_EQUAL( expectedRegister.stream6Configuration     , actualRegister.stream6Configuration     );
        CHECK_EQUAL( expectedRegister.stream6NumberOfData      , actualRegister.stream6NumberOfData      );
        CHECK_EQUAL( expectedRegister.stream6PeripheralAddress , actualRegister.stream6PeripheralAddress );
        CHECK_EQUAL( expectedRegister.stream6Memory0Address    , actualRegister.stream6Memory0Address    );
        CHECK_EQUAL( expectedRegister.stream6Memory1Address    , actualRegister.stream6Memory1Address    );
        CHECK_EQUAL( expectedRegister.stream6FifoControl       , actualRegister.stream6FifoControl       );
        CHECK_EQUAL( expectedRegister.stream7Configuration     , actualRegister.stream7Configuration     );
        CHECK_EQUAL( expectedRegister.stream7NumberOfData      , actualRegister.stream7NumberOfData      );
        CHECK_EQUAL( expectedRegister.stream7PeripheralAddress , actualRegister.stream7PeripheralAddress );
        CHECK_EQUAL( expectedRegister.stream7Memory0Address    , actualRegister.stream7Memory0Address    );
        CHECK_EQUAL( expectedRegister.stream7Memory1Address    , actualRegister.stream7Memory1Address    );
        CHECK_EQUAL( expectedRegister.stream7FifoControl       , actualRegister.stream7FifoControl       );
	}

	void setup()
	{
		vInitializeTestRegistersToResetValues();
		rccMock   = new PeripheralRccMock;
		rcc   = static_cast <PeripheralRcc*>( rccMock );
	}

	void teardown()
	{
		mock().checkExpectations();
		mock().clear();
		delete rccMock;
		rcc   = nullptr;
	}

    Dma* pInstantiateDma( uint8_t ui8Stream, uint8_t ui8Channel )
    {
        mock().disable();
        uint32_t ui32StreamConfigReg = static_cast<uint32_t>( ui8Channel ) << 25;
        switch ( ui8Stream )
        {
            case 0: expectedRegister.stream0Configuration = ui32StreamConfigReg; break;
            case 1: expectedRegister.stream1Configuration = ui32StreamConfigReg; break;
            case 2: expectedRegister.stream2Configuration = ui32StreamConfigReg; break;
            case 3: expectedRegister.stream3Configuration = ui32StreamConfigReg; break;
            case 4: expectedRegister.stream4Configuration = ui32StreamConfigReg; break;
            case 5: expectedRegister.stream5Configuration = ui32StreamConfigReg; break;
            case 6: expectedRegister.stream6Configuration = ui32StreamConfigReg; break;
            case 7: expectedRegister.stream7Configuration = ui32StreamConfigReg; break;
            default: break;
        }
        Dma* pDma = static_cast<Dma*>( new DmaImp( /* Dma Controller Base address */ &actualRegister,
                                                   /* PeripheralRcc */               rcc,
                                                   /* ui8Stream */                   ui8Stream,
                                                   /* ui8Channel */                  ui8Channel ) );
        mock().enable();
        return pDma;
    }

    void setBit ( volatile uint32_t &reg, uint8_t bit )
    {
        reg = reg | ( static_cast<uint32_t>( 1 ) << bit );
    }

    void clearBit ( volatile uint32_t &reg, uint8_t bit )
    {
        reg = reg & ~( static_cast<uint32_t>( 1 ) << bit );
    }

};

/*! Check that when DMA stream 6, Channel 4 is instantiated
 *   - The peripheralClock for the selected DMA controller is enabled
 *   - The Channel Select field of stream 6 configuration register is set to Channel 4 */
TEST( Dma, InstantiateDmaStream6 )
{
    rccMock->expectEnableClock();
    expectedRegister.stream6Configuration = 0x08000000;

    dma = static_cast<Dma*>( new DmaImp( /*Dma Controller Base address */ &actualRegister,
	                                     /* PeripheralRcc */              rcc,
	                                     /* Stream */                     6,
	                                     /* Channel */                    4 ) );


	vCheckRegisters();

	delete dma;
}

/*! Check that when DMA stream 7, Channel 4 is instantiated
 *   - The peripheralClock for the selected DMA controller is enabled
 *   - The Channel Select field of stream 7 configuration register is set to Channel 4 */
TEST( Dma, InstantiateDmaStream7 )
{
    rccMock->expectEnableClock();
    expectedRegister.stream7Configuration = 0x08000000;

    dma = static_cast<Dma*>( new DmaImp( /*Dma Controller Base address */ &actualRegister,
                                         /* PeripheralRcc */              rcc,
                                         /* Stream */                     7,
                                         /* Channel */                    4 ) );


    vCheckRegisters();

    delete dma;
}

/*! Check that when an adress is given as peripheral adress for stream 6, this address is written to
 *  stream 6 peripheral adress register.
 */
TEST( Dma, SelectStream6PeripheralAddress)
{
    constexpr uint32_t peripheralAddress = static_cast<uint32_t>( 0xAAAA5555 );

    dma = pInstantiateDma( /* ui8Stream */ 6,
                           /* ui8Channel */ 4 );

    expectedRegister.stream6PeripheralAddress = peripheralAddress;

    dma->setPeripheralAddress ( /* pvAddress */ reinterpret_cast<void*>( peripheralAddress ) );

    vCheckRegisters();

    delete dma;
}

/*! Check that when an adress is given as peripheral adress for stream 7, this address is written to
 *  stream 7 peripheral adress register.
 */
TEST( Dma, SelectStream7PeripheralAddress)
{
    constexpr uint32_t peripheralAddress = static_cast<uint32_t>( 0xAAAA5555 );

    dma = pInstantiateDma( /* ui8Stream */ 7,
                           /* ui8Channel */ 4 );

    expectedRegister.stream7PeripheralAddress = peripheralAddress;

    dma->setPeripheralAddress ( /* pvAddress */ reinterpret_cast<void*>( peripheralAddress ) );;

    vCheckRegisters();

    delete dma;
}

/*! Check that when an address is given as Memory0 adress for stream 6, this address is written to
 *  stream 6 memory 0 address register.
 */
TEST( Dma, SelectStream6Memory0Address)
{
    constexpr uint32_t memory0Address = static_cast<uint32_t>( 0x5555AAAA );

    dma = pInstantiateDma( /* ui8Stream */ 6,
                           /* ui8Channel */ 4 );

    expectedRegister.stream6Memory0Address = memory0Address;

    dma->setMemory0Address ( /* pvAddress */ reinterpret_cast<void*>( memory0Address ) );

    vCheckRegisters();

    delete dma;
}

/*! Check that when an address is given as Memory0 adress for stream 7, this address is written to
 *  stream 7 memory 0 address register.
 */
TEST( Dma, SelectStream7Memory0Address)
{
    constexpr uint32_t memory0Address = static_cast<uint32_t>( 0x5555AAAA );

    dma = pInstantiateDma( /* ui8Stream */  7,
                           /* ui8Channel */ 4 );

    expectedRegister.stream7Memory0Address = memory0Address;

    dma->setMemory0Address ( /* pvAddress */ reinterpret_cast<void*>( memory0Address ) );

    vCheckRegisters();

    delete dma;
}

/*! Check that when a number of data is given for stream 6, the number is written to
 *  stream 6 number of data register.
 */
TEST( Dma, SetStream6NumberOfData )
{
    constexpr uint16_t numberOfData = static_cast<uint16_t>( 19345 );

    dma = pInstantiateDma( /* ui8Stream */ 6,
                           /* ui8Channel */ 4 );

    expectedRegister.stream6NumberOfData = numberOfData;

    dma->setNumberOfData ( /* ui16NumberOfData */ numberOfData );

    vCheckRegisters();

    delete dma;
}

/*! Check that when a number of data is given for stream 7, the number is written to
 *  stream 7 number of data register.
 */
TEST( Dma, SetStream7NumberOfData )
{
    constexpr uint16_t numberOfData = static_cast<uint16_t>( 19345 );

    dma = pInstantiateDma( /* ui8Stream */ 7,
                           /* ui8Channel */ 4 );

    expectedRegister.stream7NumberOfData = numberOfData;

    dma->setNumberOfData ( /* ui16NumberOfData */ numberOfData );

    vCheckRegisters();

    delete dma;
}

/*! Check that when the direction is selected as memory-to-peripheral for stream 6, the direction bits in
 *  stream 6 configuration register is set to 01 - Memory-to-peripheral.
 */
TEST( Dma, SetStream6DirMemoryToPeripheral )
{
    dma = pInstantiateDma( /* ui8Stream */ 6,
                           /* ui8Channel */ 4 );

    setBit ( expectedRegister.stream6Configuration, 6 );
    clearBit ( expectedRegister.stream6Configuration, 7 );

    dma->setStreamDirection ( /* direction */ Dma::memoryToPeripheral );

    vCheckRegisters();

    delete dma;
}

/*! Check that when the direction is selected as memory-to-peripheral for stream 7, the direction bits in
 *  stream 7 configuration register is set to 01 - Memory-to-peripheral.
 */
TEST( Dma, SetStream7DirMemoryToPeripheral )
{
    dma = pInstantiateDma( /* ui8Stream */ 7,
                           /* ui8Channel */ 4 );

    setBit ( expectedRegister.stream7Configuration, 6 );
    clearBit ( expectedRegister.stream7Configuration, 7 );

    dma->setStreamDirection ( /* direction */ Dma::memoryToPeripheral );

    vCheckRegisters();

    delete dma;
}

/*! Check that when memmory incremental mode is set for stream 6, the MINC bit in
 *  stream 6 configuration register is set to 1 - Memory-to-peripheral.
 */
TEST( Dma, SetStream6DirMemoryIncrementalMode )
{
    dma = pInstantiateDma( /* ui8Stream */ 6,
                           /* ui8Channel */ 4 );

    setBit ( expectedRegister.stream6Configuration, 10 );

    dma->setMemoryIncrementalMode();

    vCheckRegisters();

    delete dma;
}

/*! Check that when memmory incremental mode is set for stream 7, the MINC bit in
 *  stream 7 configuration register is set to 1 - Memory-to-peripheral.
 */
TEST( Dma, SetStream7DirMemoryIncrementalMode )
{
    dma = pInstantiateDma( /* ui8Stream */ 7,
                           /* ui8Channel */ 4 );

    setBit ( expectedRegister.stream7Configuration, 10 );

    dma->setMemoryIncrementalMode();

    vCheckRegisters();

    delete dma;
}

/*! Check that when dma stream 6 is enabled:
 *  - Check that 1 is written to the interrupt flag clear bits related to stream 6
 *  - Check that the enable bit in the configuration register for stream 6 is set
 */
TEST( Dma, EnableStream6 )
{
    dma = pInstantiateDma( /* ui8Stream */ 6,
                           /* ui8Channel */ 4 );

    setBit ( expectedRegister.highInterruptFlagClear,16 );
    setBit ( expectedRegister.highInterruptFlagClear,18 );
    setBit ( expectedRegister.highInterruptFlagClear,19 );
    setBit ( expectedRegister.highInterruptFlagClear,20 );
    setBit ( expectedRegister.highInterruptFlagClear,21 );
    setBit ( expectedRegister.stream6Configuration, 0 );

    dma->enable ();

    vCheckRegisters();

    delete dma;
}

/*! Check that when dma stream 7 is enabled:
 *  - Check that 1 is written to the interrupt flag clear bits related to stream 7
 *  - Check that the enable bit in the configuration register for stream 7 is set
 */
TEST( Dma, EnableStream7 )
{
    dma = pInstantiateDma( /* ui8Stream */ 7,
                           /* ui8Channel */ 4 );

    setBit ( expectedRegister.highInterruptFlagClear,22 );
    setBit ( expectedRegister.highInterruptFlagClear,24 );
    setBit ( expectedRegister.highInterruptFlagClear,25 );
    setBit ( expectedRegister.highInterruptFlagClear,26 );
    setBit ( expectedRegister.highInterruptFlagClear,27 );
    setBit ( expectedRegister.stream7Configuration, 0 );

    dma->enable ();

    vCheckRegisters();

    delete dma;
}

int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}
