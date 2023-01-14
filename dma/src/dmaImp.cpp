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
    rcc  ( pRcc ),
    stream ( ui8Stream )
{
    rcc->enableClock();
    if ( 6 == stream )
    {
        dma->stream6Configuration = 0x08000000;
    }
    else if ( 7 == stream )
    {
        dma->stream7Configuration = 0x08000000;
    }
}

void DmaImp::setPeripheralAddress( void* pvAddress )
{
    if ( 6 == stream )
    {
        dma->stream6PeripheralAddress = reinterpret_cast<intptr_t>( pvAddress );
    }
    else if ( 7 == stream )
    {
        dma->stream7PeripheralAddress = reinterpret_cast<intptr_t>( pvAddress );
    }
}

void DmaImp::setMemory0Address( void* pvAddress )
{
    if ( 6 == stream )
    {
        dma->stream6Memory0Address = reinterpret_cast<intptr_t>( pvAddress );
    }
    else if ( 7 == stream )
    {
        dma->stream7Memory0Address = reinterpret_cast<intptr_t>( pvAddress );
    }

}

void DmaImp::setNumberOfData( uint16_t ui16NumberOfData )
{
    if ( 6 == stream )
    {
        dma->stream6NumberOfData = ui16NumberOfData;
    }
    else if ( 7 == stream )
    {
        dma->stream7NumberOfData = ui16NumberOfData;
    }
}

void DmaImp::setStreamDirection( uint8_t direction )
{
    if ( 6 == stream )
    {
        dma->stream6Configuration |= 0x00000040;
    }
    else if ( 7 == stream )
    {
        dma->stream7Configuration |= 0x00000040;
    }
}

void DmaImp::enable()
{
    if ( 6 == stream )
    {
        dma->stream6Configuration |= 0x00000001;
    }
    else if ( 7 == stream )
    {
        dma->stream7Configuration |= 0x00000001;
    }
}

DmaImp::~DmaImp()
{
}

Dma::~Dma()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}

