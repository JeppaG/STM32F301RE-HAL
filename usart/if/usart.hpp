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
 * Application interface of the usart
 *
 *  Created on: 23 Dec 2020
 *      Author: jeppa
 */

#ifndef USART_IF_USART_HPP_
#define USART_IF_USART_HPP_

class Usart
{
public:
    virtual void setBaudRate( uint32_t baudRate ) = 0;
    virtual void enable() = 0;
    virtual void write( const uint8_t data ) = 0;
	virtual ~Usart() = 0;
};
#endif /* USART_IF_USART_HPP_ */
