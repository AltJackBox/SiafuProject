#include <iostream>
#include <siafu/Controller.h>

std::string RELEASE = "1.0.4";

std::string SYNTAX =
    "Command line arguments: [--config=CONFIG_FILE] [--simulation=SIMULATION_PATH] [-h]\nwhere CONFIG_FILE is the configuration XML, and SIMULATION_PATH is either\nthe simulation's root folder or it's packed form in a jar file.";

int main(int argc, char *argv[])
{
    std::string simulationPath = "./ressources/Simulation-Office/";

    std::string arg;
    for (int i = 1; i < argc; i++)
    {
        arg = argv[i];
        if ((arg.compare("-v") == 0) || (arg.compare("--version") == 0))
        {
            std::cout << "Siafu v" << RELEASE << " , Miquel Martin, NEC Europe Ltd.\n";
            exit(0);
        }
        else 
        {
            std::cout << "Unrecognized parameter '" << arg << "'\n";
        }
    }

    Controller* controller = new Controller(simulationPath);
    delete controller;
    return 0;
}