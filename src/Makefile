#g++ -I../runtime/src main.cpp -o main

SRCS=$(wildcard siafu/*.cpp) \
	$(wildcard siafu/test/*.cpp) \
	$(wildcard model/*.cpp) \

OBJS=$(OBJ_DIR)/Controller.o $(OBJ_DIR)/ConsoleProgress.o $(OBJ_DIR)/t_Controller.o $(OBJ_DIR)/World.o $(OBJ_DIR)/Simulation.o $(OBJ_DIR)/t_Simulation.o

TEST=$(BIN_DIR)/t_Controller $(BIN_DIR)/t_Simulation

.PHONY: all test

all: test

test: $(TEST)

$(TEST): $(OBJS)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/t_Controller $(OBJ_DIR)/Controller.o $(OBJ_DIR)/ConsoleProgress.o $(OBJ_DIR)/World.o $(OBJ_DIR)/SimulationData.o $(OBJ_DIR)/Simulation.o $(OBJ_DIR)/t_Controller.o -lpthread
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/t_Simulation $(OBJ_DIR)/Controller.o $(OBJ_DIR)/ConsoleProgress.o  $(OBJ_DIR)/World.o $(OBJ_DIR)/SimulationData.o $(OBJ_DIR)/Simulation.o $(OBJ_DIR)/t_Simulation.o -lpthread


$(OBJS): $(SRCS)
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/Controller.cpp -o $(OBJ_DIR)/Controller.o
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/progress/ConsoleProgress.cpp -o $(OBJ_DIR)/ConsoleProgress.o
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/test/t_Controller.cpp -o $(OBJ_DIR)/t_Controller.o
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/model/SimulationData.cpp -o $(OBJ_DIR)/SimulationData.o
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/model/World.cpp -o $(OBJ_DIR)/World.o
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/Simulation.cpp -o $(OBJ_DIR)/Simulation.o
	$(CXX) $(CPPFLAGS) -c $(SRC_DIR)/siafu/test/t_Simulation.cpp -o $(OBJ_DIR)/t_Simulation.o