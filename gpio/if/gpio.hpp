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
 * gpio.hpp
 *
 * Application interface of gpio.
 *
 *  Created on: 28 Sep 2020
 *      Author: jeppa
 */

#ifndef GPIO_IF_GPIO_HPP_
#define GPIO_IF_GPIO_HPP_

class Gpio
{
public:
	static constexpr uint32_t pin5  = 0x00000020;
	static constexpr uint32_t pin9  = 0x00000200;
	static constexpr uint32_t pin10 = 0x00000400;

	static constexpr uint32_t AF07 = 7;
	virtual ~Gpio() = 0;

	virtual void setToDigitalOutput() = 0;
	virtual void setToAlternateFunction( const uint32_t alternateFunction ) = 0;
	virtual void set() = 0;
	virtual void clear() = 0;
};

#endif /* GPIO_IF_GPIO_HPP_ */
