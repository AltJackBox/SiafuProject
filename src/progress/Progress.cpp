#include <progress/Progress.h>
#include <siafu/Controller.h>

Progress::Progress(){
}

void Progress::reportWorldCreation(std::string worldName)
{
    std::cout << "Creating the world: " << worldName << "\n";
}

void Progress::reportCachePrefill(int amountOfElements) 
{
    if (amountOfElements > 0)
    {
        std::cout << "Prefilling cache (" << amountOfElements << ")\n";
    }
    else
    {
        std::cout << "Important: I'm storing place "
                  << "gradients in\n"
                  << DEFAULT_GRADIENT_PATH << "\nIt might take some 10MB!\n";
    }
}

void Progress::reportCacheElementLoaded()
{
    std::cout << ".";
}

void Progress::reportCachePrefillEnded()
{
    std::cout << "\n";
}

void Progress::reportPlacesFound(std::string type, int amount)
{
    std::cout << "Creating Places: " << type << " (" << amount << ")\n";
}

void Progress::reportPlaceCreated(std::string type)
{
    // Do nothing
}

void Progress::reportCreatingAgents()
{
    std::cout << "Creating agents\n";
}

void Progress::reportSimulationStarted()
{
    std::cout << "Starting the simulation\n";
}

void Progress::reportSimulationEnded()
{
    std::cout << "Simulation ended\n";
}

void Progress::reportBackgroundCreationStart(int amount)
{
    std::cout << "Preparing backgrounds\n";
}

void Progress::reportBackgroundCreated()
{
    std::cout << ".";
}

void Progress::reportBackgroundCreationEnd()
{
    std::cout << "\n";
}