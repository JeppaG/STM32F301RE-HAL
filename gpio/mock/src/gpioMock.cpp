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
 *  Created on: 02 Jan 2021
 *      Author: jeppa
 */

#include "CppUTestExt/MockSupport.h"
#include "gpioMock.hpp"

GpioMock::GpioMock() :
    pinMode    ( UNDEFINED_PIN_MODE ),
    outputValue( UNDEFINED_OUTPUT_VALUE )
{
}

GpioMock::~GpioMock()
{
}

Gpio::~Gpio()
{
    /* C++ demands that even a pure virtual destructor has an implementation */
}

void GpioMock::setToDigitalOutput()
{
    if ( OUTPUT != pinMode )
    {
        mock().actualCall( "setToDigitalOutput" ).onObject( this );
        pinMode = OUTPUT;
    }
}

void GpioMock::set()
{
    if ( SET != outputValue )
    {
        mock().actualCall( "set" ).onObject( this );
        outputValue = SET;
    }
}

void GpioMock::clear()
{
    if ( CLEARED != outputValue )
    {
        mock().actualCall( "clear" ).onObject( this );
        outputValue = CLEARED;
    }
}

void GpioMock::expectSetToDigitalOutput()
{
    mock().expectOneCall( "setToDigitalOutput" )
          .onObject( this );
    pinMode = UNDEFINED_PIN_MODE;
}

void GpioMock::expectSet()
{
    mock().expectOneCall( "set" ).onObject( this );
    outputValue = UNDEFINED_OUTPUT_VALUE;
}

void GpioMock::expectClear()
{
    mock().expectOneCall( "clear" ).onObject( this );
    outputValue = UNDEFINED_OUTPUT_VALUE;
}
