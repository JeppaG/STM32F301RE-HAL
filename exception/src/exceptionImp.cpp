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
 * exceptionImp.cpp
 *
 *  Created on: 8 Sep 2020
 *      Author: jeppa
 */

#include "exceptionImp.hpp"

SystemHandlerCommonImp::SystemHandlerCommonImp( void* const scbBaseAddress ) :
    scb ( reinterpret_cast<registerType* const>( scbBaseAddress ) )
{
}


SystemHandlerCommonImp::~SystemHandlerCommonImp()
{

}

SysTickHandlerImp::SysTickHandlerImp( void* const scbBaseAddress,
		                              void* const sysTickTimerBaseAddress ) :
SystemHandlerCommonImp( scbBaseAddress ),
stk( reinterpret_cast<registerType* const>( sysTickTimerBaseAddress ) )
{

}

SysTickHandlerImp::~SysTickHandlerImp()
{

}

void SysTickHandlerImp::setPriority( uint8_t priority )
{
	scb->sysTickPriority = priority;
}

void SysTickHandlerImp::enable()
{
	stk->controlAndStatus |= 0x00000002;
}

Exception::~Exception()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}


