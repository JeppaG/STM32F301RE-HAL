#
# Copyright 2023 JG Mechatronics AB
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

local_dir := $(PROJ_ROOT)/dma

local_src := \
  dmaMock.cpp \

dma_mock_source_path := $(local_dir)/mock/src

INCLUDE_PATH += -I $(local_dir)/if
INCLUDE_PATH += -I $(local_dir)/mock/inc 
  
$(OBJ_PATH)/%.o : $(dma_mock_source_path)/%.cpp
	$(G++) $(G++_FLAGS) $(INCLUDE_PATH) $< -o$@ 
      		 
OBJ += $(local_src:.cpp=.o)

