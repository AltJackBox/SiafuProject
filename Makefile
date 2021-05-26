# Directories.
export SRCDIR   = $(CURDIR)/src
export HDRDIR   = $(CURDIR)/include

CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=SRCDIR/siafu/Siafu.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
    $(CXX) $(LDFLAGS) -o main $(OBJS) $(LDLIBS)

main.o: Siafu.cpp
    g++ $(CPPFLAGS) -c Siafu.cpp

clean:
    $(RM) $(OBJS)