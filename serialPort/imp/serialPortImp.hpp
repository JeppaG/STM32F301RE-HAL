/*
 * Copyright 2023 JG Mechatronics AB
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
 * serialPortImp.hpp
 *
 * Implementation header of the serialPort interface
 *
 *  Created on: 04 Mar 2020
 *      Author: jeppa
 */

#ifndef SERIAL_IMP_SERIALPORTIMP_HPP_
#define SERIAL_IMP_SERIALPORTIMP_HPP_

#include <cstdint>
#include "usart.hpp"
#include "dma.hpp"
#include "serialPort.hpp"

class SerialPortImp:public SerialPort
{
public:

    SerialPortImp( Usart* usart,
                   Dma*   txDma,
                   Dma*   rxDma );

    void transmit( void* buffer, uint16_t size ) override;
    uint16_t receive( void* buffer, uint16_t size ) override;

    ~SerialPortImp();

private:
    Usart*   const usart;
    Dma*     const txDma;
    Dma*     const rxDma;
    uint16_t rxBufferSize;
};


#endif /* SERIAL_IMP_SERIALPORTIMP_HPP_ */
