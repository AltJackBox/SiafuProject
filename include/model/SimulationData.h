#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

static const std::string DEFAULT_PATH = "./ressources/Simulation-Office/";

static const std::string PLACES_PATH = "places/";

static const std::string WALLS_FILE = "map/walls.png";

static const std::string CONFIG_FILE = "config.xml";

class SimulationData
{

protected:
	std::string path;

public:
	~SimulationData() {}

	static SimulationData *getInstance(const std::string pathString)
	{
		std::ifstream file{pathString + "config.xml"};
		if (!file)
		{
			std::cerr << "The simulation data at " + pathString + " does not exist\n";
			return nullptr;
		}
		else
		{
			return new SimulationData(pathString);
		}
	}

	std::vector<std::string> getPlaceFiles();

	std::string getWallsFile();

protected:
	SimulationData(std::string givenPath); // need to be modified to public in order to be tested

	virtual std::string getFile(std::string path);

	virtual std::vector<std::string> getFilesByPath(const std::string path);
};

#endif
