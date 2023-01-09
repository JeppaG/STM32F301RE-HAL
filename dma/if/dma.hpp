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
 * dma.hpp
 *
 * Application interface of the dma
 *
 *  Created on: 17 May 2021
 *      Author: jeppa
 */

#ifndef DMA_IF_DMA_HPP_
#define DMA_IF_DMA_HPP_

class Dma
{
public:
    virtual void setPeripheralAddress( uint32_t ui32Address ) = 0;
    virtual void setMemory0Address( uint32_t ui32Address ) = 0;
    virtual void setNumberOfData( uint16_t ui16NumberOfData ) = 0;
    virtual void setStreamDirection ( uint8_t direction ) = 0;
	virtual ~Dma() = 0;

	static constexpr uint8_t memoryToPeripheral = 1;
};
#endif /* DMA_IF_DMA_HPP_ */
