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
 * exceptionImp.cpp
 *
 *  Created on: 20 Dec 2020
 *      Author: jeppa
 */

#include "exception.hpp"
#include "startup.hpp"
/********************************************************************
 * Interfaces that are needed for the exception vector table
 */
#include "sysTick.hpp"

/*********************************************************************
 * Symbols defined in the linker script
 */
extern uintptr_t __stack_end__;

/**********************************************************************
 * Exception vector
 */
const Exception::handlerType Exception::__vector_table__[]
	__attribute__((section(".vectors")))
{
	/* Stack pointer    */	reinterpret_cast<handlerType>( &__stack_end__),
	/* Code entry point */	Startup::lowLevelInit,
	/* NMI              */  defaultHandler,
	/* HardFault        */  defaultHandler,
    /* MemManage        */  defaultHandler,
    /* BusFault         */  defaultHandler,
    /* UsageFault       */  defaultHandler,
    /* Reserved         */  reinterpret_cast<handlerType>( 0 ),
    /* Reserved         */  reinterpret_cast<handlerType>( 0 ),
    /* Reserved         */  reinterpret_cast<handlerType>( 0 ),
    /* Reserved         */  reinterpret_cast<handlerType>( 0 ),
    /* SVCall           */  defaultHandler,
    /* Debug Monitor    */  defaultHandler,
    /* Reserved         */  reinterpret_cast<handlerType>( 0 ),
    /* PendSV           */  defaultHandler,
    /* SysTick          */  SysTick::handler,
};

void Exception::defaultHandler()
{

}
