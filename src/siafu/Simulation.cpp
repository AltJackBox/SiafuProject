#include <siafu/Simulation.h>
#include <siafu/Controller.h>
#include <progress/Progress.h>
#include <model/World.h>
#include <model/SimulationData.h>
#include <model/Agent.h>
#include <model/Position.h>
#include <Calendar.h>

#include <office/AgentModel.h>

#include <behaviormodels/BaseAgentModel.h>
#include <behaviormodels/BaseWorldModel.h>
#include <behaviormodels/BaseContextModel.h>
#include <thread>

Simulation::~Simulation()
{
	//delete control;
	if (simData){
		delete simData;
		simData = nullptr;
	}
	if (world){
		delete world;
		world = nullptr;
	}
	// delete time;
	// delete agentModel;
	// delete worldModel;
}

Simulation::Simulation(std::string simulationPath, Controller *control)
{
	this->simData = SimulationData::getInstance(simulationPath);
	this->control = control;
	ended = false;
	World::setCacheSize(100);
}

void Simulation::launchSimulation()
{
	std::thread t1(&Simulation::operator(), this);
	t1.join();
}

bool Simulation::isEnded()
{
	std::lock_guard<std::mutex> lg(lock);
	return ended;
}

void Simulation::tickTime()
{
	time->add(iterationStep);
}

void Simulation::operator()()
{
	this->world = new World(this, simData);
	this->time = world->getTime();
	this->iterationStep = 100;
	this->agentModel = world->getAgentModel();
	this->worldModel = world->getWorldModel();

	control->getProgress()->reportSimulationStarted();
	simulationRunning = true;
	while (!isEnded())
	{
		tickTime();
		worldModel->doIteration(world->getPlaces());
		agentModel->doIteration(world->getPeople());
		moveAgents();
		if (((AgentModel *)agentModel)->getDay() > 30)
		{
			control->endSimulator();
		}
	}
	simulationRunning = false;
	control->getProgress()->reportSimulationEnded();
}

void Simulation::moveAgents()
{
	for (Agent *a : world->getPeople())
	{
		a->moveTowardsDestination();
	}
}

World *Simulation::getWorld()
{
	return world;
}

bool Simulation::isSimulationRunning()
{
	return simulationRunning;
}

void Simulation::die()
{
	ended = true;
}

SimulationData *Simulation::getSimulationData()
{
	return simData;
}
