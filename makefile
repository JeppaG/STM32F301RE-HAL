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

# The script requires that the environment variable GNU_ARM_TOOL_PATH is defined and points to the 
# directory where the build tools are found.
TOOL_PATH = $(GNU_ARM_TOOL_PATH)/bin
PROJ_ROOT = .
BUILD_PATH = build
OBJ_PATH = obj

G++ = $(TOOL_PATH)/arm-none-eabi-g++
LD = $(TOOL_PATH)/arm-none-eabi-g++

G++_FLAGS = -O0 -c -g -march=armv7e-m -mcpu=cortex-m4 -mthumb -xc++ -std=gnu++14 -MMD -MP \
            -mfloat-abi=hard -mfpu=fpv4-sp-d16

LD_FLAGS = -Tstm32f410RB.ld -march=armv7e-m -mcpu=cortex-m4 -mthumb -fno-exceptions --specs=nosys.specs \
           -nostartfiles -fno-unwind-tables -fno-rtti -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 \
           -fsigned-char -ffunction-sections -fdata-sections -ffreestanding --specs=nano.specs \
           -fno-move-loop-invariants -Xlinker
#-fno-use-cxa-atexit 
        
$(shell mkdir -p $(BUILD_PATH))
$(shell mkdir -p $(OBJ_PATH))
  
OBJ :=

include main/make.mk
include startup/make.mk
include exception/make.mk
include clockGenerator/make.mk
include gpio/make.mk
include timer/make.mk
include assert/make.mk
include usart/make.mk

$(BUILD_PATH)/main.elf : $(addprefix $(OBJ_PATH)/, $(OBJ))
	$(LD) $(LD_FLAGS) $^ -o$@
		 
clean :
	rm $(BUILD_PATH)/main.elf $(OBJ_PATH)/*.*
	
-include $(addprefix $(OBJ_PATH), $(OBJ:.o=.d))
    
.PHONY : debug

debug : ; $(info OBJ is [$(OBJ)])

all : $(BUILD_PATH)/main.elf