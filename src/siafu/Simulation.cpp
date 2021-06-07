#include <siafu/Simulation.h>
#include <model/World.h>
#include <thread>

Simulation::Simulation(std::string simulationPath, Controller *control)
{
	this->simData = simData->getInstance(simulationPath);
	// this->simulationConfig = simData.getConfigFile();
	this->control = control;
	ended = false;
	// World.setShouldPrefillCache(control.getSiafuConfig().getBoolean(
	// 	"ui.gradientcache.prefill"));

	// World.setCacheSize(control.getSiafuConfig().getInt(
	// 	"ui.gradientcache.size"));

}

void Simulation::launchSimulation(){
	std::thread t1(&Simulation::operator(), this);
	t1.join();
}

// SimulatorOutputPrinter createOutputPrinter(final String type) {
// 	if (type.equalsIgnoreCase("csv")) {
// 		System.out.println("CSV output selected");
// 		return new CSVPrinter(world, siafuConfig);
// 	} else if (type.equalsIgnoreCase("null")) {
// 		return new NullPrinter();
// 	} else {
// 		throw new RuntimeException(
// 				"Unknown ouput type in the configuration");
// 	}
// }

bool Simulation::isEnded()
{
	std::lock_guard<std::mutex> lg(lock);
	return ended;
}

void Simulation::moveAgents()
{
	// for (Agent a : world.getPeople()) {
	// 	if (!isPaused() || !a.isOnAuto()) {
	// 		a.moveTowardsDestination();
	// 	}
	// }
}

void Simulation::tickTime()
{
	//time.add(Calendar.SECOND, iterationStep);
}

void Simulation::operator()()
{
	this->world = new World(this, simData);
	// this->time = world.getTime();
	// this->iterationStep = simulationConfig.getInt("iterationstep");
	// this->agentModel = world.getAgentModel();
	// this->worldModel = world.getWorldModel();
	// this->contextModel = world.getContextModel();
	// this->outputPrinter = createOutputPrinter(siafuConfig.getString("output.type"));

	control->getProgress()->reportSimulationStarted();
	simulationRunning = true;
	while (!isEnded())
	{
		control->endSimulator();
		// 	if (!isPaused())
		// 	{
		// 		tickTime();
		// 		worldModel.doIteration(world.getPlaces());
		// 		agentModel.doIteration(world.getPeople());
		// 		contextModel.doIteration(world.getOverlays());
		// 	}
		// 	moveAgents();
		// 	control.scheduleDrawing();
		// 	outputPrinter.notifyIterationConcluded();
	}
	// simulationRunning = false;

	// outputPrinter.cleanup();
	control->getProgress()->reportSimulationEnded();
}

World* Simulation::getWorld()
{
	return world;
}

bool Simulation::isSimulationRunning()
{
	return simulationRunning;
}

bool Simulation::isPaused()
{
	std::lock_guard<std::mutex> lg(lock);
	return paused;
}

void Simulation::die()
{
	ended = true;
}

SimulationData *Simulation::getSimulationData()
{
	return simData;
}
