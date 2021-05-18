#include <string>
#include <iostream>
#include <siafu/Controller.h>

class Siafu
{

private:
    Siafu()
    {
    }

public:
    /**
	 * Siafu's version.
	 */
    std::string RELEASE = "1.0.4";

    /**
	 * The string with the command line syntax.
	 */
    std::string SYNTAX =
        "Command line arguments: [--config=CONFIG_FILE] [--simulation=SIMULATION_PATH] [-h]\nwhere CONFIG_FILE is the configuration XML, and SIMULATION_PATH is either\nthe simulation's root folder or it's packed form in a jar file.";

    /**
	 * Start Siafu by parsing the command line arguments and starting the
	 * controller.
	 * 
	 * @param args the command line args
	 */
public:
    void main(int argc, char *argv[])
    {
        std::string configPath = NULL;
        std::string simulationPath = NULL;

        std::string arg;
        for (int i = 0; i < argc; i++)
        {
            arg = argv[i];
            if ((arg.compare("-v") == 0) || (arg.compare("--version") == 0))
            {
                std::cout << "Siafu v" << RELEASE << " , Miquel Martin, NEC Europe Ltd.";
                exit(0);
            }
            else
            {
                std::cout << "Unrecognized parameter '" << arg << "'";
            }
        }

        new Controller(configPath, simulationPath);
    }
};