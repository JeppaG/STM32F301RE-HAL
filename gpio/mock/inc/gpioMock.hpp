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
 * gpioMock.hpp
 *
 * Mock implementation header of the gpio interface
 *
 *  Created on: 02 Jan 2021
 *      Author: jeppa
 */

#ifndef MOCK_INC_GPIOMOCK_HPP_
#define MOCK_INC_GPIOMOCK_HPP_

#include <cstdint>

#include "gpio.hpp"


class GpioMock : public Gpio
{
public:
    GpioMock();

	~GpioMock();

	/* Mocked functions */
	virtual void setToDigitalOutput();
    virtual void setToAlternateFunction( const uint32_t alternateFunction );
	virtual void set();
	virtual void clear();

	/* Test case helper functions */
	void expectSetToDigitalOutput();
	void expectSetToAlternateFunction( const uint32_t alternateFunction );
	void expectSet();
	void expectClear();

private:
	typedef enum
	{
	    UNDEFINED_PIN_MODE = 0,
	    INPUT,
	    OUTPUT,
	    ALTERNATE_FUNCTION,
	    ANALOG
	} pinModeType;

	typedef enum
	{
	    UNDEFINED_OUTPUT_VALUE = 0,
	    SET,
	    CLEARED
	} outputValueType;

	pinModeType     pinMode;
	outputValueType outputValue;
	uint32_t        altFunc;
};

#endif /* MOCK_INC_GPIOMOCK_HPP_ */
