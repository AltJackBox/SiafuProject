#include <siafu/Controller.h>
#include <siafu/Simulation.h>
#include <progress/Progress.h>
#include <model/World.h>
#include <model/SimulationData.h>
#include <iostream>
#include <string>

Progress *Controller::progress;

Controller::Controller()
{
}

Controller::Controller(std::string simulationPath)
{

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

World *Controller::getWorld()
{
	return simulation->getWorld();
}

SimulationData *Controller::getSimulationData()
{
	return simulation->getSimulationData();
}

void Controller::endSimulator()
{
	mutex.lock();
	if (this->simulation != NULL)
	{
		this->simulation->die();
	}
	std::cout << "been through endsimulator\n";
	mutex.unlock();
}

bool Controller::isSimulationRunning()
{
	return simulation != NULL && simulation->isSimulationRunning();
}
