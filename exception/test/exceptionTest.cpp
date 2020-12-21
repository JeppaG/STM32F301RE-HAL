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
 * exceptionTest.cpp
 *
 *  Created on: 3 Nov 2020
 *      Author: jeppa
 */

#include <cstring>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "exceptionImp.hpp"

TEST_GROUP( Exception )
{
	typedef struct
	{
		volatile uint32_t interrupt0to31;
		volatile uint32_t interrupt32to63;
		volatile uint32_t interrupt64to95;
		volatile uint32_t interrupt96to127;
		volatile uint32_t interrupt128to159;
		volatile uint32_t interrupt160to191;
		volatile uint32_t interrupt192to223;
		volatile uint32_t interrupt224to239;
	} nvicSingleBitRegisterType;

	typedef struct
	{
		volatile uint32_t auxiliaryControl;
		volatile uint32_t cpuId;
		volatile uint32_t intrruptCtontrolAndState;
		volatile uint32_t vectorTableOffset;
		volatile uint32_t applicationInterruptAndResetControl;
		volatile uint32_t systemControl;
		volatile uint32_t configurationAndControl;
		volatile uint8_t  memoryManagementFaultPriority;
		volatile uint8_t  busFaultPriority;
		volatile uint8_t  usageFaultPriority;
		volatile uint8_t  reserved1;
		volatile uint8_t  reserved2;
		volatile uint8_t  reserved3;
		volatile uint8_t  reserved4;
		volatile uint8_t  svCallPriority;
		volatile uint8_t  reserved5;
		volatile uint8_t  reserved6;
		volatile uint8_t  pendSvPriority;
		volatile uint8_t  sysTickPriority;
		volatile uint32_t systemHandlerControlAndState;
		volatile uint32_t configurableFaultStatus;
		volatile uint32_t hardFaultStatus;
		volatile uint32_t addressOfMemoryManagementFault;
		volatile uint32_t addressOfBusFault;
		volatile uint32_t auxiliaryFaultStatus;
	} scbRegisterType;

	typedef struct
	{
		volatile uint32_t controlAndStatus;              /* Base address + 0x0 */
		volatile uint32_t reloadValue;                   /* Base address + 0x4 */
		volatile uint32_t currentValue;                  /* Base address + 0x8 */
		volatile uint32_t calibrationValue;              /* Base address + 0xC */
	} tickTimerRegisterType;

	scbRegisterType const scbDefaultRegister =
	{
	    /* auxiliaryControl                    */ 0x00000000,
	    /* cpuId                               */ 0x410FC241,
	    /* intrruptCtontrolAndState            */ 0x00000000,
	    /* vectorTableOffset                   */ 0x00000000,
	    /* applicationInterruptAndResetControl */ 0xFA050000,
	    /* systemControl                       */ 0x00000000,
	    /* configurationAndControl             */ 0x00000200,
        /* memoryManagementFaultPriority       */ 0x00,
		/* busFaultPriority                    */ 0x00,
		/* usageFaultPriority                  */ 0x00,
		/* reserved1                           */ 0x00,
		/* reserved2                           */ 0x00,
		/* reserved3                           */ 0x00,
		/* reserved4                           */ 0x00,
		/* svCallPriority                      */ 0x00,
		/* reserved5                           */ 0x00,
		/* reserved6                           */ 0x00,
		/* pendSvPriority                      */ 0x00,
		/* sysTickPriority                     */ 0x00,
	    /* systemHndlerControlAndState         */ 0x00000000,
	    /* configurableFaultStatus             */ 0x00000000,
	    /* hardFaultStatus                     */ 0x00000000,
	    /* addressOfMemoryManagementFault      */ 0x00000000,
	    /* addressOfBusFault                   */ 0x00000000,
	    /* auxiliaryFaultStatus                */ 0x00000000
	};

	const tickTimerRegisterType resetRegister =
	{
		0x00000000, /* controlAndStatus Reset value */
	    0x00000000, /* reloadValue Reset value */
        0x00000000, /* currentValue Reset value */
        10500,      /* calibrationValue Reset value, gives 1 ms tick with AHB_CLK = 84 MHZ -> AHB_CLK/8 = 10,5 MHz */
	};

	nvicSingleBitRegisterType setEnableExpected;
	nvicSingleBitRegisterType setEnableActual;

	nvicSingleBitRegisterType clearEnableExpected;
	nvicSingleBitRegisterType clearEnableActual;

	nvicSingleBitRegisterType setPendingExpected;
	nvicSingleBitRegisterType setPendingActual;

	nvicSingleBitRegisterType clearPendingExpected;
	nvicSingleBitRegisterType clearPendingActual;

	nvicSingleBitRegisterType active;

	scbRegisterType scbExpected;
	scbRegisterType scbActual;

	uint8_t volatile priorityExpected[240];
	uint8_t volatile priorityActual[240];

	volatile uint32_t softwareTriggerExpected;
	volatile uint32_t softwareTriggerActual;

	tickTimerRegisterType expectedTickTimerRegister;
	tickTimerRegisterType actualTickTimerRegister;

	void initializeTestRegistersToResetValues()
	{
		memset( &setEnableExpected, 0, sizeof( nvicSingleBitRegisterType ) );
		memset( &setEnableActual, 0, sizeof( nvicSingleBitRegisterType ) );

		memset( &clearEnableExpected, 0, sizeof( nvicSingleBitRegisterType ) );
		memset( &clearEnableActual, 0, sizeof( nvicSingleBitRegisterType ) );

		memset( &setPendingExpected, 0, sizeof( nvicSingleBitRegisterType ) );
		memset( &setPendingActual, 0, sizeof( nvicSingleBitRegisterType ) );

		memset( &clearPendingExpected, 0, sizeof( nvicSingleBitRegisterType ) );
		memset( &clearPendingActual, 0, sizeof( nvicSingleBitRegisterType ) );

		memset( &active, 0, sizeof( nvicSingleBitRegisterType ) );

		for ( int i = 0; i < 240; i++ )
		{
			priorityExpected[i] = 0;
		    priorityActual[i] = 0;
		}

		softwareTriggerExpected = 0U;
		softwareTriggerActual = 0U;

		memcpy( &scbExpected, &scbDefaultRegister, sizeof( scbRegisterType ) );
		memcpy( &scbActual, &scbDefaultRegister, sizeof( scbRegisterType ) );

		memcpy( &expectedTickTimerRegister, &resetRegister, sizeof( tickTimerRegisterType ) );
		memcpy( &actualTickTimerRegister, &resetRegister, sizeof( tickTimerRegisterType ) );
}

	void setup()
	{
		initializeTestRegistersToResetValues();
	}

	void teardown()
	{

	}
};

/*!
 * Test that when a sysTickTimer exception object is instantiated, and the priority is
 * set. The set priority shall be copied to the sysTickPriority register.
 */
TEST( Exception, initSysTickTimerPriority )
{
	Exception* sysTickException = dynamic_cast<Exception*>( new SysTickHandlerImp( &scbActual,
			                                                                       &actualTickTimerRegister ) );

	scbExpected.sysTickPriority = 255;
	sysTickException->setPriority( 255 );
	CHECK_EQUAL( scbExpected.sysTickPriority, scbActual.sysTickPriority );

	delete sysTickException;
}

/*!
 * Test that when a sysTickTimer exception object is instantiated, and the exception is
 * enabled, the TICK INT enable bit in the SysTick control and status register is set.
 */
TEST( Exception, initSysTickTimerEnable )
{
	Exception* sysTickException = dynamic_cast<Exception*>( new SysTickHandlerImp( &scbActual,
            																	   &actualTickTimerRegister ) );

	expectedTickTimerRegister.controlAndStatus = 0x00000002;
	sysTickException->enable();
	CHECK_EQUAL( expectedTickTimerRegister.controlAndStatus, actualTickTimerRegister.controlAndStatus );

	delete sysTickException;
}

void Exception::enableGlobal()
{
	mock().actualCall( "Exception::enableGlobal" );
}

void Exception::disableGlobal()
{
	mock().actualCall( "Exception::disableGlobal" );
}

int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}

