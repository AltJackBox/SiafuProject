#g++ -I../runtime/src main.cpp -o main

SRCS=$(wildcard siafu/*.cpp) \
	$(wildcard siafu/test/*.cpp) \
	$(wildcard model/*.cpp) \
	$(wildcard model/test/*.cpp) \
	$(wildcard progress/*.cpp) \
	$(wildcard types/*.cpp) \
	$(wildcard *.cpp) \

OBJS  := $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJS:.o=.d)

TEST0=t_RandomGen
TEST0_DEP=$(OBJ_DIR)/office/test/t_RandomGen.o

TEST1=t_stb
TEST1_DEP=$(OBJ_DIR)/model/test/t_stb.o

TEST2=t_Simulation
TEST2_DEP=$(OBJ_DIR)/siafu/Controller.o $(OBJ_DIR)/progress/Progress.o  $(OBJ_DIR)/model/World.o $(OBJ_DIR)/model/SimulationData.o \
	$(OBJ_DIR)/siafu/Simulation.o $(OBJ_DIR)/model/Position.o $(OBJ_DIR)/model/Place.o $(OBJ_DIR)/model/Gradient.o $(OBJ_DIR)/model/Agent.o $(OBJ_DIR)/Calendar.o \
	$(OBJ_DIR)/model/CoordinateTools.o $(OBJ_DIR)/office/AgentModel.o $(OBJ_DIR)/office/WorldModel.o $(OBJ_DIR)/office/Constants.o \
	$(OBJ_DIR)/utils/PersistentCachedMap.o $(OBJ_DIR)/types/BooleanType.o $(OBJ_DIR)/types/EasyTime.o $(OBJ_DIR)/types/Text.o \
	$(OBJ_DIR)/types/TimePeriod.o $(OBJ_DIR)/siafu/test/t_Simulation.o

TEST3=t_SimulationData
TEST3_DEP=$(OBJ_DIR)/model/SimulationData.o $(OBJ_DIR)/model/test/t_SimulationData.o

TEST4=t_World
TEST4_DEP=$(OBJ_DIR)/siafu/Controller.o $(OBJ_DIR)/progress/Progress.o  $(OBJ_DIR)/model/World.o $(OBJ_DIR)/model/SimulationData.o \
	$(OBJ_DIR)/siafu/Simulation.o $(OBJ_DIR)/model/Position.o $(OBJ_DIR)/model/Place.o $(OBJ_DIR)/model/Gradient.o $(OBJ_DIR)/model/Agent.o $(OBJ_DIR)/Calendar.o \
	$(OBJ_DIR)/model/CoordinateTools.o $(OBJ_DIR)/model/test/t_World.o

TEST5=t_PersistentCachedMap
TEST5_DEP=$(OBJ_DIR)/siafu/Controller.o $(OBJ_DIR)/progress/Progress.o  $(OBJ_DIR)/model/World.o $(OBJ_DIR)/model/SimulationData.o \
	$(OBJ_DIR)/siafu/Simulation.o $(OBJ_DIR)/model/Position.o $(OBJ_DIR)/model/Place.o $(OBJ_DIR)/model/Gradient.o $(OBJ_DIR)/model/Agent.o $(OBJ_DIR)/Calendar.o \
	$(OBJ_DIR)/model/CoordinateTools.o $(OBJ_DIR)/office/AgentModel.o $(OBJ_DIR)/office/WorldModel.o $(OBJ_DIR)/office/Constants.o \
	$(OBJ_DIR)/utils/PersistentCachedMap.o $(OBJ_DIR)/types/BooleanType.o $(OBJ_DIR)/types/EasyTime.o $(OBJ_DIR)/types/Text.o \
	$(OBJ_DIR)/types/TimePeriod.o $(OBJ_DIR)/utils/test/t_PersistentCachedMap.o 


	

all: build test

test: $(OBJS) $(BIN_DIR)/$(TEST2)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -c $< -o $@ 

$(BIN_DIR)/$(TEST0) : $(TEST0_DEP)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/$(TEST0) $^

$(BIN_DIR)/$(TEST1) : $(TEST1_DEP)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/$(TEST1) $^

$(BIN_DIR)/$(TEST2) : $(TEST2_DEP)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/$(TEST2) $^ -lstdc++fs -lpthread

$(BIN_DIR)/$(TEST3) : $(TEST3_DEP)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/$(TEST3) $^ -lstdc++fs

$(BIN_DIR)/$(TEST4) : $(TEST4_DEP)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/$(TEST4) $^ -lstdc++fs -lpthread

$(BIN_DIR)/$(TEST5) : $(TEST5_DEP)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(BIN_DIR)/$(TEST5) $^ -lstdc++fs -lpthread

-include $(DEPENDENCIES)

.PHONY: all build test

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)



