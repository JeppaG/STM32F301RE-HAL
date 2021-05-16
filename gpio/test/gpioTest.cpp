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
 * gpioTest.cpp
 *
 *  Created on: 14 Sep 2020
 *      Author: jeppa
 */

#include <cstring>

#include "clockGenerator.hpp"
#include "gpioImp.hpp"
#include "clockGeneratorMock.hpp"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"

TEST_GROUP( Gpio )
{
	typedef struct
	{
		volatile uint32_t mode;              /* Base address + 0x0 */
		volatile uint32_t outputType;        /* Base address + 0x4 */
		volatile uint32_t outputSpeed;       /* Base address + 0x8 */
		volatile uint32_t pullUpDown;        /* Base address + 0xC */
		volatile uint32_t inputData;         /* Base address + 0x10 */
		volatile uint32_t outputData;        /* Base address + 0x14 */
		volatile uint32_t bitSetReset;       /* Base address + 0x18 */
		volatile uint32_t configurationLock; /* Base address + 0x1C */
		volatile uint32_t alternateFunctionLow; /* Base address + 0x20 */
		volatile uint32_t alternateFunctionHigh; /* Base address + 0x24 */
	} gpioRegisterType;

	const gpioRegisterType resetRegister =
	{
		0x00000000, /* mode Reset value except for GPIOA and GPIOB */
	    0x00000000, /* outputType Reset value */
        0x00000000, /* outputSpeed Reset value, except for GPIOA and GPIOB */
        0x00000000, /* pullUpDown Reset value, except for GPIOA and GPIOB */
		0x00000000, /* inputData Reset value */
		0x00000000, /* outputData Reset value */
		0x00000000, /* bitSetReset Reset value */
		0x00000000, /* configurationLock Reset value */
		0x00000000, /* alternateFunctionLow Reset value */
		0x00000000, /* alternateFunctionHigh Reset value */
	};

	const gpioRegisterType resetRegisterGpioA =
	{
		0x0C000000, /* mode Reset value for GPIOA */
	    0x00000000, /* outputType Reset value */
        0x0C000000, /* outputSpeed Reset value for GPIOA */
        0x64000000, /* pullUpDown Reset value for GPIOA */
		0x00000000, /* inputData Reset value */
		0x00000000, /* outputData Reset value */
		0x00000000, /* bitSetReset Reset value */
		0x00000000, /* configurationLock Reset value */
		0x00000000, /* alternateFunctionLow Reset value */
		0x00000000, /* alternateFunctionHigh Reset value */
	};

	const gpioRegisterType resetRegisterGpioB =
	{
		0x00000280, /* mode Reset value for GPIOB */
	    0x00000000, /* outputType Reset value */
        0x00000C00, /* outputSpeed Reset value for GPIOB */
        0x00000100, /* pullUpDown Reset value for GPIOB */
		0x00000000, /* inputData Reset value */
		0x00000000, /* outputData Reset value */
		0x00000000, /* bitSetReset Reset value */
		0x00000000, /* configurationLock Reset value */
		0x00000000, /* alternateFunctionLow Reset value */
		0x00000000, /* alternateFunctionHigh Reset value */
	};

	gpioRegisterType expectedRegister;
	gpioRegisterType actualRegister;

	PeripheralRcc*     rcc;
	PeripheralRccMock* rccMock;

	void vInitializeTestRegistersToGpioAResetValues()
	{
		memcpy( &expectedRegister, &resetRegisterGpioA, sizeof( gpioRegisterType ) );
		memcpy( &actualRegister, &resetRegisterGpioA, sizeof( gpioRegisterType ) );
	}

	void vInitializeTestRegistersToGpioBResetValues()
	{
		memcpy( &expectedRegister, &resetRegisterGpioB, sizeof( gpioRegisterType ) );
		memcpy( &actualRegister, &resetRegisterGpioB, sizeof( gpioRegisterType ) );
	}

	void vInitializeTestRegistersToResetValues()
	{
		memcpy( &expectedRegister, &resetRegister, sizeof( gpioRegisterType ) );
		memcpy( &actualRegister, &resetRegister, sizeof( gpioRegisterType ) );
	}

	void vCheckRegisters()
	{
        CHECK_EQUAL( expectedRegister.mode                 , actualRegister.mode                  );
        CHECK_EQUAL( expectedRegister.outputType           , actualRegister.outputType            );
        CHECK_EQUAL( expectedRegister.outputSpeed          , actualRegister.outputSpeed           );
        CHECK_EQUAL( expectedRegister.pullUpDown           , actualRegister.pullUpDown            );
        CHECK_EQUAL( expectedRegister.inputData            , actualRegister.inputData             );
        CHECK_EQUAL( expectedRegister.outputData           , actualRegister.outputData            );
        CHECK_EQUAL( expectedRegister.bitSetReset          , actualRegister.bitSetReset           );
        CHECK_EQUAL( expectedRegister.configurationLock    , actualRegister.configurationLock     );
        CHECK_EQUAL( expectedRegister.alternateFunctionLow , actualRegister.alternateFunctionLow  );
        CHECK_EQUAL( expectedRegister.alternateFunctionHigh, actualRegister.alternateFunctionHigh );

	}

	Gpio* instantiateGpioA( uint32_t pin)
	{
	    mock().disable();
	    vInitializeTestRegistersToGpioAResetValues();
	    Gpio* gpioA = static_cast<Gpio*>( new GpioImp(  /* GPIOA Base address */ &actualRegister,
	                                                    /* Peripheral RCC   */   rcc,
	                                                    /* Pin              */   pin ) );
	    mock().enable();
	    return gpioA;
	}

	void setup()
	{
		vInitializeTestRegistersToResetValues();
		rccMock = new PeripheralRccMock();
		rcc = static_cast<PeripheralRcc*>( rccMock );
	}

	void teardown()
	{
	    rcc = nullptr;
		delete rccMock;
		mock().checkExpectations();
		mock().clear();
	}
};

/*! Check that when GPIOA pin 5 is instantiated the peripheral clock is enabled for GPIOA.
 */
TEST( Gpio, InstantiatGpioA5 )
{
	vInitializeTestRegistersToGpioAResetValues();

	rccMock->expectEnableClock();

	Gpio* gpioA5 = static_cast<Gpio*>( new GpioImp(  /* GPIOA Base address */ &actualRegister,
                                                     /* Peripheral RCC     */ rcc,
                                                     /* Pin Number         */ Gpio::pin5 ) );

	delete gpioA5;
}
/*! Check that when GPIOA pin 5 is instantiated and set as digital output,
 *  Pin 5 is set to an output, and the pin output is cleared.
 */
TEST( Gpio, SetGpioA5ToDigitalOutput )
{
    Gpio* gpioA5 = instantiateGpioA( /* pinNumber */ Gpio::pin5);

    expectedRegister.mode = 0x0C000400;
    expectedRegister.bitSetReset = 0x00200000;

    gpioA5->setToDigitalOutput();

    vCheckRegisters();

    delete gpioA5;
}

/*! Check that when GPIOA pin 5 is set as a digital output and the output is set
 *   gpioA pin 5 is set
 *
 */
TEST( Gpio, SetGpio5 )
{
    Gpio* gpioA5 = instantiateGpioA( /* pinNumber */ Gpio::pin5);
    gpioA5->setToDigitalOutput();
	actualRegister.bitSetReset = 0x00000000;
    expectedRegister.mode = 0x0C000400;
	expectedRegister.bitSetReset = 0x00000020;

	gpioA5->set();

	vCheckRegisters();

	delete gpioA5;
}

/*! Check that when GPIOA pin 9 is instantiated and set to alternate function AF7,
 *  the pin is set as alternate function and the AF selected is AF7
 *
 */
TEST( Gpio, SetGpioA9AsAf7 )
{
    Gpio* gpioA9 = instantiateGpioA( /* pinNumber */ Gpio::pin9 );

    expectedRegister.mode = 0x0C080000;
    expectedRegister.alternateFunctionHigh = 0x00000070;

    gpioA9->setToAlternateFunction( /* alternateFunction */ Gpio::AF07 );

    vCheckRegisters();

	delete gpioA9;
}

/*! Check that when GPIOA pin 10 is instantiated and set to alternate function AF7,
 *  the pin is set as alternate function and the AF selected is AF7
 *
 */
TEST( Gpio, SetGpioA10AsAf7 )
{
    Gpio* gpioA10 = instantiateGpioA( /* pinNumber */ Gpio::pin10 );

    expectedRegister.mode = 0x0C200000;
    expectedRegister.alternateFunctionHigh = 0x00000700;

    gpioA10->setToAlternateFunction( /* alternateFunction */ Gpio::AF07 );

    vCheckRegisters();

    delete gpioA10;
}

int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}

