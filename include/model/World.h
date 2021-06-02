#ifndef WORLD_H
#define WORLD_H

#include <siafu/Controller.h>
#include <unistd.h>
#include <vector>
#include <set>

class Simulation;

class World
{

private:
    static const int COLOR_WHITE = 0xFFFFFF;

    static const int NEAR_DISTANCE = 15;

    // static bool prefillCache;

    int height;

    int width;

    std::string worldName;

    //SortedMap<String, Overlay> overlays;

    //std::vector <Place> places;

    std::set<std::string> placeTypes /*= new HashSet<String>()*/;

    //Calendar time; look for time.h

    //BaseAgentModel agentModel;

    //BaseWorldModel worldModel;

    //BaseContextModel contextModel;

    //std::unordered_map <std::string, Agent> people;

    bool walls[0][0];

    Simulation *simulation;

    //SimulationData simData;

    //std::vector <Position> readPlacePoints(InputStream is);

    void buildWalls();

    void initializeCoordinates();

    void createPeople();

    void createTime();

    //void freezeInfoFields();

    void createPlaces();

    void createOverlays();

    // ArrayList<Overlay> createOverlaysFromImages()
    // {
    //     ArrayList<Overlay> overlaysFromImages = new ArrayList<Overlay>();
    //     Map<String, InputStream> fileList = simData.getOverlayFiles();
    //     Iterator<String> listIt = fileList.keySet().iterator();

    //     while (listIt.hasNext())
    //     {
    //         String name = listIt.next();
    //         InputStream overlayIS = fileList.get(name);
    //         overlaysFromImages.add(Overlay.getOverlay(name, overlayIS,
    //                                                   simulationConfig));
    //     }

    //     return overlaysFromImages;
    // }

protected:
    //std::vector<Place> createPlacesFromImages();

public:
    // USEFUL ?
    //void setShouldPrefillCache(bool prefill);

    // USEFUL ?
    //bool shouldPrefillCache();

    World();

    World(Simulation* simulation /*, SimulationData simData*/);

    std::string getWorldName();

    int getHeight();

    int getWidth();

    bool isAWall(/*Position pos*/);

    //std::set<std::string> getAvailableSprites();

    //std::vector<Agent> getPeople();

    //std::vector<Place> getPlaces();

    //Calendar getTime();

    //Trackable findAnythingNear(Position pos, bool visibleOnly);

    // Trackable findAgentNear(final Position pos, final boolean visibleOnly);

    //Trackable findPlaceNear(final Position pos, final boolean visibleOnly);

    //Trackable findNearOutOf(Position pos, final Collection<? extends Trackable> candidates, final int distance, final boolean visibleOnly);

    //std::vector<Trackable> findAllAgentsNear(Position pos, int distance, bool visibleOnly);

    //std::vector<Trackable> findAllPlacesNear(Position pos, int distance, bool visibleOnly);

    //std::vector<Trackable> findAllNearOutOf(Position pos, final Collection<? extends Trackable> candidates, final int distance, final boolean visibleOnly);

    //Place getPlaceByName(std::string name);

    //Place getPlaceByPosition(const Position pos);

    //Collection<Place> getPlacesOfType(const std::tring type);

    //Place getNearestPlaceOfType(const std::string type, const Position pos);

    //SortedMap<String, Overlay> getOverlays();

    std::set<std::string> getPlaceTypes();

    void addPlaceType(const std::string placeType);

    //BaseAgentModel getAgentModel();

    //BaseContextModel getContextModel();

    //BaseWorldModel getWorldModel();
};

#endif