#ifndef PROGRESS_H
#define PROGRESS_H

#include <siafu/Controller.h>
#include <string>
#include <iostream>

class Progress
{

public:
    virtual void reportWorldCreation(std::string worldName);

    virtual void reportCachePrefill(int amountOfElements);

    virtual void reportCacheElementLoaded();

    virtual void reportCachePrefillEnded();

    virtual void reportPlacesFound(std::string type, int amount);

    virtual void reportPlaceCreated(std::string type);

    virtual void reportCreatingAgents();

    virtual void reportSimulationStarted();

    virtual void reportSimulationEnded();

    virtual void reportBackgroundCreationStart(int amount);

    virtual void reportBackgroundCreated();

    virtual void reportBackgroundCreationEnd();
};

class ConsoleProgress : public Progress
{
public:
    virtual void reportWorldCreation(std::string worldName)
    {
        std::cout << "Creating the world: " << worldName << "\n";
    }

    virtual void reportCachePrefill(int amountOfElements)
    {
        if (amountOfElements > 0)
        {
            std::cout << "Prefilling cache (" << amountOfElements << ")\n";
        }
        else
        {
            std::cout << "Important: I'm storing place " << "gradients in\n" << Controller::DEFAULT_GRADIENT_PATH << "\nIt might take some 10MB!\n";
        }
    }
    virtual void reportCacheElementLoaded(){
        std::cout << ".";
    }

    virtual void reportCachePrefillEnded(){
        std::cout << "\n";
    }

    virtual void reportPlacesFound(std::string type, int amount){
        std::cout << "Creating Places: " << type << " (" << amount << ")\n";
    }

    virtual void reportPlaceCreated(std::string type){
        // Do nothing
    }

    virtual void reportCreatingAgents(){
        std::cout << "Creating agents\n";
    }

    virtual void reportSimulationStarted(){
        std::cout << "Starting the simulation\n";
    }

    virtual void reportSimulationEnded(){
        std::cout << "Simulation ended\n";
    }

    virtual void reportBackgroundCreationStart(int amount){
        std::cout << "Preparing backgrounds\n";
    }

    virtual void reportBackgroundCreated(){
        std::cout << ".";
    }

    virtual void reportBackgroundCreationEnd(){
        std::cout << "\n";
    }
};
 
#endif