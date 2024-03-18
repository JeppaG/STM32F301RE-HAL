/*
 * Copyright 2024 JG Mechatronics AB
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
 * adcImp.cpp
 *
 *  Created on: 18 Mar 2024
 *      Author: jeppa
 */

#include "adcImp.hpp"

AdcImp::AdcImp( void* const          adcBaseAddress,
                void* const          adcCommonBaseAddress,
                PeripheralRcc* const pRcc ):
    adc( static_cast<registerType* const>( adcBaseAddress ) ),
    adcCommon( static_cast<commonRegisterType* const>( adcCommonBaseAddress ) ),
    rcc  ( pRcc )
{
    rcc->enableClock();
}


AdcImp::~AdcImp()
{
}

Adc::~Adc()
{
	/* C++ demands that even a pure virtual destructor has an implementation */
}

