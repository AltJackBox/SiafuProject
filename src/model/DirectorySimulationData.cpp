#include <model/DirectorySimulationData.h>
#include <experimental/filesystem>
#include <utility>

DirectorySimulationData::DirectorySimulationData(std::string dir) : SimulationData(path)
{
    std::cout<< "DirectorySimulationData constructor accessed\n";
}

std::unordered_map<std::string, std::ifstream> DirectorySimulationData::getFilesByPath(const std::string dirPath)
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

std::vector<std::string> DirectorySimulationData::getFileNamesByPath(const std::string dirPath)
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

std::ifstream DirectorySimulationData::getFile(std::string path)
{

//     std::ifstream file{path};
//     if (!file)
//     {
//         std::cerr << "Your simulation data is missing " + path + ". Perhaps you opened the wrong directory?\n";
//         return;
//     }
//     return file;
}