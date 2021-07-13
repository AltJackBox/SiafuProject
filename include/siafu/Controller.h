#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unistd.h>
#include <mutex>
#include <string>

static const std::string separator = "/";

static const std::string ABSOLUTE_PATH = "/home" + separator + getlogin(); // Unix version

static const std::string CONFIG_PATH = ABSOLUTE_PATH + "/.Siafu"; // Unix version

static const std::string DEFAULT_GRADIENT_PATH = "./ressources/CalculatedGradients/";

static const std::string DEFAULT_CONFIG_FILE = CONFIG_PATH + separator + "config.xml";

static const int DEFAULT_CACHE_SIZE = 100;

static const int DEFAULT_UI_SPEED = 50;

class Simulation;
class Progress;
class World;
class SimulationData;

class Controller
{

private:
    Simulation *simulation;
    static Progress *progress;
    std::mutex mutex;

public:
    Controller();

    Controller(std::string simulationPath);

    static Progress *getProgress()
    {
        return progress;
    }

    void stopSimulation();

    void startSimulation(std::string simulationPath);

    World *getWorld();

    SimulationData *getSimulationData();

    void endSimulator();

    bool isSimulationRunning();
};
#endif
