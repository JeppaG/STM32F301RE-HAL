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
 * clockGeneratorImp.hpp
 *
 * Implementation header of the clockGenerator interface
 *
 *  Created on: 24 Jul 2020
 *      Author: jeppa
 */

#ifndef CLOCKGENERATOR_IMP_CLOCKGENERATORIMP_HPP_
#define CLOCKGENERATOR_IMP_CLOCKGENERATORIMP_HPP_

#include <cstdint>

#include "clockGenerator.hpp"

class ClockGeneratorCommonImp
{
public:
	typedef struct {
		volatile uint32_t clockControl;                  /* Base address + 0x0 */
		volatile uint32_t pllConfiguration;              /* Base address + 0x4 */
		volatile uint32_t clockConfiguration;            /* Base address + 0x8 */
		volatile uint32_t interrupt;                     /* Base address + 0xC */
		volatile uint32_t ahb1PeripheralReset;           /* Base address + 0x10 */
		volatile uint32_t ahb2PeripheralReset;           /* Base address + 0x14 */
		volatile uint32_t notUsed1;                      /* Base address + 0x18 */
		volatile uint32_t notUsed2;                      /* Base address + 0x1C */
		volatile uint32_t apb1PeripheralReset;           /* Base address + 0x20 */
		volatile uint32_t apb2PeripheralReset;           /* Base address + 0x24 */
		volatile uint32_t notUsed3;                      /* Base address + 0x28 */
		volatile uint32_t notUsed4;                      /* Base address + 0x2C */
		volatile uint32_t ahb1ClockEnable;               /* Base address + 0x30 */
		volatile uint32_t ahb2ClockEnable;               /* Base address + 0x34 */
		volatile uint32_t notUsed5;                      /* Base address + 0x38 */
		volatile uint32_t notUsed6;                      /* Base address + 0x3C */
		volatile uint32_t apb1ClockEnable;               /* Base address + 0x40 */
		volatile uint32_t apb2ClockEnable;               /* Base address + 0x44 */
		volatile uint32_t notUsed7;                      /* Base address + 0x48 */
		volatile uint32_t notUsed8;                      /* Base address + 0x4C */
		volatile uint32_t ahb1LowPowerClockEnable;       /* Base address + 0x50 */
		volatile uint32_t ahb2LowPowerClockEnable;       /* Base address + 0x54 */
		volatile uint32_t notUsed9;                      /* Base address + 0x58 */
		volatile uint32_t notUsed10;                     /* Base address + 0x5C */
		volatile uint32_t apb1LowPowerClockEnable;       /* Base address + 0x60 */
		volatile uint32_t apb2LowPowerClockEnable;       /* Base address + 0x64 */
		volatile uint32_t notUsed11;                     /* Base address + 0x68 */
		volatile uint32_t notUsed12;                     /* Base address + 0x6C */
		volatile uint32_t backupDomainControl;           /* Base address + 0x70 */
		volatile uint32_t controlAndStatus;              /* Base address + 0x74 */
		volatile uint32_t notUsed13;                     /* Base address + 0x78 */
		volatile uint32_t notUsed14;                     /* Base address + 0x7C */
		volatile uint32_t spreadSpectrumClockGeneration; /* Base address + 0x80 */
		volatile uint32_t pllI2sControl;                 /* Base address + 0x84 */
		volatile uint32_t dedicatedClocksConfiguration;  /* Base address + 0x8C */

	} registerType;

	~ClockGeneratorCommonImp();

};

class ClockGeneratorHsiImp : public ClockGeneratorCommonImp, public ClockGenerator
{
public:
	ClockGeneratorHsiImp( void* const rccBaseAddress );

	~ClockGeneratorHsiImp();

private:
	registerType* const rcc;
};

class PeripheralRccImp : public ClockGeneratorCommonImp, public PeripheralRcc
{
public:
	typedef enum
	{
		GPIOA,
		USART1,
		USART2,
		DMA1,
		DMA2
	} peripheralType;

	PeripheralRccImp( void* const rccBaseAddress, const peripheralType peripheralArg );

	~PeripheralRccImp();

	void enableClock();

	uint32_t getClockFrequencyInHz();

private:
	registerType* const rcc;
	peripheralType const peripheral;
};

#endif /* CLOCKGENERATOR_IMP_CLOCKGENERATORIMP_HPP_ */
