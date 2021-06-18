#ifndef WORLD_H
#define WORLD_H

#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>

class Simulation;
class SimulationData;
class Position;
class BaseAgentModel;
class BaseContextModel;
class BaseWorldModel;
class Place;
class Agent;

class World
{

private:

    static const int COLOR_WHITE = 0xFFFFFF;

    static const int NEAR_DISTANCE = 15;

    // Values available in Simulation's config.xml file in original Java project

    static const double TOPRIGHT_LATITUDE = 49.003535;

    static const double TOPRIGHT_LONGITUDE = 8.006958;

    static const double BOTTOMRIGHT_LATITUDE = 49.003535;

    static const double BOTTOMRIGHT_LONGITUDE = 8.006958;

    static const double BOTTOMLEFT_LATITUDE = 49.003410;

    static const double BOTTOMLEFT_LONGITUDE = 8.006800;



    // static bool prefillCache;

    int height;

    int width;

    std::string worldName;

    std::vector<Place *> places;

    std::set<std::string> placeTypes;

    //Calendar time; look for time.h

    BaseAgentModel *agentModel;

    BaseWorldModel *worldModel;

    BaseContextModel *contextModel;

    std::unordered_map<std::string, Agent *> people;

    bool *walls;

    Simulation *simulation;

    SimulationData *simData;

    std::vector<Position *> World::readPlacePoints(std::string filename);

    void buildWalls();

    void initializeCoordinates();

    void createPeople();

    void createTime();

    void freezeInfoFields();

    void createPlaces();

    void createOverlays();

protected:
    std::vector<Place *> createPlacesFromImages();

public:
    // USEFUL ?
    //void setShouldPrefillCache(bool prefill);

    // USEFUL ?
    //bool shouldPrefillCache();

    World();

    World(Simulation *simulation, SimulationData *simData);

    std::string getWorldName();

    int getHeight();

    int getWidth();

    bool isAWall(Position *pos);

    std::vector<Agent *> getPeople();

    std::vector<Place *> getPlaces();

    //Calendar getTime();

    //Trackable findAnythingNear(Position pos, bool visibleOnly);

    // Trackable findAgentNear(final Position pos, final boolean visibleOnly);

    //Trackable findPlaceNear(final Position pos, final boolean visibleOnly);

    //Trackable findNearOutOf(Position pos, final Collection<? extends Trackable> candidates, final int distance, final boolean visibleOnly);

    //std::vector<Trackable> findAllAgentsNear(Position pos, int distance, bool visibleOnly);

    //std::vector<Trackable> findAllPlacesNear(Position pos, int distance, bool visibleOnly);

    //std::vector<Trackable> findAllNearOutOf(Position pos, final Collection<? extends Trackable> candidates, final int distance, final boolean visibleOnly);

    Place *getPlaceByName(std::string name);

    Place *getPlaceByPosition(Position *pos);

    std::vector<Place *> World::getPlacesOfType(std::string type);

    Place* getNearestPlaceOfType(const std::string type, Position *pos);

    std::set<std::string> getPlaceTypes();

    void addPlaceType(const std::string placeType);

    BaseAgentModel *getAgentModel();

    BaseContextModel *getContextModel();

    BaseWorldModel *getWorldModel();
};

#endif