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
#include "sysTick.hpp"

#include <cstdint>

#include "clockGeneratorImp.hpp"
#include "sysTickTimerImp.hpp"
#include "gpioImp.hpp"
#include "exceptionImp.hpp"

void* const scbBaseAddress = reinterpret_cast<void*>( 0xE000ED00 );
void* const rccBaseAddress = reinterpret_cast<void*>( 0x40023800 );
void* const sysTickTimerBaseAddress = reinterpret_cast<void*>( 0xE000E010 );
void* const gpioABaseAddress = reinterpret_cast<void*>( 0x40020000 );

ClockGeneratorHsiImp clockGeneratorImp( /* RCC Base Address */ rccBaseAddress );
ClockGenerator* clockGenerator = static_cast<ClockGenerator*>( &clockGeneratorImp );

SysTickTimerImp sysTickTimerImp( /* sysTickTimerBaseAddress */ sysTickTimerBaseAddress,
					             /* ahbClockRateInHz        */ 16000000,
					             /* clockSelect             */ SysTickTimerImp::AHB_CLK_DIV_8 );
Timer* sysTickTimer = static_cast<Timer*>( &sysTickTimerImp );

SysTickHandlerImp sysTickHandlerImp( /* scbBaseAddress */          scbBaseAddress,
                                     /* sysTickTimerBaseAddress */ sysTickTimerBaseAddress );
Exception* sysTickException = static_cast<Exception*>( &sysTickHandlerImp );

PeripheralRccImp gpioARccImp( /* rccBaseAddress */ rccBaseAddress,
		                      /* peripheralRcc  */ PeripheralRccImp::GPIOA );
PeripheralRcc* gpioARcc = static_cast<PeripheralRcc*>( &gpioARccImp );

GpioImp greenLedImp( /* gpioBaseAddress */ gpioABaseAddress,
					 /* peripheralRcc   */ gpioARcc,
					 /* pin             */ GpioImp::pin5 );
Gpio* greenLed = static_cast<Gpio*>( &greenLedImp );

void Main::main()
{
	static uint16_t a = 15;
	static uint16_t b = 40;

	uint16_t c = a + b;

	greenLed->setToDigitalOutput();
	sysTickException->setPriority( 255U );
	sysTickException->enable();
	Exception::enableGlobal();
	while ( true )
	{
	    /* Do nothing */
	}
}

void SysTick::handler()
{
    static uint16_t count = 1000;
    static bool ledIsOn = false;

    if ( 0 == count )
    {
        if ( ledIsOn )
        {
            greenLed->clear();
        }
        else
        {
            greenLed->set();
        }
        ledIsOn = !ledIsOn;
        count = 1000;
    }
    count--;
}
/* __dso_handle is apparently expected by the linker */
void* __dso_handle = 0;
