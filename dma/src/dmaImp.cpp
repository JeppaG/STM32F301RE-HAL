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

#include <cstddef>
#include <cstdio>
#include "dmaImp.hpp"

DmaImp::DmaImp( void* const    dmaBaseAddress,
                PeripheralRcc* const pRcc,
                uint8_t        ui8Stream,
                uint8_t        ui8Channel ) :
    interruptReg( static_cast<interruptRegisterType* const>( dmaBaseAddress ) ),
    streamReg( reinterpret_cast<streamRegisterType* const>(
                        reinterpret_cast<uintptr_t>( dmaBaseAddress )
                      + sizeof( interruptRegisterType )
                      + ui8Stream* sizeof( streamRegisterType ) ) ),
    rcc  ( pRcc ),
    stream ( ui8Stream )
{
    rcc->enableClock();
    streamReg->configuration = 0x08000000;
}

void DmaImp::setPeripheralAddress( void* pvAddress )
{
    streamReg->peripheralAddress = reinterpret_cast<uintptr_t>( pvAddress );
}

void DmaImp::setMemory0Address( void* pvAddress )
{
    streamReg->memory0Address = reinterpret_cast<uintptr_t>( pvAddress );
}

void DmaImp::setNumberOfData( uint16_t ui16NumberOfData )
{
    streamReg->numberOfData = ui16NumberOfData;
}

void DmaImp::setDirectionMemoryToPeripheral()
{
    streamReg->configuration |= 0x00000040;
}

void DmaImp::setDirectionPeripheralToMemory()
{
    streamReg->configuration &=0xFFFFFF3F;
}

void DmaImp::setMemoryIncrementalMode()
{
    streamReg->configuration |= 0x00000400;
}

void DmaImp::enable()
{
    if ( 5 == stream )
    {
        interruptReg->highInterruptFlagClear = 0x00000F40;
        streamReg->configuration |= 0x00000001;
    }
    if ( 6 == stream )
    {
        interruptReg->highInterruptFlagClear = 0x003D0000;
        streamReg->configuration |= 0x00000001;
    }
    else if ( 7 == stream )
    {
        interruptReg->highInterruptFlagClear = 0x0F400000;
        streamReg->configuration |= 0x00000001;
    }
}

DmaImp::~DmaImp()
{
}

Dma::~Dma()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}

