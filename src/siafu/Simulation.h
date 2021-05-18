#ifndef SIMULATION_H
#define SIMULATION_H

#include "Controller.h"
#include "model/World.h"
#include <mutex>



class Simulation  /*implements Runnable*/
{

private:
    const Controller control;
    bool ended;
    //SimulationData simData;
    bool paused;
    World world;
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
    //void run();
    bool isSimulationRunning();
    World getWorld(); 
    /*synchronized*/ bool isPaused();
    void die();
    //SimulationData getSimulationData();
};

#endif