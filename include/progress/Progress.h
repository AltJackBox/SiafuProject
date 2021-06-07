#ifndef PROGRESS_H
#define PROGRESS_H

#include <string>
#include <iostream>


class Progress
{
public:

    Progress();

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