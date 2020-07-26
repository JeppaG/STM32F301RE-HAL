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
#APP_SOURCE_PATH = application/src/
DRV_SOURCE_PATH = src/
#DRV_ASM_PATH = driver/asm/

G++ = arm-none-eabi-g++
LD = arm-none-eabi-g++

#G++_FLAGS = -O0 -c -g -mcpu=cortex-m4 -mthumb -std=c++11
G++_FLAGS = -O0 -c -g -march=armv7e-m -mcpu=cortex-m4 -mthumb -xc++ -std=gnu++14 -MMD -MP -mfloat-abi=hard -mfpu=fpv4-sp-d16
#LD_FLAGS = -Tstm32f401RE.ld -mcpu=cortex-m4 -mthumb -fno-exceptions --specs=nosys.specs \
           -nostartfiles -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 \
           -fsigned-char -ffunction-sections -fdata-sections -ffreestanding \
           -fno-move-loop-invariants -Xlinker
LD_FLAGS = -Tstm32f401RE.ld -march=armv7e-m -mcpu=cortex-m4 -mthumb -fno-exceptions --specs=nosys.specs \
           -nostartfiles -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 \
           -fsigned-char -ffunction-sections -fdata-sections -ffreestanding \
           -fno-move-loop-invariants -Xlinker
        
# Source file list

APP_SOURCE = \
  
DRIVER_SOURCE = \
  exception.cpp \
  main.cpp \
  startup.cpp \
    
INCLUDE_PATH = \
  -I inc \
  
$(shell mkdir -p $(BUILD_PATH))
$(shell mkdir -p $(OBJ_PATH))
  
OBJ = $(APP_SOURCE:.cpp=.o) \
      $(DRIVER_SOURCE:.cpp=.o)

$(OBJ_PATH)/%.o : $(APP_SOURCE_PATH)%.cpp
	$(G++) $(G++_FLAGS) $(INCLUDE_PATH) $< -o$@ 
      
$(OBJ_PATH)/%.o : $(DRV_SOURCE_PATH)%.cpp
	$(G++) $(G++_FLAGS) $(INCLUDE_PATH) $< -o$@
	
$(BUILD_PATH)/main.elf : $(addprefix $(OBJ_PATH)/, $(OBJ))
	$(LD) $(LD_FLAGS) $^ -o$@
		 
clean :
	rm $(BUILD_PATH)/main.elf $(OBJ_PATH)/*.*
	
-include $(addprefix $(OBJ_PATH), $(OBJ:.o=.d))
    
.PHONY : debug

debug : ; $(info $$(addprefix $(OBJ_PATH), $(OBJ)) is [$(addprefix $(OBJ_PATH), $(OBJ))])
	
all : $(BUILD_PATH)/main.elf