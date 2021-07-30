# Directories.
export SRC_DIR=$(CURDIR)/src
export HDR_DIR=$(CURDIR)/include
export OBJ_DIR=$(CURDIR)/obj
export BIN_DIR=$(CURDIR)/bin
export RSC_DIR=$(CURDIR)/ressources
export GRAD_DIR=$(RSC_DIR)/CalculatedGradients/Simulation-Office

#g++ -I../runtime/src main.cpp -o main

export CC=gcc
export CXX=g++
export RM=rm -rvf

export CPPFLAGS= -I$(HDR_DIR) -MMD -MP -Ofast #-fopenmp -I is a preprocessor flag, not a compiler flag
export CFLAFLGS= -Wall              # some warnings about bad code
export LDFLAGS= -L/usr/lib              # -L is a linker flag
export LDLIBS= -lm                # Left empty if no libs are needed

.PHONY: all simulator test clean

all: simulator

simulator:
	cd $(SRC_DIR) && $(MAKE) all

test: 
	cd $(SRC_DIR) && $(MAKE) test

clean:
	$(RM) $(BIN_DIR)/* $(OBJ_DIR)/*




