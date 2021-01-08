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
 * usartImp.hpp
 *
 * Implementation header of the usart interface
 *
 *  Created on: 23 Dec 2020
 *      Author: jeppa
 */

#ifndef USART_IMP_USARTIMP_HPP_
#define USART_IMP_USARTIMP_HPP_

#include <cstdint>

#include "usart.hpp"

class UsartImp
{
public:
    typedef struct
    {
        volatile uint32_t status;                /* Base address + 0x0 */
        volatile uint32_t data;                  /* Base address + 0x4 */
        volatile uint32_t baudRate;              /* Base address + 0x8 */
        volatile uint32_t control1;              /* Base address + 0xC */
        volatile uint32_t control2;              /* Base address + 0x10 */
        volatile uint32_t control3;              /* Base address + 0x14 */
        volatile uint32_t guardTimeAndPrescaler; /* Base address + 0x18 */
    } registerType;

    UsartImp( void* const usartBaseAddress );

	~UsartImp();
};


#endif /* USART_IMP_USARTIMP_HPP_ */
