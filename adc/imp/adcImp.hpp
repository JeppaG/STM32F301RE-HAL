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
 * usartImp.hpp
 *
 * Implementation header of the usart interface
 *
 *  Created on: 18 March 2024
 *      Author: jeppa
 */

#ifndef ADC_IMP_ADCIMP_HPP_
#define ADC_IMP_ADCIMP_HPP_

#include <cstdint>

#include "adc.hpp"
#include "clockGenerator.hpp"
#include "gpio.hpp"

class AdcImp:public Adc
{
public:
    typedef struct
    {
        volatile uint32_t status;                 /* Base address + 0x0 */
        volatile uint32_t control1;               /* Base address + 0x4 */
        volatile uint32_t control2;               /* Base address + 0x8 */
        volatile uint32_t sampleTime1;            /* Base address + 0xC */
        volatile uint32_t sampleTime2;            /* Base address + 0x10 */
        volatile uint32_t injectedChannelOffset1; /* Base address + 0x14 */
        volatile uint32_t injectedChannelOffset2; /* Base address + 0x18 */
        volatile uint32_t injectedChannelOffset3; /* Base address + 0x1C */
        volatile uint32_t injectedChannelOffset4; /* Base address + 0x20 */
        volatile uint32_t watchdogHighThreshold;  /* Base address + 0x24 */
        volatile uint32_t watchdogLowThreshold;   /* Base address + 0x28 */
        volatile uint32_t regularSequence1;       /* Base address + 0x2C */
        volatile uint32_t regularSequence2;       /* Base address + 0x30 */
        volatile uint32_t regularSequence3;       /* Base address + 0x34 */
        volatile uint32_t injectedSequence;       /* Base address + 0x38 */
        volatile uint32_t injectedData1;          /* Base address + 0x3C */
        volatile uint32_t injectedData2;          /* Base address + 0x40 */
        volatile uint32_t injectedData3;          /* Base address + 0x44 */
        volatile uint32_t injectedData4;          /* Base address + 0x48 */
        volatile uint32_t regularData;            /* Base address + 0x4C */
    } registerType;

    typedef struct
    {
        volatile uint32_t status;                 /* Base address + 0x0 */
        volatile uint32_t control;                /* Base address + 0x4 */
    } commonRegisterType;

    AdcImp( void* const          adcBaseAddress,
            void* const          adcCommonBaseAdress,
            PeripheralRcc* const pRcc );

	~AdcImp();

private:
	registerType* const       adc;
	commonRegisterType* const adcCommon;
	PeripheralRcc* const      rcc;
};


#endif /* ADC_IMP_ADCIMP_HPP_ */
