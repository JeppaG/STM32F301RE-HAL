#
# Copyright 2020 JG Mechatronics AB
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#****************************************************************************
BUILD_PATH = build
OBJ_PATH = $(BUILD_PATH)/obj
DUT_SOURCE_PATH = ../src
TEST_SOURCE_PATH = .
TEST_LIB_PATH = $(PROJ_ROOT)/cpputest/cpputest_build/lib

G++ = g++
LD = g++

G++_FLAGS = -O0 -c -g -Wall
LD_FLAGS = -g -Wall
        
OBJ :=

INCLUDE_PATH := \
  -I ../if \
  -I ../imp \
  -I $(PROJ_ROOT)/cpputest/include \
