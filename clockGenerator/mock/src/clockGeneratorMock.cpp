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
 * clockeneratorMock.cpp Implementation of mock ClockGenerator classes
 *
 *  Created on: 28 Sep 2020
 *      Author: jeppa
 */

#include "CppUTestExt/MockSupport.h"
#include "clockGeneratorMock.hpp"

PeripheralRccMock::PeripheralRccMock():
    clockFrequencyInHz ( 16000000U )
{
}

PeripheralRccMock::~PeripheralRccMock()
{
}

PeripheralRcc::~PeripheralRcc()
{
    /* C++ demands that even a pure virtual destructor has an implementation */
}

void PeripheralRccMock::enableClock()
{
	mock().actualCall( "enableClock" )
		  .onObject( this );
}

uint32_t PeripheralRccMock::getClockFrequencyInHz()
{
    mock().actualCall( "getClockFrequencyInHz" )
          .onObject( this );
    return clockFrequencyInHz;
}

void PeripheralRccMock::expectEnableClock()
{
    mock().expectOneCall( "enableClock" )
          .onObject( this );
}

void PeripheralRccMock::expectGetClockFrequencyInHzAndReturn( uint32_t clockFrequency )
{
    mock().expectOneCall( "getClockFrequencyInHz" )
          .onObject( this );
    clockFrequencyInHz = clockFrequency;
}
