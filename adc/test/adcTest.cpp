/*
 * Copyright 2024 JG Mechatronics AB
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
 *  Created on: 26-Feb 2024
 *      Author: jeppa & Viktor
 */

#include <cstring>

#include "../imp/adcImp.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "clockGeneratorMock.hpp"
#include "gpioMock.hpp"

TEST_GROUP( Adc  )
{
    typedef struct
    {
        volatile uint32_t status;                 /* Base address + 0x0 */
        volatile uint32_t control1;               /* Base address + 0x4 */
        volatile uint32_t control2;               /* Base address + 0x8 */
        volatile uint32_t sampleTime1;            /* Base address + 0xC */
        volatile uint32_t sampleTime2;            /* Base address + 0x10 */
        volatile uint32_t injectedChannelOffset1; /* Base address + 0x14 */
        volatile uint32_t injectedChannelOffset2; /* Base address + 0x18 */
        volatile uint32_t injectedChannelOffset3; /* Base address + 0x1C */
        volatile uint32_t injectedChannelOffset4; /* Base address + 0x20 */
        volatile uint32_t watchdogHighThreshold;  /* Base address + 0x24 */
        volatile uint32_t watchdogLowThreshold;   /* Base address + 0x28 */
        volatile uint32_t regularSequence1;       /* Base address + 0x2C */
        volatile uint32_t regularSequence2;       /* Base address + 0x30 */
        volatile uint32_t regularSequence3;       /* Base address + 0x34 */
        volatile uint32_t injectedSequence;       /* Base address + 0x38 */
        volatile uint32_t injectedData1;          /* Base address + 0x3C */
        volatile uint32_t injectedData2;          /* Base address + 0x40 */
        volatile uint32_t injectedData3;          /* Base address + 0x44 */
        volatile uint32_t injectedData4;          /* Base address + 0x48 */
        volatile uint32_t regularData;            /* Base address + 0x4C */
    } adcRegisterType;

    typedef struct
    {
        volatile uint32_t status;                 /* Base address + 0x0 */
        volatile uint32_t control;                /* Base address + 0x4 */
    } adcCommonRegisterType;

	const adcRegisterType resetRegister =
	{
	    0x00C00000, /* status Reset value */
	    0x00000000, /* control1 Reset value */
        0x00000000, /* control2 Reset value */
        0x00000000, /* sampleTime1 Reset value */
        0x00000000, /* sampleTime2 Reset value */
        0x00000000, /* injectedChannelOffset1 Reset value */
        0x00000000, /* injectedChannelOffset2 Reset value */
        0x00000000, /* injectedChannelOffset3 Reset value */
        0x00000000, /* injectedChannelOffset4 Reset value */
        0x00000FFF, /* watchdogHighThreshold Reset value */
        0x00000000, /* watchdogLowThreshold Reset value */
        0x00000000, /* regularSequence1 Reset value */
        0x00000000, /* regularSequence2 Reset value */
        0x00000000, /* regularSequence3 Reset value */
        0x00000000, /* injectedSequence Reset value */
        0x00000000, /* injectedData1 Reset value */
        0x00000000, /* injectedData2 Reset value */
        0x00000000, /* injectedData3 Reset value */
        0x00000000, /* injectedData4 Reset value */
        0x00000000, /* regularData Reset value */
	};

    const adcCommonRegisterType resetCommonRegister =
    {
        0x00000000, /* status Reset value */
        0x00000000, /* control Reset value */
    };

	adcRegisterType       expectedRegister;
	adcCommonRegisterType expectedCommonRegister;
	adcRegisterType       actualRegister;
    adcCommonRegisterType actualCommonRegister;

	PeripheralRccMock* rccMock;
	GpioMock*          pinMock;
	PeripheralRcc*     rcc;
	Gpio* 	           pin;

	Adc*               adc;

	void vInitializeTestRegistersToResetValues()
	{
		memcpy( &expectedRegister, &resetRegister, sizeof( adcRegisterType ) );
        memcpy( &expectedCommonRegister, &resetCommonRegister, sizeof( adcCommonRegisterType ) );
		memcpy( &actualRegister, &resetRegister, sizeof( adcRegisterType ) );
        memcpy( &actualCommonRegister, &resetCommonRegister, sizeof( adcCommonRegisterType ) );
	}

	void vCheckRegisters()
	{
	    CHECK_EQUAL( expectedRegister.status                , actualRegister.status                 );
	    CHECK_EQUAL( expectedRegister.control1              , actualRegister.control1               );
	    CHECK_EQUAL( expectedRegister.control2              , actualRegister.control2               );
	    CHECK_EQUAL( expectedRegister.sampleTime1           , actualRegister.sampleTime1            );
	    CHECK_EQUAL( expectedRegister.sampleTime2           , actualRegister.sampleTime2            );
	    CHECK_EQUAL( expectedRegister.injectedChannelOffset1, actualRegister.injectedChannelOffset1 );
	    CHECK_EQUAL( expectedRegister.injectedChannelOffset2, actualRegister.injectedChannelOffset2 );
        CHECK_EQUAL( expectedRegister.injectedChannelOffset3, actualRegister.injectedChannelOffset3 );
        CHECK_EQUAL( expectedRegister.injectedChannelOffset4, actualRegister.injectedChannelOffset4 );
        CHECK_EQUAL( expectedRegister.watchdogHighThreshold , actualRegister.watchdogHighThreshold  );
        CHECK_EQUAL( expectedRegister.watchdogLowThreshold  , actualRegister.watchdogLowThreshold   );
        CHECK_EQUAL( expectedRegister.regularSequence1      , actualRegister.regularSequence1       );
        CHECK_EQUAL( expectedRegister.regularSequence2      , actualRegister.regularSequence2       );
        CHECK_EQUAL( expectedRegister.regularSequence3      , actualRegister.regularSequence3       );
        CHECK_EQUAL( expectedRegister.injectedSequence      , actualRegister.injectedSequence       );
        CHECK_EQUAL( expectedRegister.injectedData1         , actualRegister.injectedData1          );
        CHECK_EQUAL( expectedRegister.injectedData2         , actualRegister.injectedData2          );
        CHECK_EQUAL( expectedRegister.injectedData3         , actualRegister.injectedData3          );
        CHECK_EQUAL( expectedRegister.injectedData4         , actualRegister.injectedData4          );
        CHECK_EQUAL( expectedRegister.regularData           , actualRegister.regularData            );

        CHECK_EQUAL( expectedCommonRegister.status          , actualCommonRegister.status           );
        CHECK_EQUAL( expectedCommonRegister.control         , actualCommonRegister.control          );
	}

	void setup()
	{
		vInitializeTestRegistersToResetValues();
		rccMock   = new PeripheralRccMock;
		pinMock = new GpioMock;
		rcc   = static_cast <PeripheralRcc*>( rccMock );
		pin = static_cast <Gpio*> (pinMock);

	}

	void teardown()
	{
		mock().checkExpectations();
		mock().clear();
		delete rccMock;
		delete pinMock;
		rcc   = nullptr;
		pin = nullptr;
	}
};

/*! Check that when an ADC is instantiated:
 *   - The peripheralClock for the selected ADC is enabled
 */
TEST( Adc, Instantiate )
{
    rccMock->expectEnableClock();

	adc = static_cast<Adc*>( new AdcImp( /* ADC Base address        */ &actualRegister,
	                                     /* ADC Common Base address */ &actualCommonRegister,
	                                     /* PeripheralRcc */           rcc ) );

	vCheckRegisters();

	delete adc;
}


int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}
