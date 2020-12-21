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
 * exception.hpp
 *
 * Application interface of exceptions.
 *
 *  Created on: 28 Sep 2020
 *      Author: jeppa
 */

#ifndef EXCEPTION_IF_EXCEPTION_HPP_
#define EXCEPTION_IF_EXCEPTION_HPP_

#include <cstdint>


class Exception
{
public:
	typedef void (*handlerType)(void);

	virtual void setPriority( uint8_t priority )=0;
	virtual void enable()=0;
	virtual ~Exception() = 0;
	static void enableGlobal();
	static void disableGlobal();

private:
	static void defaultHandler();
	static const Exception::handlerType __vector_table__[];
};

#endif /* EXCEPTION_IF_EXCEPTION_HPP_ */
