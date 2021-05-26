#include <model/SimulationData.h>
#include <model/DirectorySimulationData.h>
#include <utils.h>

SimulationData* SimulationData::getInstance(const std::string pathString)
{
    std::ifstream file{pathString + "config.xml"};
    if (!file)
    {
        std::cerr << "The simulation data at " + pathString + " does not exist\n";
        return;
    }		
    else
    {
        return new DirectorySimulationData(pathString);    
    }
}


// AgentModel getAgentModelClass()
// {
//    return new AgentModel();
// }

// ContextModel getContextModelClass()
// {
//    return new ContextModel();
// }

// Class < ? extends BaseWorldModel > getWorldModelClass()
// {
//    return new WorldModel();
// }

std::unordered_map<std::string, std::ifstream> SimulationData::getPlaceFiles()
{
    return getFilesByPath(PLACES_PATH);
}

// std::unordered_map<std::string, InputStream> SimulationData::getOverlayFiles()
// {
//     return getFilesByPath(OVERLAYS_PATH);
// }

std::ifstream SimulationData::getWallsFile()
{
    return getFile(WALLS_FILE);
}

// XMLConfiguration getConfigFile()
// {
//     if (simulationConfig == null)
//     {
//         simulationConfig = new XMLConfiguration();
//         try
//         {
//             simulationConfig.load(getFile(CONFIG_FILE));
//         }
//         catch (ConfigurationException e)
//         {
//             throw new RuntimeException(
//                 "Error reading the simulation config file", e);
//         }
//     }
//     return simulationConfig;
// }

SimulationData::SimulationData(std::string givenPath)
{
    path = givenPath;
}