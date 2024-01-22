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

#include "usartMock.hpp"
#include "CppUTestExt/MockSupport.h"

UsartMock::UsartMock()
{
}

UsartMock::~UsartMock()
{
}

Usart::~Usart()
{
    /* C++ demands that even a pure virtual destructor has an implementation */
}

const void* UsartMock::getBaseAddress()
{
    return mock().actualCall( "getBaseAddress" ).onObject( this ).returnConstPointerValue();
}

void UsartMock::setBaudRate( uint32_t baudRate )
{
   // reinterpret_cast<void*>( baudRate );
}

void UsartMock::enableDmaTx()
{
    mock().actualCall( "enableDmaTx" ).onObject( this );
}

void UsartMock::enableDmaRx()
{
    mock().actualCall( "enableDmaRx" ).onObject( this );
}

void UsartMock::enable()
{
    mock().actualCall( "enable" ).onObject( this );
}

void UsartMock::write( const uint8_t data )
{
   // reinterpret_cast<void*>( data );
}

void UsartMock::clearTxComplete()
{
    mock().actualCall( "clearTxComplete" ).onObject( this );
}

bool UsartMock::newRxData()
{
    return mock().actualCall( "newRxData" ).onObject( this ).returnBoolValue();
}

uint8_t UsartMock::read()
{
    return static_cast<uint8_t>( mock().actualCall( "read" ).onObject( this ).returnIntValue() );
}
/*
 * Test case helper functions
 */
