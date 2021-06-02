#include <model/SimulationData.h>

class DirectorySimulationData : public SimulationData {
    public:
    DirectorySimulationData(std::string path);
};

SimulationData *SimulationData::getInstance(const std::string pathString)
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

std::unordered_map<std::string, std::ifstream> SimulationData::getFilesByPath(const std::string dirPath)
{
//     std::unordered_map<std::string, std::ifstream> foundFiles;

//     std::string pathString = path + "/" + dirPath;

//     std::string ext(".png");
//     std::string name;
//     std::ifstream file;
//     for (auto &p : std::experimental::filesystem::directory_iterator(pathString))
//     {
//         if (p.path().extension() == ext)
//         {
//             name = p.path().stem().string();
//             file = std::ifstream{p.path().string()};
//             //std::cout << name << '\n';
//             if (!file)
//             {
//                 std::cout << "File is missing : " + p.path().string() + ", no entry inside map\n";
//             }
//             else
//             {
//                 foundFiles.insert(std::make_pair(name, file));
//             }
//         }
//         return foundFiles;
//     }
}

std::vector<std::string> SimulationData::getFileNamesByPath(const std::string dirPath)
{
//     std::vector<std::string> foundFiles;

//     std::string pathString = path + "/" + dirPath;

//     std::string ext(".png");
//     std::string name;
//     for (auto &p : std::experimental::filesystem::directory_iterator(pathString))
//     {
//         if (p.path().extension() == ext)
//         {
//             name = p.path().stem().string();
//             //std::cout << name << '\n';
//             foundFiles.push_back(name);
//         }
//     }
//     return foundFiles;
}

std::ifstream SimulationData::getFile(std::string path)
{

//     std::ifstream file{path};
//     if (!file)
//     {
//         std::cerr << "Your simulation data is missing " + path + ". Perhaps you opened the wrong directory?\n";
//         return;
//     }
//     return file;
}