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

TOPTARGETS := all run clean
PROJ_ROOT = ..

UNITS := \
    clockGenerator \
    exception \
    gpio \
    timer \
    usart \
    dma \
    serialPort \
    
TEST_DIRS := $(addsuffix /test, $(addprefix $(PROJ_ROOT)/, $(UNITS)))

$(TOPTARGETS): $(TEST_DIRS)
$(TEST_DIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
	
.PHONY: $(TOPTARGETS) $(TEST_DIRS)
