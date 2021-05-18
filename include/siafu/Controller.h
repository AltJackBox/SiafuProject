#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <siafu/Simulation.h>
#include <progress/Progress.h>
#include <unistd.h>
#include <mutex>

class Controller
{

private:
    /** Default value for CSV interval. */
    static const int DEFAULT_CSV_INTERVAL = 300;
    /** Default value for the cache size. */
    static const int DEFAULT_CACHE_SIZE = 100;
    /** Default value for the UI speed. */
    static const int DEFAULT_UI_SPEED = 50;
    
    Simulation *simulation;
    Progress* progress;
    std::mutex mutex;

public:
    static const std::string separator = "/";
    /**
 * Configuration folder
 * 
 *   Windows: C:\Documents and Settings\<user>\Application Data\Siafu (XP)
 *            C:\Users\<user>\AppData\Roaming\Siafu (Vista, 7)
 *   Unix:    /home/<user>/.Siafu
 */
    static const std::string CONFIG_PATH = "/home/" + separator + getlogin() + "/.Siafu"; // Unix version
    /** Default value for the gradient path. */
    static const std::string DEFAULT_GRADIENT_PATH = CONFIG_PATH + separator + "CalculatedGradients" + separator;
    /** Default config file location. */
    static const std::string DEFAULT_CONFIG_FILE = CONFIG_PATH + separator + "config.xml";

    Controller();
    Controller(std::string configPath, std::string simulationPath);
    Progress* getProgress();
    void stopSimulation();
    void startSimulation(std::string simulationPath);
    // void setPaused(const bool state);
    // bool isPaused();
    World getWorld();
    // SimulationData getSimulationData();
    void endSimulator();
    bool isSimulationRunning();
};
#endif
