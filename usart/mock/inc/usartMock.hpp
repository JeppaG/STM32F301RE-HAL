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
 * usartMock.hpp
 *
 * Mock implementation header of the usart interface
 *
 *  Created on: 04 Mar 2023
 *      Author: jeppa
 */

#ifndef MOCK_INC_USARTMOCK_HPP_
#define MOCK_INC_USARTMOCK_HPP_

#include <cstdint>

#include "usart.hpp"


class UsartMock : public Usart
{
public:
    UsartMock();

	~UsartMock();

	/* Mocked functions */
	const void* getBaseAddress() override;
    void setBaudRate( uint32_t baudRate ) override;
    void enableDmaTx() override;
    void enableDmaRx() override;
    void enable() override;
    void write( const uint8_t data ) override;
    void clearTxComplete() override;

private:

};

#endif /* MOCK_INC_USARTMOCK_HPP_ */
