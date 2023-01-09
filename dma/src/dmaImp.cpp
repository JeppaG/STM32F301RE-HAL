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
 *  Created on: 2 Jan 2023
 *      Author: jeppa
 */

#include "dmaImp.hpp"

DmaImp::DmaImp( void* const    dmaBaseAddress,
                PeripheralRcc* const pRcc,
                uint8_t        ui8Stream,
                uint8_t        ui8Channel ) :
    dma( static_cast<registerType* const>( dmaBaseAddress ) ),
    rcc  ( pRcc )
{
    rcc->enableClock();
    dma->stream6Configuration = 0x08000000;
}

void DmaImp::setPeripheralAddress( uint32_t ui32Address )
{
    dma->stream6PeripheralAddress = ui32Address;
}

void DmaImp::setMemory0Address( uint32_t ui32Address )
{
    dma->stream6Memory0Address = ui32Address;
}

void DmaImp::setNumberOfData( uint16_t ui16NumberOfData )
{
    dma->stream6NumberOfData = ui16NumberOfData;
}

void DmaImp::setStreamDirection( uint8_t direction )
{
    dma->stream6Configuration |= 0x00000040;
}

DmaImp::~DmaImp()
{
}

Dma::~Dma()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}

