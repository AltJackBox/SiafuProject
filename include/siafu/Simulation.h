#ifndef SIMULATION_H
#define SIMULATION_H

#include <siafu/Controller.h>
#include <model/SimulationData.h>
#include <mutex>
#include <string>

class World;

class Simulation
{

private:
    const Controller* control;
    bool ended;
    SimulationData* simData;
    bool paused;
    World* world;
    //Calendar time;
    //BaseAgentModel agentModel;
    //BaseWorldModel worldModel;
    //BaseContextModel contextModel;
    int iterationStep;
    //SimulatorOutputPrinter outputPrinter;
    bool simulationRunning;
    //XMLConfiguration siafuConfig;
    std::mutex lock; 

    /*synchronized*/ bool isEnded();
    void moveAgents();
    void tickTime();

public:
    Simulation();
    Simulation(std::string simulationPath, Controller* control);
    bool isSimulationRunning();
    World* getWorld(); 
    /*synchronized*/ bool isPaused();
    void operator()();
    void die();
    SimulationData* getSimulationData();
};

#endif