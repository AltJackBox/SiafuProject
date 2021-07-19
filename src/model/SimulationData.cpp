#include <model/SimulationData.h>
#include <experimental/filesystem>
#include <utility>

std::vector<std::string> SimulationData::getPlaceFiles()
{
    return getFilesByPath(PLACES_PATH);
}

std::string SimulationData::getWallsFile()
{
    return getFile(WALLS_FILE);
}

SimulationData::SimulationData(std::string givenPath)
{
    path = givenPath;
}

std::vector<std::string> SimulationData::getFilesByPath(const std::string dirPath)
{
    std::vector<std::string> foundFiles;

    std::string pathString = path + dirPath;

    std::string ext(".png");
    std::string name;
    std::ifstream file;
    for (auto &p : std::experimental::filesystem::directory_iterator(pathString))
    {
        if (p.path().extension() == ext)
        {
            name = p.path().string(); // UPDATE : p.path().stem().string(); ---> without extension
            file = std::ifstream{p.path().string()};
            if (!file)
            {
                throw std::runtime_error("File is missing : " + p.path().string() + ", no entry inside map");
            }
            else
            {
                foundFiles.push_back(name);
            }
        }
    }
    return foundFiles;
}

std::string SimulationData::getFile(std::string path)
{
    std::string pathString = this->path + path;
    std::ifstream file{pathString};
    if (!file)
    {
        throw std::runtime_error("Your simulation data is missing " + pathString + ". Perhaps you opened the wrong directory ?");
    }
    return pathString;
}