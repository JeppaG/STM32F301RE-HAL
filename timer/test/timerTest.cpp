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
 * timerTest.cpp
 *
 *  Created on: 3 Sep 2020
 *      Author: jeppa
 */

#include <cstring>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "sysTickTimerImp.hpp"

TEST_GROUP( SysTickTimer )
{
	typedef struct
	{
		volatile uint32_t controlAndStatus;              /* Base address + 0x0 */
		volatile uint32_t reloadValue;                   /* Base address + 0x4 */
		volatile uint32_t currentValue;                  /* Base address + 0x8 */
		volatile uint32_t calibrationValue;              /* Base address + 0xC */
	} tickTimerRegisterType;

	const tickTimerRegisterType resetRegister =
	{
		0x00000000, /* controlAndStatus Reset value */
	    0x00000000, /* reloadValue Reset value */
        0x00000000, /* currentValue Reset value */
        10500,      /* calibrationValue Reset value, gives 1 ms tick with AHB_CLK = 84 MHZ -> AHB_CLK/8 = 10,5 MHz */
	};

	tickTimerRegisterType expectedRegister;
	tickTimerRegisterType actualRegister;

	Timer* timer;

	void vInitializeTestRegistersToResetValues()
	{
		memcpy( &expectedRegister, &resetRegister, sizeof( tickTimerRegisterType ) );
		memcpy( &actualRegister, &resetRegister, sizeof( tickTimerRegisterType ) );
	}

	void vCheckRegisters()
	{
	    CHECK_EQUAL( expectedRegister.controlAndStatus, actualRegister.controlAndStatus );
	    CHECK_EQUAL( expectedRegister.reloadValue     , actualRegister.reloadValue      );
	    CHECK_EQUAL( expectedRegister.currentValue    , actualRegister.currentValue     );
	    CHECK_EQUAL( expectedRegister.calibrationValue, actualRegister.calibrationValue );
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

/*! Check that when SysTickTimer is instantiated with AHB_CLK set to 16 MHz and using AHB_CLK/8,
 *  The AHB_CLK/8 is selected in HW, Tick Interrupt, is disabled and the counter is enabled.
 *  The reload register is set up so that the tick interval is 1 ms
 */
TEST( SysTickTimer, InstantiateWith16MHzHclkDiv8 )
{
	expectedRegister.controlAndStatus = 0x00000001;
	expectedRegister.reloadValue = 16000000/8000 - 1; /* to get system tick 1 ms with AHB_CLK = 16000000 Hz and using AHB_CLK/8 */

	timer = dynamic_cast<Timer*>( new SysTickTimerImp( /* SysTickTimer Base address */ &actualRegister,
			                                           /* AHB_CLK rate in Hz   */      16000000,
													   /* Clock selection      */      SysTickTimerImp::AHB_CLK_DIV_8 ) );

	vCheckRegisters();

	delete timer;
}

int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}

