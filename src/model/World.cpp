#include <model/World.h>
#include <model/Position.h>
#include <siafu/Simulation.h>
#include <model/SimulationData.h>
#include <model/Place.h>
#include <behaviormodels/BaseAgentModel.h>
#include <behaviormodels/BaseContextModel.h>
#include <behaviormodels/BaseWorldModel.h>
#include <iostream>

extern "C"
{
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
}

bool load_image(std::vector<unsigned char> &image, const std::string &filename, int &x, int &y)
{
    int n;
    unsigned char *data = stbi_load(filename.c_str(), &x, &y, &n, 1);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y /** 0*/);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

std::vector<Position *> World::readPlacePoints(std::string filename)
{
    std::vector<Position *> placePoints;

    int width, height;
    std::vector<unsigned char> image;
    bool success = load_image(image, filename, width, height);
    if (!success)
    {
        std::cout << "Error loading image\n";
        return;
    }
    size_t index;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            index = (x * width + y);
            if (image[index] == 0)
            {
                Position *attractor;
                try
                {
                    attractor = new Position(x, y);
                    placePoints.push_back(attractor);
                }
                catch (std::exception const &e)
                {
                    std::cerr << "Place (" << x << "  " << y << ") is unreachable. Is it out of the map or on a wall?\n";
                }
            }
        }
    }

    return placePoints;
}

void World::buildWalls()
{
    int width, height;
    std::vector<unsigned char> image;
    std::string filename = simData->getWallsFile();
    bool success = load_image(image, filename, width, height);
    if (!success)
    {
        std::cout << "Error loading image\n";
        return;
    }

    walls = new bool[height * width];

    size_t index;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            index = (x * width + y);
            walls[index] = (image[index] == COLOR_WHITE);
        }
    }
}

void World::initializeCoordinates()
{
    // double[] topRight = new double[]{
    //     simulationConfig.getDouble("calibration.topright[@latitude]"),
    //     simulationConfig.getDouble("calibration.topright[@longitude]")};

    // double[] bottomLeft = new double[]{
    //     simulationConfig.getDouble("calibration." + "bottomleft[@latitude]"),
    //     simulationConfig.getDouble("calibration." + "bottomleft[@longitude]")};
    // double[] bottomRight = new double[]{
    //     simulationConfig.getDouble("calibration." + "bottomright[@latitude]"),
    //     simulationConfig.getDouble("calibration." + "bottomright[@longitude]")};

    // Position.initialize(this, topRight, bottomRight, bottomLeft);
}

void World::createPeople()
{
    // people = new HashMap<std::string, Agent>();

    // try
    // {
    //     agentModel = (BaseAgentModel)simData.getAgentModelClass()
    //                      .getConstructor(new Class[]{this.getClass()})
    //                      .newInstance(new Object[]{this});
    // }
    // catch (Exception e)
    // {
    //     throw new RuntimeException("Can't instantiate the agent model", e);
    // }

    // Agent.initialize(this);
    // Controller.getProgress().reportCreatingAgents();
    // ArrayList<Agent> peopleList = agentModel.createAgents();
    // Iterator<Agent> peopleIt = peopleList.iterator();

    // while (peopleIt.hasNext())
    // {
    //     Agent p = peopleIt.next();
    //     people.put(p.getName(), p);
    // }
}

void World::createTime()
{
    // time = Calendar.getInstance();

    // time.set(Calendar.getInstance().get(Calendar.YEAR),
    //          Calendar.getInstance().get(Calendar.MONTH),
    //          Calendar.getInstance().get(Calendar.DAY_OF_MONTH),
    //          6,
    //          0);
}

// void freezeInfoFields()
// {
//     Iterator<Agent> peopleIt = people.values().iterator();

//     while (peopleIt.hasNext())
//     {
//         Agent p = peopleIt.next();

//         if (!p.checkAllInfoFieldsPresent())
//         {
//             throw new RuntimeException(
//                 "Agent " + p.getName() + " is missing at least one field that other agents have.");
//         }
//     }

//     Agent.lockInfoFields();
// }

void World::createPlaces()
{
    // try
    // {
    //     worldModel = (BaseWorldModel)simData.getWorldModelClass()
    //                      .getConstructor(new Class[]{this.getClass()})
    //                      .newInstance(new Object[]{this});
    // }
    // catch (Exception e)
    // {
    //     throw new RuntimeException("Can't instantiate the world model", e);
    // }
    // places = createPlacesFromImages();
    // worldModel.createPlaces(places);
}

std::vector<Place*> World::createPlacesFromImages()
{
    Place place;
    place.initialize(this);
    std::vector<Place *> placesFromImg;
    std::vector<std::string> fileList = simData->getPlaceFiles();
    int index = 0;
    while (index != fileList.size())
    {
        std::string filename = fileList[index];
        std::vector<Position*> placePoints = readPlacePoints(filename);
        Iterator<Position> it = placePoints.iterator();
        //total += placePoints.size();
        Controller.getProgress().reportPlacesFound(type, placePoints.size());

        while (it.hasNext())
        {
            Position pos = (Position)it.next();
            Place place;
            try
            {
                place = new Place(type, pos, this);
            }
            catch (PositionOnAWallException e)
            {
                throw new RuntimeException("One of your \"" + type + "\" places, at " + pos + " is on a wall");
            }
            Controller.getProgress().reportPlaceCreated(type);
            placesFromImg.add(place);
        }
    }

    // return placesFromImg;
    //}

    // void World::setShouldPrefillCache(bool prefill)
    // {
    //     this->prefillCache = prefill;
    // }

    // bool World::shouldPrefillCache()
    // {
    //     return this->prefillCache;
    // }

    World::World(Simulation * simulation, SimulationData * simData)
    {
        this->simulation = simulation;
        this->simData = simData;
        //this->simulationConfig = simData.getConfigFile();
        //this->worldName = simulationConfig.getstd::string("worldname");

        //Agent.resetAgents();

        //Controller.getProgress().reportWorldCreation(worldName);

        // buildWalls();

        // initializeCoordinates();

        // createTime();

        // createPlaces();

        // createPeople();

        //freezeInfoFields();
    }

    std::string World::getWorldName()
    {
        return worldName;
    }

    int World::getHeight()
    {
        return height;
    }

    int World::getWidth()
    {
        return width;
    }

    bool World::isAWall(Position * pos)
    {
        return walls[pos->getRow()][pos->getCol()];
    }

    // std::vector<Agent> World::getPeople()
    // {
    //     std::vector<Agent> agents;
    //     agents.reserve(people.size());
    //     for (auto kv : map)
    //     {
    //         agents.push_back(kv.second);
    //     }
    //     return agents;
    // }

    // std::vector<Place> World::getPlaces()
    // {
    //     return places;
    // }

    // Calendar World::getTime()
    // {
    //     return time;
    // }

    //TRACKABLE FUNCTIONS : NEED DEEPER INVESTIGATION TO DETERMINE UTILITY OF THESE FUNCTIONS

    // Trackable World::findAnythingNear(Position pos, bool visibleOnly) throws NothingNearException
    // {
    //     try
    //     {
    //         return findAgentNear(pos, visibleOnly);
    //     }
    //     catch (NothingNearException e)
    //     {
    //         return findPlaceNear(pos, visibleOnly);
    //     }
    // }

    // Trackable World::findAgentNear(Position pos, bool visibleOnly)
    //     throws NothingNearException
    // {
    //     return findNearOutOf(pos, people.values(), NEAR_DISTANCE, visibleOnly);
    // }

    // Trackable World::findPlaceNear(Position pos, bool visibleOnly)
    //     throws NothingNearException
    // {
    //     return findNearOutOf(pos, places, NEAR_DISTANCE, visibleOnly);
    // }

    // Trackable findNearOutOf(Position pos,
    // 			final Collection<? extends Trackable> candidates,
    // 			final int distance, final boolean visibleOnly)
    // 			throws NothingNearException
    // {
    //     Trackable target = null;
    //     Trackable candidate = null;

    //     Iterator < ? extends Trackable > candidateIt = candidates.iterator();

    //     while ((target == null) && candidateIt.hasNext())
    //     {
    //         candidate = (Trackable)candidateIt.next();

    //         if ((!visibleOnly || candidate.isVisible()) && candidate.getPos().isNear(pos, distance))
    //         {
    //             target = candidate;
    //             if (visibleOnly && !((Trackable)candidate).isVisible())
    //             {
    //                 target = null;
    //             }
    //         }
    //     }

    //     if (target == null)
    //     {
    //         throw new NothingNearException();
    //     }
    //     else
    //     {
    //         return target;
    //     }
    // }

    // std::vector<Trackable> findAllAgentsNear(Position pos, int distance, bool visibleOnly)
    //     throws NothingNearException
    // {
    //     return findAllNearOutOf(pos, people.values(), distance, visibleOnly);
    // }

    // std::vector<Trackable> findAllNearOutOf(Position pos, final Collection<? extends Trackable> candidates, final int distance, final boolean visibleOnly)
    // 			throws NothingNearException
    // {
    //     ArrayList<Trackable> targets = new ArrayList<Trackable>();
    //     Trackable candidate;

    //     Iterator < ? extends Trackable > candidatesIt = candidates.iterator();

    //     while (candidatesIt.hasNext())
    //     {
    //         candidate = (Trackable)candidatesIt.next();

    //         if ((!visibleOnly || candidate.isVisible()) && candidate.getPos().isNear(pos, distance))
    //         {
    //             targets.add(candidate);
    //         }
    //     }

    //     if (targets.isEmpty())
    //     {
    //         throw new NothingNearException();
    //     }
    //     else
    //     {
    //         return targets;
    //     }
    // }

    // Place World::getPlaceByName(std::string name)
    //     throws PlaceNotFoundException
    // {
    //     Iterator<Place> placesIt = places.iterator();

    //     while (placesIt.hasNext())
    //     {
    //         Place p = placesIt.next();

    //         if (p.getName().equals(name))
    //         {
    //             return p;
    //         }
    //     }

    //     throw new PlaceNotFoundException(name);
    // }

    // Place World::getPlaceByPosition(Position pos)
    //         throws PlaceNotFoundException
    //     {
    //         Iterator<Place> placesIt = places.iterator();

    //         while (placesIt.hasNext())
    //         {
    //             Place p = placesIt.next();

    //             if (p.getPos().equals(pos))
    //             {
    //                 return p;
    //             }
    //         }

    //         throw new PlaceNotFoundException("at " + pos.toString());
    //     }

    // Collection<Place> World::getPlacesOfType(final String type)
    //     throws PlaceTypeUndefinedException
    // {
    //     if (!placeTypes.contains(type))
    //     {
    //         throw new PlaceTypeUndefinedException(type);
    //     }

    //     ArrayList<Place> selection = new ArrayList<Place>();
    //     Iterator<Place> it = places.iterator();

    //     while (it.hasNext())
    //     {
    //         Place p = (Place)it.next();

    //         if (p.getType().equals(type))
    //         {
    //             selection.add(p);
    //         }
    //     }

    //     return selection;
    // }

    // Place World::getNearestPlaceOfType(final std::tring type, final Position pos)
    //     throws PlaceTypeUndefinedException
    // {
    //     Place nearest = null;
    //     double minDistance = -1;
    //     Iterator<Place> pIt = getPlacesOfType(type).iterator();

    //     while (pIt.hasNext())
    //     {
    //         Place p = pIt.next();
    //         double distance = p.distanceFrom(pos);

    //         if ((distance < minDistance) || (nearest == null))
    //         {
    //             nearest = p;
    //             minDistance = distance;
    //         }
    //     }

    //     return nearest;
    // }

    // SortedMap<String, Overlay> getOverlays()
    // {
    //     return overlays;
    // }

    std::set<std::string> World::getPlaceTypes()
    {
        return placeTypes;
    }

    void World::addPlaceType(const std::string placeType)
    {
        placeTypes.insert(placeType);
    }

    BaseAgentModel *World::getAgentModel()
    {
        return agentModel;
    }

    BaseContextModel *World::getContextModel()
    {
        return contextModel;
    }

    BaseWorldModel *World::getWorldModel()
    {
        return worldModel;
    }