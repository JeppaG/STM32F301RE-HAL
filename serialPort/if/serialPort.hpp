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
 * serialPort.hpp
 *
 * Application interface of the serialPort
 *
 *  Created on: 04 Mar 2023
 *      Author: jeppa
 */

#ifndef SERIALPORT_IF_SERIALPORT_HPP_
#define SERIALPORT_IF_SERIALPORT_HPP_

class SerialPort
{
public:
    virtual ~SerialPort() = 0;
};
#endif /* SERIALPORT_IF_SERIALPORT_HPP_ */
