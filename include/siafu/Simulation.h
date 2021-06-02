#ifndef SIMULATION_H
#define SIMULATION_H

#include <siafu/Controller.h>
//#include <model/World.h>
#include <mutex>
#include <string>

class World;

class Task
{
 public:
     Task() { std::cout << "task constructor\n"; }

     void operator()() const
     {
        std::cout << "operator()\n";
     }
};

class Simulation
{

private:
    const Controller control;
    bool ended;
    //SimulationData simData;
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
    //void operator()();
    bool isSimulationRunning();
    World* getWorld(); 
    /*synchronized*/ bool isPaused();
    void die();
    //SimulationData getSimulationData();
};

#endif