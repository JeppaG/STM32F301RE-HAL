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
 * gpioImp.cpp
 *
 *  Created on: 8 Sep 2020
 *      Author: jeppa
 */

#include "gpioImp.hpp"

GpioImp::GpioImp( void* const          gpioBaseAddress,
		  	  	  PeripheralRcc* const peripheralRcc,
		          const uint32_t       pinNumber ) :
    gpio( reinterpret_cast<registerType* const>( gpioBaseAddress ) ),
    rcc( peripheralRcc ),
    pin( pinNumber )

{
	rcc->enableClock();
}

void GpioImp::setToDigitalOutput()
{
    gpio->mode |= 0x00000400;
    gpio->bitSetReset = 0x00200000;
}

void GpioImp::set()
{
	gpio->bitSetReset = 0x00000020;
}

void GpioImp::clear()
{
	gpio->bitSetReset = 0x00200000;
}

void GpioImp::setToAlternateFunction( const uint32_t alternateFunction )
{
    gpio->mode |= pin*pin*2;
    if ( pin9 == pin )
    {
        gpio->alternateFunctionHigh |= 0x00000070;
    }
    else if ( pin10 == pin )
    {
        gpio->alternateFunctionHigh |= 0x00000700;
    }
}

GpioImp::~GpioImp()
{

}

Gpio::~Gpio()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}

