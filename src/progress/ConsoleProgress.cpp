#include <progress/ConsoleProgress.h>


void ConsoleProgress::reportWorldCreation(std::string worldName)
{
    std::cout << "Creating the world: " << worldName << "\n";
}

void ConsoleProgress::reportCachePrefill(int amountOfElements) 
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

void ConsoleProgress::reportCacheElementLoaded()
{
    std::cout << ".";
}

void ConsoleProgress::reportCachePrefillEnded()
{
    std::cout << "\n";
}

void ConsoleProgress::reportPlacesFound(std::string type, int amount)
{
    std::cout << "Creating Places: " << type << " (" << amount << ")\n";
}

void ConsoleProgress::reportPlaceCreated(std::string type)
{
    // Do nothing
}

void ConsoleProgress::reportCreatingAgents()
{
    std::cout << "Creating agents\n";
}

void ConsoleProgress::reportSimulationStarted()
{
    std::cout << "Starting the simulation\n";
}

void ConsoleProgress::reportSimulationEnded()
{
    std::cout << "Simulation ended\n";
}

void ConsoleProgress::reportBackgroundCreationStart(int amount)
{
    std::cout << "Preparing backgrounds\n";
}

void ConsoleProgress::reportBackgroundCreated()
{
    std::cout << ".";
}

void ConsoleProgress::reportBackgroundCreationEnd()
{
    std::cout << "\n";
}