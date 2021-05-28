#ifndef PROGRESS_H
#define PROGRESS_H

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

#endif