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

	void vCheckRegisters ()
	{
        CHECK_EQUAL( expectedRegister.clockControl                  , actualRegister.clockControl                  );
        CHECK_EQUAL( expectedRegister.pllConfiguration              , actualRegister.pllConfiguration              );
        CHECK_EQUAL( expectedRegister.clockConfiguration            , actualRegister.clockConfiguration            );
        CHECK_EQUAL( expectedRegister.interrupt                     , actualRegister.interrupt                     );
        CHECK_EQUAL( expectedRegister.ahb1PeripheralReset           , actualRegister.ahb1PeripheralReset           );
        CHECK_EQUAL( expectedRegister.ahb2PeripheralReset           , actualRegister.ahb2PeripheralReset           );
        CHECK_EQUAL( expectedRegister.notUsed1                      , actualRegister.notUsed1                      );
        CHECK_EQUAL( expectedRegister.notUsed2                      , actualRegister.notUsed2                      );
        CHECK_EQUAL( expectedRegister.apb1PeripheralReset           , actualRegister.apb1PeripheralReset           );
        CHECK_EQUAL( expectedRegister.apb2PeripheralReset           , actualRegister.apb2PeripheralReset           );
        CHECK_EQUAL( expectedRegister.notUsed3                      , actualRegister.notUsed3                      );
        CHECK_EQUAL( expectedRegister.notUsed4                      , actualRegister.notUsed4                      );
        CHECK_EQUAL( expectedRegister.ahb1ClockEnable               , actualRegister.ahb1ClockEnable               );
        CHECK_EQUAL( expectedRegister.ahb2ClockEnable               , actualRegister.ahb2ClockEnable               );
        CHECK_EQUAL( expectedRegister.notUsed5                      , actualRegister.notUsed5                      );
        CHECK_EQUAL( expectedRegister.notUsed6                      , actualRegister.notUsed6                      );
        CHECK_EQUAL( expectedRegister.apb1ClockEnable               , actualRegister.apb1ClockEnable               );
        CHECK_EQUAL( expectedRegister.apb2ClockEnable               , actualRegister.apb2ClockEnable               );
        CHECK_EQUAL( expectedRegister.notUsed7                      , actualRegister.notUsed7                      );
        CHECK_EQUAL( expectedRegister.notUsed8                      , actualRegister.notUsed8                      );
        CHECK_EQUAL( expectedRegister.ahb1LowPowerClockEnable       , actualRegister.ahb1LowPowerClockEnable       );
        CHECK_EQUAL( expectedRegister.ahb2LowPowerClockEnable       , actualRegister.ahb2LowPowerClockEnable       );
        CHECK_EQUAL( expectedRegister.notUsed9                      , actualRegister.notUsed9                      );
        CHECK_EQUAL( expectedRegister.notUsed10                     , actualRegister.notUsed10                     );
        CHECK_EQUAL( expectedRegister.apb1LowPowerClockEnable       , actualRegister.apb1LowPowerClockEnable       );
        CHECK_EQUAL( expectedRegister.apb2LowPowerClockEnable       , actualRegister.apb2LowPowerClockEnable       );
        CHECK_EQUAL( expectedRegister.notUsed11                     , actualRegister.notUsed11                     );
        CHECK_EQUAL( expectedRegister.notUsed12                     , actualRegister.notUsed12                     );
        CHECK_EQUAL( expectedRegister.backupDomainControl           , actualRegister.backupDomainControl           );
        CHECK_EQUAL( expectedRegister.controlAndStatus              , actualRegister.controlAndStatus              );
        CHECK_EQUAL( expectedRegister.notUsed13                     , actualRegister.notUsed13                     );
        CHECK_EQUAL( expectedRegister.notUsed14                     , actualRegister.notUsed14                     );
        CHECK_EQUAL( expectedRegister.spreadSpectrumClockGeneration , actualRegister.spreadSpectrumClockGeneration );
        CHECK_EQUAL( expectedRegister.pllI2sControl                 , actualRegister.pllI2sControl                 );
        CHECK_EQUAL( expectedRegister.dedicatedClocksConfiguration  , actualRegister.dedicatedClocksConfiguration  );
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

	vCheckRegisters();

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

	vCheckRegisters();

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

	vCheckRegisters();

    delete peripheralRcc;
}

/*! Check that when an instance of peripheralClockControl is used to enable the clock for
 *  USART1, the USART1 Clock Enable bit in the APB2ClockEnable register is set
 */
TEST( ClockGenerator, EnableUsart1 )
{
    peripheralRcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                        /* Peripheral Rcc */   PeripheralRccImp::USART1 ) );
    CHECK_EQUAL( expectedRegister.apb2ClockEnable, actualRegister.apb2ClockEnable );

    expectedRegister.apb2ClockEnable |= 0x00000010; /* USART1 ClockEnable bit set */

    peripheralRcc->enableClock();

    vCheckRegisters();

    delete peripheralRcc;
}

/*! Check that when an instance of peripheralClockControl is used to enable the clock for
 *  USART2, the USART2 Clock Enable bit in the APB1ClockEnable register is set
 */
TEST( ClockGenerator, EnableUsart2 )
{
    peripheralRcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                        /* Peripheral Rcc */   PeripheralRccImp::USART2 ) );
    CHECK_EQUAL( expectedRegister.apb1ClockEnable, actualRegister.apb1ClockEnable );

    expectedRegister.apb1ClockEnable |= 0x00020000; /* USART2 ClockEnable bit set */

    peripheralRcc->enableClock();

    vCheckRegisters();

    delete peripheralRcc;
}

/*! Check that when an instance of peripheralClockControl is used to enable the clock for
 *  DMA1, the DMA1 Clock Enable bit in the AHB1ClockEnable register is set
 */
TEST( ClockGenerator, EnableDma1 )
{
    peripheralRcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                        /* Peripheral Rcc */   PeripheralRccImp::DMA1 ) );
    CHECK_EQUAL( expectedRegister.ahb1ClockEnable, actualRegister.ahb1ClockEnable );

    expectedRegister.ahb1ClockEnable |= 0x00200000; /* DMA1 ClockEnable bit set */

    peripheralRcc->enableClock();

    vCheckRegisters();

    delete peripheralRcc;
}

/*! Check that when an instance of peripheralClockControl is used to enable the clock for
 *  DMA2, the DMA2 Clock Enable bit in the AHB1ClockEnable register is set
 */
TEST( ClockGenerator, EnableDma2 )
{
    peripheralRcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                        /* Peripheral Rcc */   PeripheralRccImp::DMA2 ) );
    CHECK_EQUAL( expectedRegister.ahb1ClockEnable, actualRegister.ahb1ClockEnable );

    expectedRegister.ahb1ClockEnable |= 0x00400000; /* DMA2 ClockEnable bit set */

    peripheralRcc->enableClock();

    vCheckRegisters();

    delete peripheralRcc;
}

/*! Check that when an instance of peripheralClockControl is used to enable the clock for
 *  GPIOA and then an instance of peripheralClockControl is used to enable the clock for DMA2,
 *  the DMA2 Clock Enable bit in AHB1ClockEnable register is set while the GPIOA Clock Enable
 *  bit remains set.
 */
TEST( ClockGenerator, EnableGpioAndThenDma2 )
{
    peripheralRcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                        /* Peripheral Rcc */   PeripheralRccImp::GPIOA ) );

    PeripheralRcc* dma2Rcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                                  /* Peripheras Rcc */ PeripheralRccImp::DMA2 ) );

    expectedRegister.ahb1ClockEnable |= 0x00400001; /* DMA2 and GPIOA ClockEnable bit set */

    peripheralRcc->enableClock();
    dma2Rcc->enableClock();

    vCheckRegisters();

    delete peripheralRcc;
    delete dma2Rcc;
}

/*! Check that when an instance of peripheralClockControl is used to enable the clock for
 *  GPIOA and then an instance of peripheralClockControl is used to enable the clock for DMA1,
 *  the DMA1 Clock Enable bit in AHB1ClockEnable register is set while the GPIOA Clock Enable
 *  bit remains set.
 */
TEST( ClockGenerator, EnableGpioAndThenDma1 )
{
    peripheralRcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                        /* Peripheral Rcc */   PeripheralRccImp::GPIOA ) );

    PeripheralRcc* dma1Rcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                                  /* Peripheras Rcc */ PeripheralRccImp::DMA1 ) );

    expectedRegister.ahb1ClockEnable |= 0x00200001; /* DMA1 and GPIOA ClockEnable bit set */

    peripheralRcc->enableClock();
    dma1Rcc->enableClock();

    vCheckRegisters();

    delete peripheralRcc;
    delete dma1Rcc;
}

/*! Check that when an instance of peripheralClockControl is used to enable the clock for
 *  DMA2 and then an instance of peripheralClockControl is used to enable the clock for GPIOA,
 *  the GPIOA Clock Enable bit in AHB1ClockEnable register is set while the DMA 2 Clock Enable
 *  bit remains set.
 */
TEST( ClockGenerator, EnableDma2AndThenGpioA )
{
    peripheralRcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                        /* Peripheral Rcc */   PeripheralRccImp::DMA2 ) );

    PeripheralRcc* gpioaRcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                                  /* Peripheras Rcc */ PeripheralRccImp::GPIOA ) );

    expectedRegister.ahb1ClockEnable |= 0x00400001; /* DMA2 and GPIOA ClockEnable bit set */

    peripheralRcc->enableClock();
    gpioaRcc->enableClock();

    vCheckRegisters();

    delete peripheralRcc;
    delete gpioaRcc;
}

/*! Check that it is possible to read out the correct APB1 clock speed when the HSI clock is used and
 *  there is no division of neither AHB clock or APB1 clock, Ie, APB2Clk = AHBClk = SysClk = 16000000 Hz
 *  when peripheralRcc is instantiated for USART2 (which uses APB1)
 */
TEST( ClockGenerator, GetApb1ClkWhenEqualToHsiClk )
{
    peripheralRcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                        /* Peripheral Rcc */   PeripheralRccImp::USART2 ) );
    CHECK_EQUAL( 16000000U, peripheralRcc->getClockFrequencyInHz() );
    delete peripheralRcc;
}

/*! Check that it is possible to read out the correct APB2 clock speed when the HSI clock is used and
 *  there is no division of neither AHB clock or APB2 clock, Ie, APB2Clk = AHBClk = SysClk = 16000000 Hz
 *  when peripheralRcc is instantiated for USART1 (which uses APB2)
 */
TEST( ClockGenerator, GetApb2ClkWhenEqualToHsiClk )
{
    peripheralRcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccImp( /* RCC Base address */ &actualRegister,
                                                                        /* Peripheral Rcc */   PeripheralRccImp::USART1 ) );
    CHECK_EQUAL( 16000000U, peripheralRcc->getClockFrequencyInHz() );
    delete peripheralRcc;
}

int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}
