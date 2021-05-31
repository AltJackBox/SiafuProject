#ifndef CONSOLEPROGRESS_H
#define CONSOLEPROGRESS_H

#include <string>
#include <iostream>


class ConsoleProgress
{
public:

    ConsoleProgress();

    ~ConsoleProgress();

    void reportWorldCreation(std::string worldName);

    void reportCachePrefill(int amountOfElements) ;

    void reportCacheElementLoaded() ;

    void reportCachePrefillEnded() ;

    void reportPlacesFound(std::string type, int amount) ;

    void reportPlaceCreated(std::string type) ;

    void reportCreatingAgents() ;

    void reportSimulationStarted() ;

    void reportSimulationEnded() ;

    void reportBackgroundCreationStart(int amount) ;

    void reportBackgroundCreated() ;

    void reportBackgroundCreationEnd() ;
};

#endif