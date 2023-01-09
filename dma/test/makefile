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
 
PROJ_ROOT = ../..

include $(PROJ_ROOT)/testCommon/commonHeader.mk 

# Source file list

DUT_SOURCE = \
  dmaImp.cpp \
  
TEST_SOURCE = \
  dmaTest.cpp \
  
USED_UNITS = \
  include $(PROJ_ROOT)/assert/mock/make.mk
  include $(PROJ_ROOT)/clockGenerator/mock/make.mk
  
include $(PROJ_ROOT)/testCommon/commonFooter.mk