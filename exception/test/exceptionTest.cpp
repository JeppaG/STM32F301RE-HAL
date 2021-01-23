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

	void vCheckNvicRegisters()
	{
        CHECK_EQUAL( setEnableExpected.interrupt0to31      , setEnableActual.interrupt0to31       );
        CHECK_EQUAL( setEnableExpected.interrupt32to63     , setEnableActual.interrupt32to63      );
        CHECK_EQUAL( setEnableExpected.interrupt64to95     , setEnableActual.interrupt64to95      );
        CHECK_EQUAL( setEnableExpected.interrupt96to127    , setEnableActual.interrupt96to127     );
        CHECK_EQUAL( setEnableExpected.interrupt128to159   , setEnableActual.interrupt128to159    );
        CHECK_EQUAL( setEnableExpected.interrupt160to191   , setEnableActual.interrupt160to191    );
        CHECK_EQUAL( setEnableExpected.interrupt192to223   , setEnableActual.interrupt192to223    );
        CHECK_EQUAL( setEnableExpected.interrupt224to239   , setEnableActual.interrupt224to239    );
        CHECK_EQUAL( clearEnableExpected.interrupt0to31    , clearEnableActual.interrupt0to31     );
        CHECK_EQUAL( clearEnableExpected.interrupt32to63   , clearEnableActual.interrupt32to63    );
        CHECK_EQUAL( clearEnableExpected.interrupt64to95   , clearEnableActual.interrupt64to95    );
        CHECK_EQUAL( clearEnableExpected.interrupt96to127  , clearEnableActual.interrupt96to127   );
        CHECK_EQUAL( clearEnableExpected.interrupt128to159 , clearEnableActual.interrupt128to159  );
        CHECK_EQUAL( clearEnableExpected.interrupt160to191 , clearEnableActual.interrupt160to191  );
        CHECK_EQUAL( clearEnableExpected.interrupt192to223 , clearEnableActual.interrupt192to223  );
        CHECK_EQUAL( clearEnableExpected.interrupt224to239 , clearEnableActual.interrupt224to239  );
        CHECK_EQUAL( setPendingExpected.interrupt0to31     , setPendingActual.interrupt0to31      );
        CHECK_EQUAL( setPendingExpected.interrupt32to63    , setPendingActual.interrupt32to63     );
        CHECK_EQUAL( setPendingExpected.interrupt64to95    , setPendingActual.interrupt64to95     );
        CHECK_EQUAL( setPendingExpected.interrupt96to127   , setPendingActual.interrupt96to127    );
        CHECK_EQUAL( setPendingExpected.interrupt128to159  , setPendingActual.interrupt128to159   );
        CHECK_EQUAL( setPendingExpected.interrupt160to191  , setPendingActual.interrupt160to191   );
        CHECK_EQUAL( setPendingExpected.interrupt192to223  , setPendingActual.interrupt192to223   );
        CHECK_EQUAL( setPendingExpected.interrupt224to239  , setPendingActual.interrupt224to239   );
        CHECK_EQUAL( clearPendingExpected.interrupt0to31   , clearPendingActual.interrupt0to31    );
        CHECK_EQUAL( clearPendingExpected.interrupt32to63  , clearPendingActual.interrupt32to63   );
        CHECK_EQUAL( clearPendingExpected.interrupt64to95  , clearPendingActual.interrupt64to95   );
        CHECK_EQUAL( clearPendingExpected.interrupt96to127 , clearPendingActual.interrupt96to127  );
        CHECK_EQUAL( clearPendingExpected.interrupt128to159, clearPendingActual.interrupt128to159 );
        CHECK_EQUAL( clearPendingExpected.interrupt160to191, clearPendingActual.interrupt160to191 );
        CHECK_EQUAL( clearPendingExpected.interrupt192to223, clearPendingActual.interrupt192to223 );
        CHECK_EQUAL( clearPendingExpected.interrupt224to239, clearPendingActual.interrupt224to239 );
        for ( int i = 0; i < 240; i++ )
        {
            CHECK_EQUAL( priorityExpected[i], priorityActual[i] );
        }

	}

	void vCheckScbRegisters()
	{
	    CHECK_EQUAL( scbExpected.auxiliaryControl                   , scbActual.auxiliaryControl                    );
	    CHECK_EQUAL( scbExpected.cpuId                              , scbActual.cpuId                               );
	    CHECK_EQUAL( scbExpected.intrruptCtontrolAndState           , scbActual.intrruptCtontrolAndState            );
	    CHECK_EQUAL( scbExpected.vectorTableOffset                  , scbActual.vectorTableOffset                   );
	    CHECK_EQUAL( scbExpected.applicationInterruptAndResetControl, scbActual.applicationInterruptAndResetControl );
	    CHECK_EQUAL( scbExpected.systemControl                      , scbActual.systemControl                       );
	    CHECK_EQUAL( scbExpected.configurationAndControl            , scbActual.configurationAndControl             );
	    CHECK_EQUAL( scbExpected.memoryManagementFaultPriority      , scbActual.memoryManagementFaultPriority       );
	    CHECK_EQUAL( scbExpected.busFaultPriority                   , scbActual.busFaultPriority                    );
	    CHECK_EQUAL( scbExpected.usageFaultPriority                 , scbActual.usageFaultPriority                  );
	    CHECK_EQUAL( scbExpected.reserved1                          , scbActual.reserved1                           );
	    CHECK_EQUAL( scbExpected.reserved2                          , scbActual.reserved2                           );
	    CHECK_EQUAL( scbExpected.reserved3                          , scbActual.reserved3                           );
	    CHECK_EQUAL( scbExpected.reserved4                          , scbActual.reserved4                           );
	    CHECK_EQUAL( scbExpected.svCallPriority                     , scbActual.svCallPriority                      );
	    CHECK_EQUAL( scbExpected.reserved5                          , scbActual.reserved5                           );
	    CHECK_EQUAL( scbExpected.reserved6                          , scbActual.reserved6                           );
	    CHECK_EQUAL( scbExpected.pendSvPriority                     , scbActual.pendSvPriority                      );
	    CHECK_EQUAL( scbExpected.sysTickPriority                    , scbActual.sysTickPriority                     );
	    CHECK_EQUAL( scbExpected.systemHandlerControlAndState       , scbActual.systemHandlerControlAndState        );
	    CHECK_EQUAL( scbExpected.configurableFaultStatus            , scbActual.configurableFaultStatus             );
	    CHECK_EQUAL( scbExpected.hardFaultStatus                    , scbActual.hardFaultStatus                     );
	    CHECK_EQUAL( scbExpected.addressOfMemoryManagementFault     , scbActual.addressOfMemoryManagementFault      );
	    CHECK_EQUAL( scbExpected.addressOfBusFault                  , scbActual.addressOfBusFault                   );
	    CHECK_EQUAL( scbExpected.auxiliaryFaultStatus               , scbActual.auxiliaryFaultStatus                );
	}

	void vCheckTickTimerRegisters()
	{
	    CHECK_EQUAL( expectedTickTimerRegister.controlAndStatus, actualTickTimerRegister.controlAndStatus );
	    CHECK_EQUAL( expectedTickTimerRegister.reloadValue     , actualTickTimerRegister.reloadValue      );
	    CHECK_EQUAL( expectedTickTimerRegister.currentValue    , actualTickTimerRegister.currentValue     );
	    CHECK_EQUAL( expectedTickTimerRegister.calibrationValue, actualTickTimerRegister.calibrationValue );
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

	vCheckScbRegisters();

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

	vCheckTickTimerRegisters();

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

