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
 * exception.hpp
 *
 * Application interface of exceptions.
 *
 *  Created on: 28 Sep 2020
 *      Author: jeppa
 */

#ifndef MAIN_IF_SYS_TICK_HPP_
#define MAIN_IF_SYS_TICK_HPP_

#include <cstdint>


class SysTick
{
public:
    // the exception-handler needs to be public in order to be accessed from the exception vector
    static void handler();

private:
};

#endif /* MAIN_IF_SYS_TICK_HPP_ */
