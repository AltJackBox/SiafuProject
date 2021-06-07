#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>


//static const std::string OVERLAYS_PATH = "overlays";

static const std::string PLACES_PATH = "places";

static const std::string WALLS_FILE = "map/walls.png";

static const std::string BACKGROUND_FILE = "map/background.png";

static const std::string CONFIG_FILE = "config.xml";

class SimulationData
{

protected:
	std::string path;
	//URLClassLoader classLoader;

	//private:
	//XMLConfiguration simulationConfig;

public:
	static SimulationData* getInstance(const std::string pathString);

	//Class < ? extends BaseAgentModel > getAgentModelClass();

	//Class < ? extends BaseContextModel > getContextModelClass();

	//Class < ? extends BaseWorldModel > getWorldModelClass();

	std::unordered_map<std::string, std::ifstream> getPlaceFiles();

	//std::unordered_map<String, InputStream> getOverlayFiles();

	std::ifstream getWallsFile();

	//XMLConfiguration getConfigFile();

protected:
	SimulationData(std::string givenPath);

	virtual std::ifstream getFile(std::string path);

	virtual std::unordered_map<std::string, std::ifstream> getFilesByPath(const std::string path);

	virtual std::vector<std::string> getFileNamesByPath(const std::string path);
};

#endif
