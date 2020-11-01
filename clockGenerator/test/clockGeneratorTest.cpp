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
 * clockGeneratorTest.cpp
 *
 *  Created on: 26-Jul 2020
 *      Author: jeppa
 */

#include <cstring>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "clockGeneratorImp.hpp"

TEST_GROUP( ClockGenerator)
{
	typedef struct
	{
		volatile uint32_t clockControl;                  /* Base address + 0x0 */
		volatile uint32_t pllConfiguration;              /* Base address + 0x4 */
		volatile uint32_t clockConfiguration;            /* Base address + 0x8 */
		volatile uint32_t interrupt;                     /* Base address + 0xC */
		volatile uint32_t ahb1PeripheralReset;           /* Base address + 0x10 */
		volatile uint32_t ahb2PeripheralReset;           /* Base address + 0x14 */
		volatile uint32_t notUsed1;                      /* Base address + 0x18 */
		volatile uint32_t notUsed2;                      /* Base address + 0x1C */
		volatile uint32_t apb1PeripheralReset;           /* Base address + 0x20 */
		volatile uint32_t apb2PeripheralReset;           /* Base address + 0x24 */
		volatile uint32_t notUsed3;                      /* Base address + 0x28 */
		volatile uint32_t notUsed4;                      /* Base address + 0x2C */
		volatile uint32_t ahb1ClockEnable;               /* Base address + 0x30 */
		volatile uint32_t ahb2ClockEnable;               /* Base address + 0x34 */
		volatile uint32_t notUsed5;                      /* Base address + 0x38 */
		volatile uint32_t notUsed6;                      /* Base address + 0x3C */
		volatile uint32_t apb1ClockEnable;               /* Base address + 0x40 */
		volatile uint32_t apb2ClockEnable;               /* Base address + 0x44 */
		volatile uint32_t notUsed7;                      /* Base address + 0x48 */
		volatile uint32_t notUsed8;                      /* Base address + 0x4C */
		volatile uint32_t ahb1LowPowerClockEnable;       /* Base address + 0x50 */
		volatile uint32_t ahb2LowPowerClockEnable;       /* Base address + 0x54 */
		volatile uint32_t notUsed9;                      /* Base address + 0x58 */
		volatile uint32_t notUsed10;                     /* Base address + 0x5C */
		volatile uint32_t apb1LowPowerClockEnable;       /* Base address + 0x60 */
		volatile uint32_t apb2LowPowerClockEnable;       /* Base address + 0x64 */
		volatile uint32_t notUsed11;                     /* Base address + 0x68 */
		volatile uint32_t notUsed12;                     /* Base address + 0x6C */
		volatile uint32_t backupDomainControl;           /* Base address + 0x70 */
		volatile uint32_t controlAndStatus;              /* Base address + 0x74 */
		volatile uint32_t notUsed13;                     /* Base address + 0x78 */
		volatile uint32_t notUsed14;                     /* Base address + 0x7C */
		volatile uint32_t spreadSpectrumClockGeneration; /* Base address + 0x80 */
		volatile uint32_t pllI2sControl;                 /* Base address + 0x84 */
		volatile uint32_t dedicatedClocksConfiguration;  /* Base address + 0x8C */
	} clockRegisterType;

	const clockRegisterType resetRegister =
	{ 0x00000083, /* clockControl Reset value - assuming that HSI clock is ready when the SW starts to execute */
	  0x24003010, /* pllConfiguration Reset value */
      0x00000000, /* clockConfiguration Reset value */
      0x00000000, /* interrupt Reset value */
      0x00000000, /* ahb1PeripheralReset Reset value */
      0x00000000, /* ahb2PeripheralReset Reset value */
      0x00000000, /* notUsed1 */
      0x00000000, /* notUsed2 */
      0x00000000, /* apb1PeripheralReset Reset value */
      0x00000000, /* apb2PeripheralReset Reset value */
      0x00000000, /* notUsed3 */
      0x00000000, /* notUsed4 */
      0x00000000, /* ahb1ClockEnable Reset value */
      0x00000000, /* ahb2ClockEnable Reset value */
      0x00000000, /* notUsed5 */
      0x00000000, /* notUsed6 */
      0x00000000, /* apb1ClockEnable Reset value */
      0x00000000, /* apb2ClockEnable Reset value */
      0x00000000, /* notUsed7 */
      0x00000000, /* notUsed8 */
      0x0061900F, /* ahb1LowPowerClockEnable Reset value */
      0x00000080, /* ahb2LowPowerClockEnable Reset value */
      0x00000000, /* notUsed9 */
      0x00000000, /* notUsed10 */
      0x10E2C80F, /* apb1LowPowerClockEnable Reset value */
      0x00077930, /* apb2LowPowerClockEnable Reset value */
      0x00000000, /* notUsed11 */
      0x00000000, /* notUsed12 */
      0x00000000, /* backupDomainControl Reset value */
      0x0E000000, /* controlAndStatus */
      0x00000000, /* notUsed13 */
      0x00000000, /* notUsed14 */
      0x00000000, /* spreadSpectrumClockGeneration Reset value */
      0x24003000, /* pllI2sControl Reset value */
      0x00000000, /* dedicatedClocksConfiguration Reset value */
	};

	clockRegisterType expectedRegister;
	clockRegisterType actualRegister;

	ClockGenerator* clockGenerator;
	PeripheralRcc* peripheralRcc;

	void vInitializeTestRegistersToResetValues()
	{
		memcpy( &expectedRegister, &resetRegister, sizeof( clockRegisterType ) );
		memcpy( &actualRegister, &resetRegister, sizeof( clockRegisterType ) );
	}

	void setup()
	{
		vInitializeTestRegistersToResetValues();
	}

	void teardown()
	{
		mock().checkExpectations();
		mock().clear();
	}
};

/*! Check that when ClockeneratorHsi is instantiated and the HSIRDY flag is set by HW
 *  no Assert is called and the ClockControl register is kept at the reset value
 */
TEST( ClockGenerator, InstantiateHsi )
{
	clockGenerator = dynamic_cast<ClockGenerator*>( new ClockGeneratorHsiImp( /* RCC Base address */ &actualRegister ) );

	CHECK_EQUAL( expectedRegister.clockControl, actualRegister.clockControl );

	delete clockGenerator;
}

/*! Check that when ClockeneratorHsi is instantiated and the HSIRDY flag is not set by HW
 *  assert is called and the ClockControl register is kept at the reset value
 */
TEST( ClockGenerator, InstantiateHsiHsiRdyFlagNotSet )
{
	actualRegister.clockControl &= 0xFFFFFFFD; /* Clear the HSIRDY bit */
	expectedRegister.clockControl &= 0xFFFFFFFD;

	mock().expectOneCall("assert");

	clockGenerator = dynamic_cast<ClockGenerator*>( new ClockGeneratorHsiImp( /* RCC Base address */ &actualRegister ) );

	CHECK_EQUAL( expectedRegister.clockControl, actualRegister.clockControl );

	delete clockGenerator;
}
/*! Check that the clock-control register bit HSEON (Bit 16) is set in the
 *  clockControl register following instantiation with HSE clock enabled
 */
//TEST( ClockGenerator, InstantiateHse )
//{
//	expectedRegister.clockControl |= 0x00010000; /* 0000 0000 0000 0001 0000 0000 0000 0000
//	                                                                  |
//	                                                                  +--------------------- Bit 16, HSEON = 1 */
//	ClockGeneratorImp clockGenerator( /* RCC Base address */ &actualRegister,
//			                          /* Clock source */     ClockGeneratorImp::HSE );
//
//	CHECK_EQUAL( expectedRegister.clockControl, actualRegister.clockControl );
//};

/*! Check that when an instance of peripheralClockControl is used to enable the clock for
 *  GPIOA, the PIOA Clock Enable bit in the AHB1ClockEnable register is set
 */
TEST( ClockGenerator, EnableGpioA )
{
	peripheralRcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
			                                                            /* Peripheral Rcc */   PeripheralRccImp::GPIOA ) );
    CHECK_EQUAL( expectedRegister.ahb1ClockEnable, actualRegister.ahb1ClockEnable );

    expectedRegister.ahb1ClockEnable |= 0x00000001; /* GPIOA ClockEnable bit set */

	peripheralRcc->enableClock();

    CHECK_EQUAL( expectedRegister.ahb1ClockEnable, actualRegister.ahb1ClockEnable );

    delete peripheralRcc;
}

int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}
