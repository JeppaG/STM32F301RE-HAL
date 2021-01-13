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
 * gpioImp.hpp
 *
 *  Created on: 28 Sep 2020
 *      Author: jeppa
 */

#ifndef GPIO_IMP_GPIOIMP_HPP_
#define GPIO_IMP_GPIOIMP_HPP_

#include <cstdint>

#include "gpio.hpp"
#include "clockGenerator.hpp"

class GpioImp : public Gpio
{
public:

	GpioImp( void* const          gpioBaseAddress,
	         PeripheralRcc*       peripheralRcc,
		     const uint32_t       pinNumber );

	virtual void setToDigitalOutput();
    virtual void setToAlternateFunction( const uint32_t alternateFunction );
    virtual	void set();
	virtual void clear();

	~GpioImp();

private:
	typedef struct
	{
		volatile uint32_t mode;              /* Base address + 0x0 */
		volatile uint32_t outputType;        /* Base address + 0x4 */
		volatile uint32_t outputSpeed;       /* Base address + 0x8 */
		volatile uint32_t pullUpDown;        /* Base address + 0xC */
		volatile uint32_t inputData;         /* Base address + 0x10 */
		volatile uint32_t outputData;        /* Base address + 0x14 */
		volatile uint32_t bitSetReset;       /* Base address + 0x18 */
		volatile uint32_t configurationLock; /* Base address + 0x1C */
		volatile uint32_t alternateFunctionLow; /* Base address + 0x20 */
		volatile uint32_t alternateFunctionHigh; /* Base address + 0x24 */
	} registerType;

	registerType*  const gpio;
	PeripheralRcc* rcc;
	uint32_t       const pin;
};

#endif /* GPIO_IMP_GPIOIMP_HPP_ */
