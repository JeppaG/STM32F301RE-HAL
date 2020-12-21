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

DigitalOutputImp::DigitalOutputImp( void* const          gpioBaseAddress,
		  	  	  	  	  	  	    PeripheralRcc* const peripheralRcc,
		                            const uint32_t       pin,
		                            const uint32_t       outputType,
		                            const uint32_t       speed,
		                            const uint32_t       polarity ) :
gpio( reinterpret_cast<registerType* const>( gpioBaseAddress ) ),
rcc( peripheralRcc )
{
	rcc->enableClock();
	gpio->mode |= 0x00000400;
	gpio->bitSetReset |= 0x00200000;
}

void DigitalOutputImp::set()
{
	gpio->bitSetReset = 0x00000020;
}

void DigitalOutputImp::clear()
{
	gpio->bitSetReset = 0x00200000;
}

DigitalOutputImp::~DigitalOutputImp()
{

}

DigitalOutput::~DigitalOutput()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}

Gpio::~Gpio()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}


