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
 * clockImp.hpp
 *
 * Mock implementation header of the clockGenerator interface
 *
 *  Created on: 28 Sep 2020
 *      Author: jeppa
 */

#ifndef MOCK_INC_CLOCKGENERATORMOCK_HPP_
#define MOCK_INC_CLOCKGENERATORMOCK_HPP_

#include <cstdint>

#include "clockGenerator.hpp"


class PeripheralRccMock : public PeripheralRcc
{
public:
    PeripheralRccMock();

	~PeripheralRccMock();

	/* Mocked functions */
	void enableClock();

	/* Test case helper functions */
	void expectEnableClock();

	uint32_t getClockFrequencyInHz();
};

#endif /* MOCK_INC_CLOCKGENERATORMOCK_HPP_ */
