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
    bool paused;
    World* world;
    Calendar* time;
    BaseAgentModel* agentModel;
    BaseWorldModel* worldModel;
    BaseContextModel* contextModel;
    int iterationStep;
    //SimulatorOutputPrinter outputPrinter;
    bool simulationRunning;
    //XMLConfiguration siafuConfig;
    std::mutex lock; 

    /*synchronized*/ bool isEnded();
    void tickTime();

public:
    Simulation();
    Simulation(std::string simulationPath, Controller* control);
    void launchSimulation();
    bool isSimulationRunning();
    World* getWorld(); 
    /*synchronized*/ bool isPaused();
    void operator()();
    void die();
    SimulationData* getSimulationData();
};

#endif