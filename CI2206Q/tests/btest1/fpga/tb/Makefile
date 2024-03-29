# SPDX-FileCopyrightText: 2020 Efabless Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0


# ---- Include Partitioned Makefiles ----

 
#######################################################################
## Caravel Verilog for Integration Tests
#######################################################################

DESIGNS?=../

export RTL_DIR ?=  $(DESIGNS)/rtl


## Simulation mode: RTL/GL
SIM?=RTL
DUMP?=OFF

### To Enable IVERILOG FST DUMP
export IVERILOG_DUMPER = fst


.SUFFIXES:

PATTERN = tb_top

all:  ${PATTERN:=.vcd}


vvp:  ${PATTERN:=.vvp}

%.vvp: %.v
ifeq ($(SIM),RTL)
   ifeq ($(DUMP),OFF)
	iverilog -g2012 -DFUNCTIONAL -DSIM \
	-ffilelist.f \
	$< -o $@ 
    else  
	iverilog -g2012 -DWFDUMP -DFUNCTIONAL -DSIM \
	-ffilelist.f \
	$< -o $@ 
   endif
else  
   ifeq ($(DUMP),OFF)
	iverilog -g2012 -DFUNCTIONAL -DUSE_POWER_PINS -DGL \
	-ffilelist.f \
	$< -o $@ 
    else  
	iverilog -g2012 -DWFDUMP -DFUNCTIONAL -DUSE_POWER_PINS -DGL \
	-ffilelist.f \
	$< -o $@ 
   endif
endif

%.vcd: %.vvp
	vvp $< 


# ---- Clean ----

clean:
	rm -f *.vvp *.vcd *.log 

.PHONY: clean hex all
