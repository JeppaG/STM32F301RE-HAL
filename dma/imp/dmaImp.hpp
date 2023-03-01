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

    DmaImp( void* const    dmaBaseAddress,
            PeripheralRcc* const pRcc,
            uint8_t        ui8Stream,
            uint8_t        ui8Channel );

    void setPeripheralAddress( void* pvAddress ) override;
    void setMemory0Address( void* pvAddress ) override;
    void setNumberOfData( uint16_t ui16NumberOfData ) override;
    void setDirectionMemoryToPeripheral() override;
    void setDirectionPeripheralToMemory() override;
    void setMemoryIncrementalMode() override;
    void setCircularMode() override;
    uint32_t getNumberOfData() override;
    void enable() override;

	~DmaImp();

private:
    typedef struct
    {
        volatile uint32_t lowInterruptStatus;       /* Base address + 0x0 */
        volatile uint32_t highInterruptStatus;      /* Base address + 0x4 */
        volatile uint32_t lowInterruptFlagClear;    /* Base address + 0x8 */
        volatile uint32_t highInterruptFlagClear;   /* Base address + 0xC */
    } interruptRegisterType;

	typedef struct
	{
        volatile uint32_t configuration;     /* Base address + 0x00 */
        volatile uint32_t numberOfData;      /* Base address + 0x04 */
        volatile uint32_t peripheralAddress; /* Base address + 0x08 */
        volatile uint32_t memory0Address;    /* Base address + 0x0C */
        volatile uint32_t memory1Address;    /* Base address + 0x10 */
        volatile uint32_t fifoControl   ;    /* Base address + 0x14 */
	} streamRegisterType;

	interruptRegisterType* const interruptReg;
    streamRegisterType*    const streamReg;
	PeripheralRcc*         const rcc;
	uint8_t                const stream;
};


#endif /* DMA_IMP_DMAIMP_HPP_ */
