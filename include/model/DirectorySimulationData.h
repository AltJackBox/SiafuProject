#ifndef DIRECTORYSIMULATIONDATA_H
#define DIRECTORYSIMULATIONDATA_H

#include <model/SimulationData.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

class DirectorySimulationData : public SimulationData
{
public:
	DirectorySimulationData(std::string dir);

protected:
	std::unordered_map<std::string, std::ifstream> getFilesByPath(const std::string dirPath) override;

	std::vector<std::string> getFileNamesByPath(const std::string dirPath) override;

	std::ifstream getFile(std::string path) override;
};

#endif
