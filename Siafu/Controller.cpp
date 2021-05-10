#include <unistd.h>
#include <iostream>
#include <string>
#include "Controller.h"
#include "Simulation.h"
// import java.io.File;
// import java.io.IOException;

// import org.apache.commons.configuration.ConfigurationException;
// import org.apache.commons.configuration.XMLConfiguration;
// import org.eclipse.swt.widgets.Display;

// import de.nec.nle.siafu.control.progress.ConsoleProgress;
// import de.nec.nle.siafu.control.progress.GUIProgress;
// import de.nec.nle.siafu.control.progress.Progress;
// import de.nec.nle.siafu.exceptions.GUINotReadyException;
// import de.nec.nle.siafu.externalCommand.CommandListener;
// import de.nec.nle.siafu.graphics.GUI;
// import de.nec.nle.siafu.graphics.Markers;
// import de.nec.nle.siafu.graphics.markers.Marker;
// import de.nec.nle.siafu.model.SimulationData;
// import de.nec.nle.siafu.model.Trackable;
// import de.nec.nle.siafu.model.World;

static const std::string separator = "/";

/**
 * Configuration folder
 * 
 *   Windows: C:\Documents and Settings\<user>\Application Data\Siafu (XP)
 *            C:\Users\<user>\AppData\Roaming\Siafu (Vista, 7)
 *   Unix:    /home/<user>/.Siafu
 */
static const std::string CONFIG_PATH = "/home/"  + separator + getlogin() + "/.Siafu"; // Unix version

/** Default value for the gradient path. */
static const std::string DEFAULT_GRADIENT_PATH = CONFIG_PATH + separator + "CalculatedGradients" + separator;

/** Default config file location. */
static const std::string DEFAULT_CONFIG_FILE = CONFIG_PATH	+ separator + "config.xml";

class Controller {
    private:
	/** Default value for CSV interval. */
	static const int DEFAULT_CSV_INTERVAL = 300;

	/** Default value for the cache size. */
	static const int DEFAULT_CACHE_SIZE = 100;

	/** Default value for the UI speed. */
	static const int DEFAULT_UI_SPEED = 50;


	/**
	 * The configuration file for the simulator.
	 */
	//XMLConfiguration config;

	// FIXME refactor ro siafuConfig

	/**
	 * The simulation <code>Runnable</code>.
	 */
	Simulation simulation;

	/**
	 * The Progress object that displays simulation load status.
	 */
	//static Progress progress;

	/**
	 * Get the Progress class that displays simulation laod status.
	 * 
	 * @return the progress instance to use
	 */
	public:
    // static Progress getProgress() {
	// 	return progress;
	// }

	/**
	 * Initialize the simulator itself, and run the simulation.
	 * 
	 * @param configPath the file that defines the parameters of the
	 *            simulation
	 * @param simulationPath the path to the simulation data
	 */
	Controller(std::string configPath, std::string simulationPath) {
		std::string verifiedConfigPath = configPath;

		if (configPath.empty()) {
			//verifiedConfigPath = Controller.DEFAULT_CONFIG_FILE;
		}

		// try {
			//config = new XMLConfiguration(verifiedConfigPath);
			std::cout << "Using configuration at " + verifiedConfigPath;
		// } catch (ConfigurationException e) {
		// 	System.out.println("The config file doesn't exist or "
		// 			+ "is malformed. Recreating.");
		// 	config = createDefaultConfigFile();
		// }

        if (!simulationPath.empty()) {
			// Printout to the Console
			//progress = new ConsoleProgress();

			// Start the simulation without a GUI
			//simulation = new Simulation(simulationPath, this);
		} else {
			// No simulation and no GUI to load. This won't
			// work. Die.
			std::cout << "Please activate the GUI in the config file " << "or provide a simulation at the command line.";
			exit(1);
		}

	}

	/**
	 * Create a config file with default values. This is used when the config
	 * file doesn't exist in the first place.
	 * 
	 * @return the newly created configuration file.
	 */
	// private XMLConfiguration createDefaultConfigFile() {
	// 	std::cout << "Creating a default configuration file at " << DEFAULT_CONFIG_FILE;
	// 	XMLConfiguration newConfig = new XMLConfiguration();
	// 	newConfig.setRootElementName("configuration");
	// 	newConfig.setProperty("commandlistener.enable", true);
	// 	newConfig.setProperty("commandlistener.tcpport", DEFAULT_PORT);
	// 	newConfig.setProperty("ui.usegui", true);
	// 	newConfig.setProperty("ui.speed", DEFAULT_UI_SPEED);
	// 	newConfig.setProperty("ui.gradientcache.prefill", true);
	// 	newConfig.setProperty("ui.gradientcache.size", DEFAULT_CACHE_SIZE);
	// 	newConfig.setProperty("output.type", "null");
	// 	newConfig.setProperty("output.csv.path", System
	// 			.getProperty("user.home")
	// 			+ File.separator + "SiafuContext.csv");
	// 	newConfig.setProperty("output.csv.interval", DEFAULT_CSV_INTERVAL);
	// 	newConfig.setProperty("output.csv.keephistory", true);

	// 	try {
	// 		newConfig.setFileName(DEFAULT_CONFIG_FILE);
	// 		newConfig.save();
	// 	} catch (ConfigurationException e) {
	// 		throw new RuntimeException(
	// 				"Can not create a default config file at "
	// 						+ DEFAULT_CONFIG_FILE, e);
	// 	}

	// 	return newConfig;
	// }

	
	/**
	 * Request for the simulation to stop. note that this doesn't kill the GUI
	 * (if it is being used).
	 * 
	 */
	/*synchronized*/ void stopSimulation() {
		//simulation.die();
		//simulation = NULL;
	}

	/**
	 * Start the simulation pointed to by the simulationpath.
	 * 
	 * @param simulationPath the path to the folder or jar containing the
	 *            simulation.
	 */
	void startSimulation(std::string simulationPath) {
		//simulation = new Simulation(simulationPath, this);
	}

	/**
	 * Get the configuration for the simulator.
	 * 
	 * @return the <code>Configuration</code> object
	 */
	// XMLConfiguration getSiafuConfig() {
	// 	return config;
	// }

	/**
	 * Pauses the simulation. See <code>isPaused()</code> for details. If no
	 * gui is used, the simulation thread still pauses.
	 * 
	 * @param state a boolean with the value true will pause the simulation,
	 *            while false will resume it.
	 */
	void setPaused(const bool state) {
		//simulation.setPaused(state);
	}

	
	/**
	 * Reports on the pause state of the simulation.
	 * <p>
	 * When paused, time stops, and all automatic behaviour is interrupted.
	 * However, using the GUI, the user can still manipulate agents in his
	 * control, or update variables through the external command interface.
	 * 
	 * @return true if the simulation is paused, false otherwise
	 */
	bool isPaused() {
		//return simulation.isPaused();
	}

	/**
	 * Get the world being simulated.
	 * 
	 * @return a World object representing the world.
	 */
	// World getWorld() {
	// 	return simulation.getWorld();
	// }

	/**
	 * Get the folder or jar file that contains all the simulation data.
	 * 
	 * @return a File that represents the folder with the images
	 */
	// SimulationData getSimulationData() {
	// 	return simulation.getSimulationData();
	// }

	/**
	 * End the simulator, that is quit. Stop the simulation, but also the GUI
	 * and anything else that's running.
	 */
	/*synchronized*/ void endSimulator() {

		// End the simulation
		// if (simulation != null) {
		// 	simulation.die();
		// }
	}

	/**
	 * Find out if the simulation is finished loading and already running.
	 * 
	 * @return true if the simulation is running.
	 */
	bool isSimulationRunning() {
		//return simulation != null && simulation.isSimulationRunning();
	}
};
