#g++ -I../runtime/src main.cpp -o main

SRCS=$(wildcard siafu/*.cpp) \
	$(wildcard siafu/test/*.cpp) \

OBJS=$(OBJ_DIR)/Controller.o $(OBJ_DIR)/ConsoleProgress.o $(OBJ_DIR)/t_Controller.o
HDRS=$(HDR_DIR)/siafu/Controller.h $(HDR_DIR)/progress/ConsoleProgress.h

TEST=$(BIN_DIR)/test

.PHONY: all test

all: test

test: $(TEST)

$(TEST): $(OBJS)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(TEST) $(OBJS) 

$(OBJS): $(SRCS)
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/Controller.cpp -o $(OBJ_DIR)/Controller.o
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/test/t_Controller.cpp -o $(OBJ_DIR)/t_Controller.o