#include <model/SimulationData.h>
#include <experimental/filesystem>
#include <utility>


// AgentModel getAgentModelClass()
// {
//    return new AgentModel();                          SIMULATION_OFFICE
// }

// ContextModel getContextModelClass()
// {
//    return new ContextModel();                        SIMULATION_OFFICE
// }

// Class < ? extends BaseWorldModel > getWorldModelClass()
// {
//    return new WorldModel();                          SIMULATION_OFFICE
// }

std::vector<std::string> SimulationData::getPlaceFiles()
{
    return getFilesByPath(PLACES_PATH);
}

std::string SimulationData::getWallsFile()
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

std::vector<std::string> SimulationData::getFilesByPath(const std::string dirPath)
{
    std::vector<std::string> foundFiles;

    std::string pathString = path + "/" + dirPath;

    std::string ext(".png");
    std::string name;
    std::ifstream file;
    for (auto &p : std::experimental::filesystem::directory_iterator(pathString))
    {
        if (p.path().extension() == ext)
        {
            name = p.path().string(); // UPDATE : p.path().stem().string(); ---> without extension
            file = std::ifstream{p.path().string()};
            //std::cout << name << '\n';
            if (!file)
            {
                std::cout << "File is missing : " + p.path().string() + ", no entry inside map\n";
            }
            else
            {
                foundFiles.push_back(name);
            }
        }
        return foundFiles;
    }
}

std::string SimulationData::getFile(std::string path)
{

    std::ifstream file{path};
    if (!file)
    {
        std::cerr << "Your simulation data is missing " + path + ". Perhaps you opened the wrong directory?\n";
        return;
    }
    return path;
}