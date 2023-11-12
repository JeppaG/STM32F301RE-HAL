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
 * main.cpp
 *
 *  Created on: 4 Jun 2020
 *      Author: jeppa
 */
#include "main.hpp"
#include "sysTick.hpp"

#include <cstdint>

#include "clockGeneratorImp.hpp"
#include "sysTickTimerImp.hpp"
#include "gpioImp.hpp"
#include "exceptionImp.hpp"
#include "usartImp.hpp"
#include "dmaImp.hpp"
#include "serialPortImp.hpp"

void* const scbBaseAddress = reinterpret_cast<void*>( 0xE000ED00 );
void* const rccBaseAddress = reinterpret_cast<void*>( 0x40023800 );
void* const sysTickTimerBaseAddress = reinterpret_cast<void*>( 0xE000E010 );
void* const gpioABaseAddress = reinterpret_cast<void*>( 0x40020000 );
void* const usart1BaseAddress = reinterpret_cast<void*>( 0x40011000 );
void* const usart2BaseAddress = reinterpret_cast<void*>( 0x40004400 );
void* const dma1BaseAddress = reinterpret_cast<void*>( 0x40026000 );
void* const dma2BaseAddress = reinterpret_cast<void*>( 0x40026400 );

ClockGeneratorHsiImp clockGeneratorImp( /* RCC Base Address */ rccBaseAddress );
ClockGenerator* clockGenerator = static_cast<ClockGenerator*>( &clockGeneratorImp );

SysTickTimerImp sysTickTimerImp( /* sysTickTimerBaseAddress */ sysTickTimerBaseAddress,
					             /* ahbClockRateInHz        */ 16000000,
					             /* clockSelect             */ SysTickTimerImp::AHB_CLK_DIV_8 );
Timer* sysTickTimer = static_cast<Timer*>( &sysTickTimerImp );

SysTickHandlerImp sysTickHandlerImp( /* scbBaseAddress */          scbBaseAddress,
                                     /* sysTickTimerBaseAddress */ sysTickTimerBaseAddress );
Exception* sysTickException = static_cast<Exception*>( &sysTickHandlerImp );

PeripheralRccImp gpioARccImp( /* rccBaseAddress */ rccBaseAddress,
		                      /* peripheralRcc  */ PeripheralRccImp::GPIOA );
PeripheralRccImp usart1RccImp( /* rccBaseAddress */ rccBaseAddress,
                               /* peripheralRcc  */ PeripheralRccImp::USART1 );
PeripheralRccImp usart2RccImp( /* rccBaseAddress */ rccBaseAddress,
                               /* peripheralRcc  */ PeripheralRccImp::USART2 );
PeripheralRccImp dma1RccImp( /* rccBaseAddress */ rccBaseAddress,
                             /* peripheralRcc  */ PeripheralRccImp::DMA1 );
PeripheralRccImp dma2RccImp( /* rccBaseAddress */ rccBaseAddress,
                             /* peripheralRcc  */ PeripheralRccImp::DMA2 );
PeripheralRcc* gpioARcc = static_cast<PeripheralRcc*>( &gpioARccImp );
PeripheralRcc* usart1Rcc = static_cast<PeripheralRcc*>( &usart1RccImp );
PeripheralRcc* usart2Rcc = static_cast<PeripheralRcc*>( &usart2RccImp );
PeripheralRcc* dma1Rcc = static_cast<PeripheralRcc*>( &dma1RccImp );
PeripheralRcc* dma2Rcc = static_cast<PeripheralRcc*>( &dma2RccImp );

GpioImp greenLedImp( /* gpioBaseAddress */ gpioABaseAddress,
					 /* peripheralRcc   */ gpioARcc,
					 /* pin             */ GpioImp::pin5 );
Gpio* greenLed = static_cast<Gpio*>( &greenLedImp );

GpioImp usart1TxImp( /* gpioBaseAddress */ gpioABaseAddress,
                     /* peripheralRcc   */ gpioARcc,
                     /* pin             */ GpioImp::pin9 );
GpioImp usart1RxImp( /* gpioBaseAddress */ gpioABaseAddress,
                     /* peripheralRcc   */ gpioARcc,
                     /* pin             */ GpioImp::pin10 );
Gpio* usart1Tx = static_cast<Gpio*>( &usart1TxImp );
Gpio* usart1Rx = static_cast<Gpio*>( &usart1RxImp );

Usart1_2Imp usart1Imp( /* usartBaseAddress */ usart1BaseAddress,
                       /* peripheralRcc    */ usart1Rcc,
                       /* rxPin            */ usart1Rx,
                       /* txPin            */ usart1Tx );
Usart* usart1 = static_cast<Usart*>( &usart1Imp );

GpioImp usart2TxImp( /* gpioBaseAddress */ gpioABaseAddress,
                     /* peripheralRcc   */ gpioARcc,
                     /* pin             */ GpioImp::pin2 );
GpioImp usart2RxImp( /* gpioBaseAddress */ gpioABaseAddress,
                     /* peripheralRcc   */ gpioARcc,
                     /* pin             */ GpioImp::pin3 );
Gpio* usart2Tx = static_cast<Gpio*>( &usart2TxImp );
Gpio* usart2Rx = static_cast<Gpio*>( &usart2RxImp );

Usart1_2Imp usart2Imp( /* usartBaseAddress */ usart2BaseAddress,
                       /* peripheralRcc    */ usart2Rcc,
                       /* rxPin            */ usart2Rx,
                       /* txPin            */ usart2Tx );
Usart* usart2 = static_cast<Usart*>( &usart2Imp );

DmaImp dmaUsart1TxImp( /* dmaBaseAddress */ dma2BaseAddress,
                       /* peripheralRcc  */ dma2Rcc,
                       /* ui8Stream      */ 7,
                       /* ui8Channel     */ 4 );
Dma* dmaUsart1Tx = static_cast<Dma*>( &dmaUsart1TxImp );

DmaImp dmaUsart1RxImp ( /* dmaBaseAddress */ dma2BaseAddress,
                        /* peripheralRcc  */ dma2Rcc,
                        /* ui8Stream      */ 5,
                        /* ui8Channel     */ 4 );
Dma* dmaUsart1Rx = static_cast<Dma*>( &dmaUsart1RxImp );

SerialPortImp serial1Imp ( /* usart */ usart1,
                           /* txDma */ dmaUsart1Tx,
                           /* rxDma */ dmaUsart1Rx );
SerialPort* serial1 = static_cast<SerialPort*>( &serial1Imp );

DmaImp dmaUsart2TxImp( /* dmaBaseAddress */ dma1BaseAddress,
                       /* peripheralRcc  */ dma1Rcc,
                       /* ui8Stream      */ 6,
                       /* ui8Channel     */ 4 );
Dma* dmaUsart2Tx = static_cast<Dma*>( &dmaUsart2TxImp );

void Main::main()
{
	static uint16_t a = 15;
	static uint16_t b = 40;

	uint16_t c = a + b;

	greenLed->setToDigitalOutput();
	sysTickException->setPriority( 255U );
	sysTickException->enable();
	dmaUsart2Tx->setPeripheralAddress( usart2BaseAddress + 4 );
	dmaUsart2Tx->setDirectionMemoryToPeripheral();
	dmaUsart2Tx->setMemoryIncrementalMode();
	usart2->enableDmaTx();
	usart2->enable();
	Exception::enableGlobal();

    while ( true )
	{
	    /* Do nothing */
	}
}

void SysTick::handler()
{
    const char* helloStr = "Hello World\n";
    const char* goodbyeStr = "Goodbye World\n";
    static void* hello = static_cast<void*>( const_cast<char*>( helloStr ) );
    static void* goodbye = static_cast<void*>( const_cast<char*>( goodbyeStr ) );
    static uint16_t count = 1000;
    static bool ledIsOn = false;

    if ( 0 == count )
    {
        if ( ledIsOn )
        {
            greenLed->clear();
            dmaUsart2Tx->setMemory0Address( hello );
            dmaUsart2Tx->setNumberOfData( 12 );
            usart2->clearTxComplete();
            dmaUsart2Tx->enable();
            serial1->transmit( goodbye, 14 );
        }
        else
        {
            greenLed->set();
            dmaUsart2Tx->setMemory0Address( goodbye );
            dmaUsart2Tx->setNumberOfData( 14 );
            usart2->clearTxComplete();
            dmaUsart2Tx->enable();
            serial1->transmit( hello, 12 );
        }
        ledIsOn = !ledIsOn;
        count = 1000;
    }
    count--;
}
/* __dso_handle is apparently expected by the linker */
void* __dso_handle = 0;
