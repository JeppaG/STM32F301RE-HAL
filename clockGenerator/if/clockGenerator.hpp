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
 * clockGenerator.hpp
 *
 * Application interface of the clock controller
 *
 *  Created on: 24 Jul 2020
 *      Author: jeppa
 */

#ifndef CLOCKGENERATOR_IF_CLOCKGENERATOR_HPP_
#define CLOCKGENERATOR_IF_CLOCKGENERATOR_HPP_

class ClockGenerator
{
public:
	virtual ~ClockGenerator() = 0;
};

class PeripheralRcc
{
public:
	virtual void enableClock() = 0;
	virtual ~PeripheralRcc() = 0;
};
#endif /* CLOCKGENERATOR_IF_CLOCKGENERATOR_HPP_ */