#include <siafu/Controller.h>
#include <siafu/Simulation.h>
#include <iostream>
#include <string>

Controller::Controller(){
}

Controller::Controller(std::string configPath, std::string simulationPath)
{
	// std::string verifiedConfigPath = configPath;

	// if (configPath.empty())
	// {
	// 	verifiedConfigPath = DEFAULT_CONFIG_FILE;
	// }

	//Start the simulation without a GUI
	if (!simulationPath.empty())
	{
		progress = new Progress();
		simulation = new Simulation(simulationPath, this);
		simulation->launchSimulation();
	}
	else
	{
		std::cout << "You need to provide a simulation at the command line.\n";
		exit(1);
	}
}

Progress* Controller::getProgress() {
	return progress;
}


void Controller::stopSimulation()
{
	mutex.lock();
	simulation->die();
	simulation = NULL;
	mutex.unlock();
}

void Controller::startSimulation(std::string simulationPath)
{
	simulation = new Simulation(simulationPath, this);
}

bool Controller::isPaused()
{
	return simulation->isPaused();
}

World* Controller::getWorld() {
	return simulation->getWorld();
}

SimulationData* Controller::getSimulationData() {
	return simulation->getSimulationData();
}

void Controller::endSimulator()
{
	mutex.lock();
	if (this->simulation != NULL) {
		this->simulation->die();
	}
	std::cout<< "been through endsimulator\n";
	mutex.unlock();
}

bool Controller::isSimulationRunning()
{
	return simulation != NULL && simulation->isSimulationRunning();
}
