#include <siafu/Controller.h>
#include <iostream>
#include <string>

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
		progress = new ConsoleProgress();
		//simulation = new Simulation(simulationPath, this);
	}
	else
	{
		std::cout << "You need to provide a simulation at the command line.\n";
		exit(1);
	}
	std::cout << "Controller created\n";
}

Progress* Controller::getProgress() {
	return progress;
}

// /*synchronized*/
// void Controller::stopSimulation()
// {
// 	mutex.lock();
// 	simulation->die();
// 	simulation = NULL;
// 	mutex.unlock();
// }

// void Controller::startSimulation(std::string simulationPath)
// {
// 	simulation = new Simulation(simulationPath, this);
// }

// // void Controller::setPaused(const bool state)
// // {
// // 	simulation->setPaused(state);
// // }

// // bool Controller::isPaused()
// // {
// // 	return simulation->isPaused();
// // }

// World Controller::getWorld() {
// 	return simulation->getWorld();
// }

// // SimulationData getSimulationData() {
// // 	return simulation.getSimulationData();
// // }

// /*synchronized*/
// void Controller::endSimulator()
// {
// 	mutex.lock();
// 	if (simulation != NULL) {
// 		simulation->die();
// 	}
// 	mutex.unlock();
// }

// bool Controller::isSimulationRunning()
// {
// 	return simulation != NULL && simulation->isSimulationRunning();
// }
