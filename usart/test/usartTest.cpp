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
 *  Created on: 22-Dec 2020
 *      Author: jeppa
 */

#include <cstring>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "usartImp.hpp"

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

	Usart* usart;

	void vInitializeTestRegistersToResetValues()
	{
		memcpy( &expectedRegister, &resetRegister, sizeof( usartRegisterType ) );
		memcpy( &actualRegister, &resetRegister, sizeof( usartRegisterType ) );
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

/*! Check that when Usart1_2 is instantiated the Rx pand Tx pins are set to alternate function AF07.
 */
TEST( Usart, InstantiateUsart1_2 )
{
	usart = static_cast<Usart*>( new Usart1_2Imp( /* Usart Base address */ &actualRegister ) );

	CHECK_EQUAL( expectedRegister.status, actualRegister.status );

	delete usart;
}


int main( int ac, char** av )
{
	return CommandLineTestRunner::RunAllTests( ac, av );
}
