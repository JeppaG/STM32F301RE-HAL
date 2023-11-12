/*
 * Copyright 2023 JG Mechatronics AB
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
 *  Created on: 04 Mar 2023
 *      Author: jeppa
 */

#include "serialPortImp.hpp"

SerialPortImp::SerialPortImp( Usart* const pUsart,
						      Dma*	 const pTxDma,
						      Dma*	 const pRxDma ) :
  usart( pUsart ),
  txDma( pTxDma ),
  rxDma( pRxDma ),
  rxBufferSize( 0 )
{
    const void* usartBaseAddress = pUsart->getBaseAddress();
    pTxDma->setPeripheralAddress( const_cast<void*>( usartBaseAddress ) + 4 );
    pRxDma->setPeripheralAddress( const_cast<void*>( usartBaseAddress ) + 4 );
    pTxDma->setDirectionMemoryToPeripheral();
    pRxDma->setDirectionPeripheralToMemory();
    pTxDma->setMemoryIncrementalMode();
    pRxDma->setMemoryIncrementalMode();
    pUsart->enableDmaTx();
    pUsart->enableDmaRx();
    pUsart->enable();
}

void SerialPortImp::transmit( void* buffer, uint16_t size )
{
    txDma->setMemory0Address( buffer );
    txDma->setNumberOfData( size );
    usart->clearTxComplete();
    txDma->enable();
}

uint16_t SerialPortImp::receive( void* buffer, uint16_t size )
{
    uint16_t numberOfReadData;

    rxDma->disable();
    numberOfReadData = rxBufferSize - rxDma->getNumberOfData();
    rxDma->setMemory0Address( buffer );
    rxDma->setNumberOfData( size );
    rxDma->enable();
    rxBufferSize = size;

    return numberOfReadData;
}

SerialPortImp::~SerialPortImp()
{
}

SerialPort::~SerialPort()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}

