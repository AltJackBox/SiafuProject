#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H
#include <string>


static const std::string OVERLAYS_PATH = "overlays";

static const std::string PLACES_PATH = "places";

static const std::string WALLS_FILE = "map/walls.png";

static const std::string BACKGROUND_FILE = "map/background.png";

static const std::string CONFIG_FILE = "config.xml";

class SimulationData
{

protected:
	//URLClassLoader classLoader;

	//private:
	//XMLConfiguration simulationConfig;

public:
	static SimulationData getInstance(const std::string pathString);

	//Class < ? extends BaseAgentModel > getAgentModelClass();

	//Class < ? extends BaseContextModel > getContextModelClass();

	//Class < ? extends BaseWorldModel > getWorldModelClass();

	//HashMap<std::string, InputStream> getPlaceFiles();

	//HashMap<String, InputStream> getOverlayFiles();

	//InputStream getWallsFile();

	//XMLConfiguration getConfigFile();

protected:
	//SimulationData(final File givenPath);

	//virtual InputStream getFile(const std::string path);

	//virtual HashMap<std::string, InputStream> getFilesByPath(const std::string path);

	//virtual ArrayList<std::string> getFileNamesByPath(const std::string path);
};

#endif
