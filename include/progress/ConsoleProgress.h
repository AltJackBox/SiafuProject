#ifndef CONSOLEPROGRESS_H
#define CONSOLEPROGRESS_H

#include <progress/Progress.h>

class ConsoleProgress : public Progress
{
public:

    ConsoleProgress();

    ~ConsoleProgress();

    void reportWorldCreation(std::string worldName) override;

    void reportCachePrefill(int amountOfElements) override;

    void reportCacheElementLoaded() override;

    void reportCachePrefillEnded() override;

    void reportPlacesFound(std::string type, int amount) override;

    void reportPlaceCreated(std::string type) override;

    void reportCreatingAgents() override;

    void reportSimulationStarted() override;

    void reportSimulationEnded() override;

    void reportBackgroundCreationStart(int amount) override;

    void reportBackgroundCreated() override;

    void reportBackgroundCreationEnd() override;
};

#endif