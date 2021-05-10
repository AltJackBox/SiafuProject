#include <string>
#include <iostream>

class Siafu
{
public:
    /**
	 * Siafu's version.
	 */
    char *RELEASE = "1.0.4";

    /**
	 * The string with the command line syntax.
	 */
    char *SYNTAX =
        "Command line arguments: [--config=CONFIG_FILE] " + "[--simulation=SIMULATION_PATH] [-h]\n" + "where CONFIG_FILE is the configuration XML, " + "and SIMULATION_PATH is either\n" + "the simulation's root folder or it's " + "packed form in a jar file.";

    /**
	 * Prevent this utility class from being instantiated.
	 */
private:
    Siafu()
    {
    }

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

        //new Controller(configPath, simulationPath);
    }
};