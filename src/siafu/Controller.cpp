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

Controller::~Controller()
{
	if (simulation) {
		delete simulation;
		simulation = nullptr;
	}
	if (progress){
		delete progress;
		progress = nullptr;
	}
}

Controller::Controller(std::string simulationPath, int days)
{
	if (days == -1) {
		duration = 30;
	} else {
		duration = days;
	}

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

int Controller::getDuration(){
	return duration;
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
	if (this->simulation != nullptr)
	{
		this->simulation->die();
	}
	mutex.unlock();
}

bool Controller::isSimulationRunning()
{
	return simulation != nullptr && simulation->isSimulationRunning();
}
