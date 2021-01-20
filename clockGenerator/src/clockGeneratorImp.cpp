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
 * clockGeneratorImp.cpp
 *
 *  Created on: 11 Aug 2020
 *      Author: jeppa
 */

#include "clockGeneratorImp.hpp"
#include "assert.hpp"

ClockGeneratorCommonImp::~ClockGeneratorCommonImp()
{
}

ClockGeneratorHsiImp::ClockGeneratorHsiImp( void* const rccBaseAddress ) :
rcc( reinterpret_cast<registerType* const>( rccBaseAddress ) )
{
	ASSERT( ( rcc->clockControl & 0x00000002 ) == 0x00000002 );
}

ClockGeneratorHsiImp::~ClockGeneratorHsiImp()
{
}

PeripheralRccImp::PeripheralRccImp( void* const rccBaseAddress, const PeripheralRccType peripheralRcc ) :
rcc( reinterpret_cast<registerType* const>( rccBaseAddress ) )
{
}

PeripheralRccImp::~PeripheralRccImp()
{
}

void PeripheralRccImp::enableClock()
{
	rcc->ahb1ClockEnable = 0x00000001;
	rcc->apb2ClockEnable = 0x00000010;
}

ClockGenerator::~ClockGenerator()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}

PeripheralRcc::~PeripheralRcc()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}
