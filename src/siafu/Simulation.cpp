#include "Simulation.h"
#include <string>

Simulation::Simulation(std::string simulationPath, Controller* control)
{
	// this->simData = SimulationData.getInstance(simulationPath);
	// this->siafuConfig = control.getSiafuConfig();
	// this->simulationConfig = simData.getConfigFile();
	// this->control = control;

	// World.setShouldPrefillCache(control.getSiafuConfig().getBoolean(
	// 	"ui.gradientcache.prefill"));

	// World.setCacheSize(control.getSiafuConfig().getInt(
	// 	"ui.gradientcache.size"));

	// new Thread(this, "Simulation thread").start();
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

/*synchronized*/ bool Simulation::isEnded()
{
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

// void run() {
// 	this.world = new World(this, simData);
// 	this.time = world.getTime();
// 	this.iterationStep = simulationConfig.getInt("iterationstep");
// 	this.agentModel = world.getAgentModel();
// 	this.worldModel = world.getWorldModel();
// 	this.contextModel = world.getContextModel();
// 	this.outputPrinter =
// 			createOutputPrinter(siafuConfig.getString("output.type"));

// 	Controller.getProgress().reportSimulationStarted();
// 	simulationRunning = true;
// 	while (!isEnded()) {
// 		if (!isPaused()) {
// 			tickTime();
// 			worldModel.doIteration(world.getPlaces());
// 			agentModel.doIteration(world.getPeople());
// 			contextModel.doIteration(world.getOverlays());
// 		}
// 		moveAgents();
// 		control.scheduleDrawing();
// 		outputPrinter.notifyIterationConcluded();
// 	}
// 	simulationRunning = false;

// 	outputPrinter.cleanup();
// 	Controller.getProgress().reportSimulationEnded();
// }

World Simulation::getWorld() {
	return world;
}

bool Simulation::isSimulationRunning()
{
	return simulationRunning;
}

/*synchronized*/ bool Simulation::isPaused()
{
	return paused;
}

void Simulation::die()
{
	ended = true;
}

// SimulationData getSimulationData() {
// 	return simData;
// }
