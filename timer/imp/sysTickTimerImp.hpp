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
 * sysTickTimerImp.hpp
 *
 *  Created on: 2 Sep 2020
 *      Author: jeppa
 */

#ifndef TIMER_IMP_SYSTICKTIMERIMP_HPP_
#define TIMER_IMP_SYSTICKTIMERIMP_HPP_

#include <cstdint>

#include "timer.hpp"

class SysTickTimerImp : public Timer
{
public:
	typedef enum {
		AHB_CLK_DIV_8 = 0,
	} clockSelectType;

	SysTickTimerImp( void* const           sysTickTimerBaseAddress,
					 const uint32_t        ahbClockRateInHz,
					 const clockSelectType clockSelect );

	~SysTickTimerImp();

private:
	typedef struct {
		volatile uint32_t controlAndStatus;              /* Base address + 0x0 */
		volatile uint32_t reloadValue;                   /* Base address + 0x4 */
		volatile uint32_t currentValue;                  /* Base address + 0x8 */
		volatile uint32_t calibrationValue;              /* Base address + 0xC */
	} registerType;

	registerType* const stk;
};

#endif /* TIMER_IMP_SYSTICKTIMERIMP_HPP_ */
