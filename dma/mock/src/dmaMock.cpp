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

#include "../inc/dmaMock.hpp"
#include "CppUTestExt/MockSupport.h"

DmaMock::DmaMock() :
    returnNumberOfData ( 0 )
{
}

DmaMock::~DmaMock()
{
}

Dma::~Dma()
{
    /* C++ demands that even a pure virtual destructor has an implementation */
}

void DmaMock::setPeripheralAddress( void* pvAddress )
{
    mock().actualCall( "setPeripheralAddress" ).onObject( this ).withPointerParameter( "pvAddress", pvAddress );
}

void DmaMock::setMemory0Address( void* pvAddress )
{
    mock().actualCall( "setMemory0Address" ).onObject( this ).withPointerParameter( "pvAddress", pvAddress );
}

void DmaMock::setNumberOfData( uint16_t ui16NumberOfData )
{
    mock().actualCall( "setNumberOfData" ).onObject( this ).withParameterOfType( "uint16_t", "ui16NumberOfData", &ui16NumberOfData );
}

void DmaMock::setDirectionMemoryToPeripheral()
{
    mock().actualCall( "setDirectionMemoryToPeripheral" ).onObject( this );
}

void DmaMock::setDirectionPeripheralToMemory()
{
    mock().actualCall( "setDirectionPeripheralToMemory" ).onObject( this );
}

void DmaMock::setMemoryIncrementalMode()
{
    mock().actualCall( "setMemoryIncrementalMode" ).onObject( this );
}

void DmaMock::setCircularMode()
{
}

uint16_t DmaMock::getNumberOfData()
{
    mock().actualCall( "getNumberOfData" ).onObject( this );
    return returnNumberOfData;
}

void DmaMock::enable()
{
    mock().actualCall( "enable" ).onObject( this );
}

void DmaMock::disable()
{
    mock().actualCall( "disable" ).onObject( this );
}

/*************************************************************
 * Test case helper functions
 ************************************************************/
void DmaMock::expectGetNumberOfData ( uint32_t numberOfData )
{
    mock().expectOneCall( "getNumberOfData" ).onObject( static_cast<void*>( this ) );
    returnNumberOfData = numberOfData;
}

