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
 * exceptionImp.hpp
 *
 *  Created on: 28 Sep 2020
 *      Author: jeppa
 */

#ifndef EXCEPTION_IMP_EXCEPTIONIMP_HPP_
#define EXCEPTION_IMP_EXCEPTIONIMP_HPP_

#include "exception.hpp"

class SystemHandlerCommonImp
{
protected:
	SystemHandlerCommonImp( void* scbBaseAddress );

	virtual ~SystemHandlerCommonImp();

	typedef struct
	{
		volatile uint32_t auxiliaryControl;
		volatile uint32_t cpuId;
		volatile uint32_t intrruptCtontrolAndState;
		volatile uint32_t vectorTableOffset;
		volatile uint32_t applicationInterruptAndResetControl;
		volatile uint32_t systemControl;
		volatile uint32_t configurationAndControl;
		volatile uint8_t  memoryManagementFaultPriority;
		volatile uint8_t  busFaultPriority;
		volatile uint8_t  usageFaultPriority;
		volatile uint8_t  reserved1;
		volatile uint8_t  reserved2;
		volatile uint8_t  reserved3;
		volatile uint8_t  reserved4;
		volatile uint8_t  svCallPriority;
		volatile uint8_t  reserved5;
		volatile uint8_t  reserved6;
		volatile uint8_t  pendSvPriority;
		volatile uint8_t  sysTickPriority;
		volatile uint32_t systemHandlerControlAndState;
		volatile uint32_t configurableFaultStatus;
		volatile uint32_t hardFaultStatus;
		volatile uint32_t addressOfMemoryManagementFault;
		volatile uint32_t addressOfBusFault;
		volatile uint32_t auxiliaryFaultStatus;
	} registerType;

	registerType* const scb;
};

class SysTickHandlerImp : public Exception, private SystemHandlerCommonImp
{
public:
	SysTickHandlerImp( void* const scbBaseAddress,
					   void* const sysTickTimerBaseAddress );

	virtual void setPriority( uint8_t priority );

	virtual void enable();

	virtual ~SysTickHandlerImp();

private:
	typedef struct {
		volatile uint32_t controlAndStatus;              /* Base address + 0x0 */
		volatile uint32_t reloadValue;                   /* Base address + 0x4 */
		volatile uint32_t currentValue;                  /* Base address + 0x8 */
		volatile uint32_t calibrationValue;              /* Base address + 0xC */
	} registerType;

	registerType* const stk;

};

#endif /* EXCEPTION_IMP_EXCEPTIONIMP_HPP_ */
