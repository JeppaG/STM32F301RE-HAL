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
 * timer.hpp
 *
 * Application interface of the timer.
 *
 *  Created on: 28 Sep 2020
 *      Author: jeppa
 */

#ifndef GPIO_IF_GPIO_HPP_
#define GPIO_IF_GPIO_HPP_

class Gpio
{
public:
	static constexpr uint32_t pin5 = 0x00000020;
	static constexpr uint32_t activeHigh = 0x00000001;
	virtual ~Gpio() = 0;
};

class DigitalOutput
{
public:
	static constexpr uint32_t pushPull = 0x00000001;
	static constexpr uint32_t lowSpeed = 0x00000001;

	virtual void set() =0;
	virtual void clear() =0;

	virtual ~DigitalOutput() =0;
};

#endif /* GPIO_IF_GPIO_HPP_ */
