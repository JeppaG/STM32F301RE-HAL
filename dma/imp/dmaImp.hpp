/*
 * Copyright 2021 JG Mechatronics AB
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
 * dmaImp.hpp
 *
 * Implementation header of the dma interface
 *
 *  Created on: 17 May 2021
 *      Author: jeppa
 */

#ifndef DMA_IMP_DMAIMP_HPP_
#define DMA_IMP_DMAIMP_HPP_

#include <cstdint>
#include "clockGenerator.hpp"
#include "dma.hpp"

class DmaImp:public Dma
{
public:
    typedef struct
    {
        volatile uint32_t lowInterruptStatus;       /* Base address + 0x0 */
        volatile uint32_t highInterruptStatus;      /* Base address + 0x4 */
        volatile uint32_t lowInterruptFlagClear;    /* Base address + 0x8 */
        volatile uint32_t highInterruptFlagClear;   /* Base address + 0xC */
        volatile uint32_t stream0Configuration;     /* Base address + 0x10 */
        volatile uint32_t stream0NumberOfData;      /* Base address + 0x14 */
        volatile uint32_t stream0PeripheralAddress; /* Base address + 0x18 */
        volatile uint32_t stream0Memory0Address;    /* Base address + 0x1C */
        volatile uint32_t stream0Memory1Address;    /* Base address + 0x20 */
        volatile uint32_t stream0FifoControl   ;    /* Base address + 0x24 */
        volatile uint32_t stream1Configuration;     /* Base address + 0x28 */
        volatile uint32_t stream1NumberOfData;      /* Base address + 0x2C */
        volatile uint32_t stream1PeripheralAddress; /* Base address + 0x30 */
        volatile uint32_t stream1Memory0Address;    /* Base address + 0x34 */
        volatile uint32_t stream1Memory1Address;    /* Base address + 0x38 */
        volatile uint32_t stream1FifoControl   ;    /* Base address + 0x3C */
        volatile uint32_t stream2Configuration;     /* Base address + 0x40 */
        volatile uint32_t stream2NumberOfData;      /* Base address + 0x44 */
        volatile uint32_t stream2PeripheralAddress; /* Base address + 0x48 */
        volatile uint32_t stream2Memory0Address;    /* Base address + 0x4C */
        volatile uint32_t stream2Memory1Address;    /* Base address + 0x50 */
        volatile uint32_t stream2FifoControl   ;    /* Base address + 0x54 */
        volatile uint32_t stream3Configuration;     /* Base address + 0x58 */
        volatile uint32_t stream3NumberOfData;      /* Base address + 0x5C */
        volatile uint32_t stream3PeripheralAddress; /* Base address + 0x60 */
        volatile uint32_t stream3Memory0Address;    /* Base address + 0x64 */
        volatile uint32_t stream3Memory1Address;    /* Base address + 0x68 */
        volatile uint32_t stream3FifoControl   ;    /* Base address + 0x6C */
        volatile uint32_t stream4Configuration;     /* Base address + 0x70 */
        volatile uint32_t stream4NumberOfData;      /* Base address + 0x74 */
        volatile uint32_t stream4PeripheralAddress; /* Base address + 0x78 */
        volatile uint32_t stream4Memory0Address;    /* Base address + 0x7C */
        volatile uint32_t stream4Memory1Address;    /* Base address + 0x80 */
        volatile uint32_t stream4FifoControl   ;    /* Base address + 0x84 */
        volatile uint32_t stream5Configuration;     /* Base address + 0x88 */
        volatile uint32_t stream5NumberOfData;      /* Base address + 0x8C */
        volatile uint32_t stream5PeripheralAddress; /* Base address + 0x90 */
        volatile uint32_t stream5Memory0Address;    /* Base address + 0x94 */
        volatile uint32_t stream5Memory1Address;    /* Base address + 0x98 */
        volatile uint32_t stream5FifoControl   ;    /* Base address + 0x9C */
        volatile uint32_t stream6Configuration;     /* Base address + 0xA0 */
        volatile uint32_t stream6NumberOfData;      /* Base address + 0xA4 */
        volatile uint32_t stream6PeripheralAddress; /* Base address + 0xA8 */
        volatile uint32_t stream6Memory0Address;    /* Base address + 0xAC */
        volatile uint32_t stream6Memory1Address;    /* Base address + 0xB0 */
        volatile uint32_t stream6FifoControl   ;    /* Base address + 0xB4 */
        volatile uint32_t stream7Configuration;     /* Base address + 0xB8 */
        volatile uint32_t stream7NumberOfData;      /* Base address + 0xBC */
        volatile uint32_t stream7PeripheralAddress; /* Base address + 0xC0 */
        volatile uint32_t stream7Memory0Address;    /* Base address + 0xC4 */
        volatile uint32_t stream7Memory1Address;    /* Base address + 0xC8 */
        volatile uint32_t stream7FifoControl   ;    /* Base address + 0xCC */
    } registerType;

    DmaImp( void* const    dmaBaseAddress,
            PeripheralRcc* const pRcc,
            uint8_t        ui8Stream,
            uint8_t        ui8Channel );

    void setPeripheralAddress( void* pvAddress ) override;
    void setMemory0Address( void* pvAddress ) override;
    void setNumberOfData( uint16_t ui16NumberOfData ) override;
    void setStreamDirection( uint8_t direction ) override;
    void setMemoryIncrementalMode() override;
    void enable() override;

	~DmaImp();

private:
	registerType* const  dma;
	PeripheralRcc* const rcc;
	uint8_t        const stream;
};


#endif /* DMA_IMP_DMAIMP_HPP_ */
