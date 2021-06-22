#g++ -I../runtime/src main.cpp -o main

SRCS=$(wildcard siafu/*.cpp) \
	$(wildcard siafu/test/*.cpp) \
	$(wildcard model/*.cpp) \
	$(wildcard model/test/*.cpp) \
	$(wildcard progress/*.cpp) \
	$(wildcard types/*.cpp) \
	$(wildcard *.cpp) \

#OBJS=$(OBJ_DIR)/Controller.o $(OBJ_DIR)/Progress.o $(OBJ_DIR)/t_Controller.o $(OBJ_DIR)/World.o $(OBJ_DIR)/Simulation.o $(OBJ_DIR)/t_Simulation.o
OBJS  := $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJS:.o=.d)

TEST=t_Controller t_Simulation

all: build test

test: $(BIN_DIR)/$(TEST)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

$(BIN_DIR)/$(TEST): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/$(TEST) $^ -lpthread

-include $(DEPENDENCIES)

.PHONY: all build test

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

#$(TEST): $(OBJS) \
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/t_Controller $(OBJ_DIR)/Controller.o $(OBJ_DIR)/Progress.o $(OBJ_DIR)/World.o $(OBJ_DIR)/SimulationData.o $(OBJ_DIR)/Simulation.o $(OBJ_DIR)/t_Controller.o -lpthread \
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/t_Simulation $(OBJ_DIR)/Controller.o $(OBJ_DIR)/Progress.o  $(OBJ_DIR)/World.o $(OBJ_DIR)/SimulationData.o $(OBJ_DIR)/Simulation.o $(OBJ_DIR)/t_Simulation.o -lpthread


#$(OBJS): $(SRCS) \
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/Controller.cpp -o $(OBJ_DIR)/Controller.o \
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/progress/Progress.cpp -o $(OBJ_DIR)/Progress.o \
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/test/t_Controller.cpp -o $(OBJ_DIR)/t_Controller.o \
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/model/SimulationData.cpp -o $(OBJ_DIR)/SimulationData.o \
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/model/World.cpp -o $(OBJ_DIR)/World.o \
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/Simulation.cpp -o $(OBJ_DIR)/Simulation.o \
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/test/t_Simulation.cpp -o $(OBJ_DIR)/t_Simulation.o



