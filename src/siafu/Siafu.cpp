#include <iostream>
#include <siafu/Controller.h>

std::string RELEASE = "1.0.4";

std::string SYNTAX =
    "Command line arguments: [--config=CONFIG_FILE] [--simulation=SIMULATION_PATH] [-h]\nwhere CONFIG_FILE is the configuration XML, and SIMULATION_PATH is either\nthe simulation's root folder or it's packed form in a jar file.";

int main(int argc, char *argv[])
{
    std::string simulationPath = "./ressources/Simulation-Office/";
    int duration = 30;
    bool stop = false;
    bool gradient = false;
    std::string arg;
    for (int i = 1; i < argc; i++)
    {
        arg = argv[i];
        if ((arg.compare("-v") == 0) || (arg.compare("--version") == 0))
        {
            std::cout << "Siafu v" << RELEASE << " , Miquel Martin, NEC Europe Ltd.\n";
            exit(0);
        }
        else if ((arg.compare("-d") == 0) || (arg.compare("--days") == 0))
        {
            duration = std::stoi(argv[i + 1]);
        }
        else if ((arg.compare("-s") == 0) || (arg.compare("--stop") == 0))
        {
            stop = true;
        }
        else if ((arg.compare("-g") == 0) || (arg.compare("--grad") == 0))
        {
            gradient = true;
        }
    }

    Controller *controller = new Controller(simulationPath, duration, stop, gradient);
    delete controller;
    return 0;
}