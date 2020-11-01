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

local_dir := $(PROJ_ROOT)/clockGenerator

local_used_if := \
  assert \

local_used_imp := \

local_src := \
  clockGeneratorImp.cpp \

clock_generator_source_path := $(local_dir)/src

clock_generator_include_path := \
  -I $(local_dir)/if \
  -I $(local_dir)/imp \
  $(addprefix -I $(PROJ_ROOT)/, $(addsuffix /if, $(local_used_if))) \
  $(addprefix -I $(PROJ_ROOT)/, $(addsuffix /imp, $(local_used_imp))) \
  
$(OBJ_PATH)/%.o : $(clock_generator_source_path)/%.cpp
	$(G++) $(G++_FLAGS) $(clock_generator_include_path) $< -o$@ 
      		 
OBJ += $(local_src:.cpp=.o)
