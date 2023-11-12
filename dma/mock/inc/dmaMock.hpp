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
 * dmaMock.hpp
 *
 * Mock implementation header of the usart interface
 *
 *  Created on: 04 Mar 2023
 *      Author: jeppa
 */

#ifndef MOCK_INC_DMAMOCK_HPP_
#define MOCK_INC_DMAMOCK_HPP_

#include <cstdint>

#include "dma.hpp"


class DmaMock : public Dma
{
public:
    DmaMock();

	~DmaMock();

	/* Mocked functions */
    void setPeripheralAddress( void* pvAddress ) override;
    void setMemory0Address( void* pvAddress ) override;
    void setNumberOfData( uint16_t ui16NumberOfData ) override;
    void setDirectionMemoryToPeripheral () override;
    void setDirectionPeripheralToMemory () override;
    void setMemoryIncrementalMode() override;
    void setCircularMode() override;
    uint16_t getNumberOfData() override;
    void enable() override;
    void disable() override;

	/* Test case helper functions */
    void expectGetNumberOfData ( uint32_t numberOfData );

private:
    uint16_t returnNumberOfData;

};

#endif /* MOCK_INC_DMAMOCK_HPP_ */
