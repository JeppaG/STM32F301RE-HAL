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

Usart1_2Imp::Usart1_2Imp( void* const          usartBaseAddress,
                          PeripheralRcc* const pRcc,
						  Gpio*		           rxPin,
						  Gpio*		           txPin ):
    usart( static_cast<registerType* const>( usartBaseAddress ) ),
    rcc  ( pRcc )
{
	rxPin->setToAlternateFunction( Gpio::AF07 );
	txPin->setToAlternateFunction( Gpio::AF07 );
	rcc->enableClock();
	rcc->getClockFrequencyInHz();
	usart->baudRate = 139U;
}

const void* Usart1_2Imp::getBaseAddress()
{
    return static_cast<const void*>( usart );
}

void Usart1_2Imp::setBaudRate( uint32_t baudRate )
{
    rcc->getClockFrequencyInHz();
    usart->baudRate = 139;
}

void Usart1_2Imp::enableDmaTx()
{
    usart->control3 |= 0x00000080;
}

void Usart1_2Imp::enableDmaRx()
{
    usart->control3 |= 0x00000040;
}

void Usart1_2Imp::enable()
{
    usart->control1 = 0x0000200C;
}

void Usart1_2Imp::write( const uint8_t data )
{
    usart->data = data;
}

void Usart1_2Imp::clearTxComplete()
{
    usart->status = 0x00C00000;
}

Usart1_2Imp::~Usart1_2Imp()
{
}

Usart::~Usart()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}

