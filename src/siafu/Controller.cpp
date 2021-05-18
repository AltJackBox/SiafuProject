#include "Controller.h"
#include <iostream>
#include <string>

Controller::Controller(std::string configPath, std::string simulationPath)
{
	std::string verifiedConfigPath = configPath;

	if (configPath.empty())
	{
		verifiedConfigPath = DEFAULT_CONFIG_FILE;
	}

	// try {
	//config = new XMLConfiguration(verifiedConfigPath);
	std::cout << "Using configuration at " + verifiedConfigPath;
	// } catch (ConfigurationException e) {
	// 	System.out.println("The config file doesn't exist or "
	// 			+ "is malformed. Recreating.");
	// 	config = createDefaultConfigFile();
	// }

	if (!simulationPath.empty())
	{
		// Printout to the Console
		//progress = new ConsoleProgress();

		// Start the simulation without a GUI
		simulation = new Simulation(simulationPath, this);
	}
	else
	{
		// No simulation and no GUI to load. This won't
		// work. Die.
		std::cout << "Please activate the GUI in the config file "
				  << "or provide a simulation at the command line.";
		exit(1);
	}
}
// static Progress getProgress() {
// 	return progress;
// }

/**
	 * Request for the simulation to stop. note that this doesn't kill the GUI
	 * (if it is being used).
	 * 
	 */
/*synchronized*/ void Controller::stopSimulation()
{
	simulation->die();
	simulation = NULL;
}

void Controller::startSimulation(std::string simulationPath)
{
	simulation = new Simulation(simulationPath, this);
}

void Controller::setPaused(const bool state)
{
	//simulation->setPaused(state);
}

bool Controller::isPaused()
{
	return simulation->isPaused();
}

World getWorld() {
	return simulation->getWorld();
}

// SimulationData getSimulationData() {
// 	return simulation.getSimulationData();
// }

/*synchronized*/ void Controller::endSimulator()
{

	// if (simulation != null) {
	// 	simulation.die();
	// }
}

bool Controller::isSimulationRunning()
{
	//return simulation != null && simulation.isSimulationRunning();
}
