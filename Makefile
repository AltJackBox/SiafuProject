# Directories.
SRC_DIR=$(CURDIR)/src
HDR_DIR=$(CURDIR)/include
OBJ_DIR=$(CURDIR)/obj
BIN_DIR=$(CURDIR)/bin

CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS= -Iinclude -MMD -MP # -I is a preprocessor flag, not a compiler flag
CFLAFLGS= -Wall              # some warnings about bad code
LDFLAGS= -Llib              # -L is a linker flag
LDLIBS= -lm                # Left empty if no libs are needed

SRCS=$(SRC_DIR)/siafu/Siafu.cpp
OBJS=$(patsubst $(SRC_DIR)/siafu/Siafu.cpp, $(OBJ_DIR)/%.o, $(SRCS))

EXE=$(BIN_DIR)/main

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
    $(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
    $(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
    mkdir -p $@ #creates directory if it does not exists

clean:
    @$(RM) -rv $(BIN_DIR) $(OBJ_DIR) # The @ disables the echoing of the command

