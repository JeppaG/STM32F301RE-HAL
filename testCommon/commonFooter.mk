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
   
$(shell mkdir -p $(BUILD_PATH))
$(shell mkdir -p $(OBJ_PATH))
  
OBJ += $(DUT_SOURCE:.cpp=.o)
OBJ += $(TEST_SOURCE:.cpp=.o)

$(OBJ_PATH)/%.o : $(DUT_SOURCE_PATH)/%.cpp
	$(G++) $(G++_FLAGS) $(INCLUDE_PATH) $< -o$@ 
      
$(OBJ_PATH)/%.o : $(TEST_SOURCE_PATH)/%.cpp
	$(G++) $(G++_FLAGS) $(INCLUDE_PATH) $< -o$@
	
$(BUILD_PATH)/test.exe : $(addprefix $(OBJ_PATH)/, $(OBJ))
	$(LD) $(LD_FLAGS) $^ $(TEST_LIB_PATH)/libCppUTest.a $(TEST_LIB_PATH)/libCppUTestExt.a -o$@
		 
clean :
	rm $(BUILD_PATH)/test.exe $(OBJ_PATH)/*.*
	
-include $(addprefix $(OBJ_PATH), $(OBJ:.o=.d))
    
.PHONY : debug
sp := 
sp +=
debug : ; $(info $$(USED_UNITS) is [ $(USED_UNITS) ])
	
all : $(BUILD_PATH)/test.exe

run : $(BUILD_PATH)/test.exe
	$(BUILD_PATH)/test.exe