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

	PeripheralRcc* rcc;

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

	void setup()
	{
		vInitializeTestRegistersToResetValues();
		rcc = dynamic_cast<PeripheralRcc*>( new PeripheralRccMock() );
	}

	void teardown()
	{
		delete rcc;
		mock().checkExpectations();
		mock().clear();
	}
};

/*! Check that when GPIOA pin 5 is instantiated as a digital output,PushPull and Low-speed with polarity ACTIVE_HIGH,
 *  the peripheral clock is enabled for GPIOA. Pin 5 is set to an output with PushPull output stage and the initial
 *  value is set to LOW
 */
TEST( Gpio, InstantiatGpioA1AsOutputPushPullLowspeedActiveLow )
{
	vInitializeTestRegistersToGpioAResetValues();

	mock().expectOneCall( "enableClock" ).onObject( rcc );
	expectedRegister.mode        = 0x0C000400; /* Bit 5 is set as an output */
	expectedRegister.bitSetReset = 0x00200000; /* Reset output bit 5 */

	DigitalOutput* output = dynamic_cast<DigitalOutput*>
	                        ( new DigitalOutputImp( /* GPIOA Base address */ &actualRegister,
			                                        /* Peripheral RCC   */   rcc,
							  		                /* Pin              */   Gpio::pin5,
							  					    /* Output type      */   DigitalOutput::pushPull,
												    /* Speed            */   DigitalOutput::lowSpeed,
												    /* Polarity         */   Gpio::activeHigh ) );

	CHECK_EQUAL( expectedRegister.mode, actualRegister.mode );
	CHECK_EQUAL( expectedRegister.bitSetReset, actualRegister.bitSetReset );

	delete output;
}

/*! Check that when GPIOA pin 5 is instantiated as a digital output that is ACTIVE_HIGH and the output
 *  is set, gpioA pin 5 is set
 *
 */
TEST( Gpio, SetGpio5 )
{
	vInitializeTestRegistersToGpioAResetValues();

	mock().disable();
	DigitalOutput* output = dynamic_cast<DigitalOutput*>
	                        ( new DigitalOutputImp( /* GPIOA Base address */ &actualRegister,
			                                        /* Peripheral RCC   */   rcc,
							  		                /* Pin              */   Gpio::pin5,
							  					    /* Output type      */   DigitalOutput::pushPull,
												    /* Speed            */   DigitalOutput::lowSpeed,
												    /* Polarity         */   Gpio::activeHigh ) );

	actualRegister.bitSetReset = 0x00000000;
	expectedRegister.bitSetReset = 0x00000020;

	output->set();

	CHECK_EQUAL( expectedRegister.bitSetReset, actualRegister.bitSetReset );

	delete output;
}

/*! Check that when GPIOA pin 5 is instantiated as a digital output that is ACTIVE_HIGH and the output
 *  is cleared, gpioA pin 5 is cleared
 *
 */
TEST( Gpio, ClearGpio5 )
{
	vInitializeTestRegistersToGpioAResetValues();

	mock().disable();
	DigitalOutput* output = dynamic_cast<DigitalOutput*>
	                        ( new DigitalOutputImp( /* GPIOA Base address */ &actualRegister,
			                                        /* Peripheral RCC   */   rcc,
							  		                /* Pin              */   Gpio::pin5,
							  					    /* Output type      */   DigitalOutput::pushPull,
												    /* Speed            */   DigitalOutput::lowSpeed,
												    /* Polarity         */   Gpio::activeHigh ) );

	actualRegister.bitSetReset = 0x00000000;
	expectedRegister.bitSetReset = 0x00200000;

	output->clear();

	CHECK_EQUAL( expectedRegister.bitSetReset, actualRegister.bitSetReset );

	delete output;
}

int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}

