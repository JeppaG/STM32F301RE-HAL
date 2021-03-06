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
 * sysTickTimerImp.cpp
 *
 *  Created on: 8 Sep 2020
 *      Author: jeppa
 */

#include "sysTickTimerImp.hpp"

SysTickTimerImp::SysTickTimerImp( void* const           sysTickTimerBaseAddress,
		                          const uint32_t        ahbClockRateInHz,
							      const clockSelectType clockSelect) :
	stk( reinterpret_cast<registerType* const>( sysTickTimerBaseAddress ) )
{
	stk->controlAndStatus = 1;
	stk->reloadValue = 1999;
}

SysTickTimerImp::~SysTickTimerImp()
{

}

Timer::~Timer()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}


