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
 * startup.cpp
 *
 *  Created on: 3 Jun 2020
 *      Author: jeppa
 */

/*********************************************************************
 * Symbols defined in the linker script
 */

#include "../../startup/if/startup.hpp"

#include <cstdint>
#include <cstring>

#include "../if/main.hpp"

/* Imported symbols from the linker script */

extern uint8_t __text_end__;
extern uint8_t __data_start__;
extern uint8_t __data_end__;
extern uint8_t __bss_start__;
extern uint8_t __bss_end__;
extern uint8_t __ctors_start__;
extern uint8_t __ctors_end__;
extern uint8_t _HEAP_START;
extern uint8_t _HEAP_END;


void Startup::lowLevelInit()
{
	/* Copy data belonging to the '.data' section from its
	 * load time position on flash (ROM) to its run time position
	 * in SRAM.
	 */
	memcpy( reinterpret_cast<void*>( &__data_start__ ),
		    reinterpret_cast<const void*>( &__text_end__ ),
		    &__data_end__ - &__data_start__ );

	/* Initialize data in the '.bss' section to zeros.
	 */
	memset( reinterpret_cast<void*>( &__bss_start__ ),
			0,
			&__bss_end__ - &__bss_start__ );

	/* Call C++ constructors for static objects
	 */
	Startup::ctorType* firstCtor = reinterpret_cast<Startup::ctorType*>( &__ctors_start__ );
	Startup::ctorType* lastCtor = reinterpret_cast<Startup::ctorType*>( &__ctors_end__ );
	for ( Startup::ctorType* p = firstCtor; p < lastCtor; ++p )
	{
		(*p)();
	}

	/* Call the 'main()'"function defined in 'test_program.cpp'.
	 */
	Main::main();
}

