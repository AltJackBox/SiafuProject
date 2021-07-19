#ifndef SIMULATION_H
#define SIMULATION_H

#include <mutex>
#include <string>

class World;
class Calendar;
class SimulationData;
class Controller;
class BaseAgentModel;
class BaseWorldModel;
class BaseContextModel;

class Simulation
{

private:
    Controller* control;
    bool ended;
    SimulationData* simData;
    World* world;
    Calendar* time;
    BaseAgentModel* agentModel;
    BaseWorldModel* worldModel;
    BaseContextModel* contextModel;
    int iterationStep;
    bool simulationRunning;
    std::mutex lock; 

    bool isEnded();
    void tickTime();
    void moveAgents();

public:
    Simulation();
    Simulation(std::string simulationPath, Controller* control);

    int day;
    
    void launchSimulation();
    bool isSimulationRunning();
    World* getWorld(); 
    void operator()();
    void die();
    SimulationData* getSimulationData();
};

#endif