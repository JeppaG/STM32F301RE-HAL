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
 * usartImp.cpp
 *
 *  Created on: 8 Jan 2021
 *      Author: jeppa
 */

#include "usartImp.hpp"

Usart1_2Imp::Usart1_2Imp( void* const    usartBaseAddress,
                          PeripheralRcc* rcc,
						  Gpio*		     rxPin,
						  Gpio*		     txPin )
{
	rxPin->setToAlternateFunction( Gpio::AF07 );
	txPin->setToAlternateFunction( Gpio::AF07 );
	rcc->enableClock();
}

Usart1_2Imp::~Usart1_2Imp()
{
}

Usart::~Usart()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}

