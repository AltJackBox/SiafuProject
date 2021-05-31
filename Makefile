# Directories.
SRC_DIR=$(CURDIR)/src
HDR_DIR=$(CURDIR)/include
OBJ_DIR=$(CURDIR)/obj
BIN_DIR=$(CURDIR)/bin

#g++ -I../runtime/src main.cpp -o main

CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS= -I$(HDR_DIR) -MMD -MP # -I is a preprocessor flag, not a compiler flag
CFLAFLGS= -Wall              # some warnings about bad code
LDFLAGS= -Llib              # -L is a linker flag
LDLIBS= -lm                # Left empty if no libs are needed

SRCS=$(SRC_DIR)/siafu/Siafu.cpp $(SRC_DIR)/siafu/Controller.cpp
OBJS=$(OBJ_DIR)/Controller.o $(OBJ_DIR)/Siafu.o
HDRS=$(HDR_DIR)/siafu/Controller.h 

EXE=$(BIN_DIR)/programme

.PHONY: all test clean

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(EXE) $(OBJS) 

$(OBJS): $(SRCS)
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/Controller.cpp -o $(OBJ_DIR)/Controller.o
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/Siafu.cpp -o $(OBJ_DIR)/Siafu.o

test: 
	cd $(SRC_DIR) && $(MAKE) test

clean:
	$(RM) $(BIN_DIR)/* $(OBJ_DIR)/*



