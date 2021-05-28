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

SRCS=$(SRC_DIR)/siafu/Siafu.cpp
OBJS=$(OBJ_DIR)/Siafu.o
HDRS=$(HDR_DIR)/siafu/Siafu.h

EXE=$(BIN_DIR)/programme

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJS) 
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(EXE) $(OBJS) 

$(OBJS): $(SRCS)
	$(CXX) $(CPPFLAGS) -c $(SRCS) -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@ #creates directory if it does not exists

clean:
	$(RM) $(BIN_DIR)/* $(OBJ_DIR)/* # The @ disables the echoing of the command



