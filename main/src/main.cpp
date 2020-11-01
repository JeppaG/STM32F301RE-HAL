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
 * main.cpp
 *
 *  Created on: 4 Jun 2020
 *      Author: jeppa
 */

#include "main.hpp"
#include <cstdint>
#include "clockGeneratorImp.hpp"
#include "sysTickTimerImp.hpp"
#include "gpioImp.hpp"

void* const rccBaseAddress = reinterpret_cast<void*>( 0x40023800 );
void* const sysTickTimerBaseAddress = reinterpret_cast<void*>( 0xE000E010 );
void* const gpioABaseAddress = reinterpret_cast<void*>( 0x40020000 );

ClockGeneratorHsiImp clockGeneratorImp( /* RCC Base Address */ rccBaseAddress );
ClockGenerator* clockGenerator = dynamic_cast<ClockGenerator*>( &clockGeneratorImp );

SysTickTimerImp sysTickTimerImp( /* sysTickTimerBaseAddress */ sysTickTimerBaseAddress,
					             /* ahbClockRateInHz        */ 16000000,
					             /* clockSelect             */ SysTickTimerImp::AHB_CLK_DIV_8 );
Timer* sysTickTimer = dynamic_cast<Timer*>( &sysTickTimerImp );

PeripheralRccImp gpioARccImp( /* rccBaseAddress */ rccBaseAddress,
		                      /* peripheralRcc  */ PeripheralRccImp::GPIOA );
PeripheralRcc* gpioARcc = dynamic_cast<PeripheralRcc*>( &gpioARccImp );

DigitalOutputImp greenLedImp( /* gpioBaseAddress */ gpioABaseAddress,
					          /* peripheralRcc   */ gpioARcc,
					          /* pin             */ DigitalOutputImp::pin5,
					          /* outputType      */ DigitalOutputImp::pushPull,
					          /* speed           */ DigitalOutputImp::lowSpeed,
					          /* polarity        */ DigitalOutputImp::activeHigh );
DigitalOutput* greenLed = dynamic_cast<DigitalOutput*>( &greenLedImp );

void Main::main()
{
	static uint16_t a = 15;
	static uint16_t b = 40;

	uint16_t c = a + b;
	while ( true )
	{
		greenLed->set();
		for ( int i = 0; i < 64000; i++ )
		{
		}
		greenLed->clear();
		for ( int i = 0; i < 64000; i++ )
		{
		}
	}
}

///* Entry point from crt0.s */
//
//int main()
//{
//	Main::main();
//	return 0;
//}

/* __dso_handle is apparently expected by the linker */
void* __dso_handle = 0;
