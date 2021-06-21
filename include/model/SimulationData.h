#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

static const std::string PLACES_PATH = "places";

static const std::string WALLS_FILE = "map/walls.png";

static const std::string BACKGROUND_FILE = "map/background.png";

static const std::string CONFIG_FILE = "config.xml";

class SimulationData
{

protected:
	std::string path;


public:

	static SimulationData *getInstance(const std::string pathString)
	{
		std::ifstream file{pathString + "config.xml"};
		if (!file)
		{
			std::cerr << "The simulation data at " + pathString + " does not exist\n";
			return NULL;
		}
		else
		{
			return new SimulationData(pathString);
		}
	}

	//Class < ? extends BaseAgentModel > getAgentModelClass();

	//Class < ? extends BaseContextModel > getContextModelClass();

	//Class < ? extends BaseWorldModel > getWorldModelClass();

	std::vector<std::string> getPlaceFiles();

	std::string getWallsFile();

protected:
	SimulationData(std::string givenPath);

	virtual std::string getFile(std::string path);

	virtual std::vector<std::string> getFilesByPath(const std::string path);

	virtual std::vector<std::string> getFileNamesByPath(const std::string path);
};

#endif
