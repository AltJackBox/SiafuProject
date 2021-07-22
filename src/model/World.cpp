#include <model/World.h>
#include <model/Agent.h>
#include <model/Position.h>
#include <siafu/Simulation.h>
#include <siafu/Controller.h>
#include <model/SimulationData.h>
#include <model/Place.h>
#include <progress/Progress.h>
#include <office/AgentModel.h>
#include <office/WorldModel.h>
#include <office/Constants.h>
#include <Calendar.h>
#include <behaviormodels/BaseAgentModel.h>
#include <behaviormodels/BaseWorldModel.h>
#include <exceptions/PlaceTypeUndefinedException.h>
#include <exceptions/PositionOnAWallException.h>
#include <iostream>

int World::cacheSize;

extern "C"
{
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
}

World::~World()
{
    if (time)
    {
        delete time;
        time = nullptr;
    }
    if (agentModel)
    {
        delete agentModel;
        agentModel = nullptr;
    }
    if (worldModel)
    {
        delete worldModel;
        worldModel = nullptr;
    }
    if (walls)
    {
        delete[] walls;
        walls = nullptr;
    }
    // delete simData;
    if (!places.empty())
    {
        for (Place* &pl : places)
        {
            if (pl)
            {
                delete pl;
                pl = nullptr;
            }
        }
    }
    Constants::removeConstantsPointers();
    ActivityManager::removeFieldsPointers();

    if (!people.empty())
    {
        for (std::pair<const std::string, Agent *> &ag : people)
        {
            if (ag.second) {
                delete ag.second;
                ag.second = nullptr;
            }
        }
    }
    //delete simulation;
}

bool load_image(std::vector<unsigned char> &image, const std::string &filename, int &x, int &y)
{
    int n;
    unsigned char *data = stbi_load(filename.c_str(), &x, &y, &n, 1);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y);
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
        exit(EXIT_FAILURE);
    }
    size_t index;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            index = (y * width + x);
            if (image[index] == 0)
            {
                Position *attractor;
                try
                {
                    attractor = new Position(y, x);
                    placePoints.push_back(attractor);
                }
                catch (const PositionUnreachableException &e)
                {
                    throw std::runtime_error("Place (" + std::to_string(x) + "." + std::to_string(y) + ") is unreachable. Is it out of the map or on a wall ?");
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
        throw std::runtime_error("World.cpp : Error loading image of the walls");
    }

    this->width = width;
    this->height = height;

    walls = new bool[height * width];

    int index;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            index = (y * width + x);
            walls[index] = (image[index] == COLOR_WHITE);
        }
    }
}

void World::initializeCoordinates()
{
    double topRight[2] = {TOPRIGHT_LATITUDE, TOPRIGHT_LONGITUDE};

    double bottomLeft[2] = {BOTTOMLEFT_LATITUDE, BOTTOMLEFT_LONGITUDE};

    double bottomRight[2] = {BOTTOMRIGHT_LATITUDE, BOTTOMRIGHT_LONGITUDE};

    Position::initialize(this, topRight, bottomRight, bottomLeft);
}

void World::createPeople()
{
    try
    {
        agentModel = new AgentModel(this);
    }
    catch (std::exception &e)
    {
        throw std::runtime_error("Can't instantiate the agent model");
    }

    Agent::initialize(this);
    Controller::getProgress()->reportCreatingAgents();
    std::vector<Agent *> peopleList = agentModel->createAgents();
    int index = 0;
    while (index != peopleList.size())
    {
        Agent *p = peopleList[index];
        std::pair<std::string, Agent *> pair(p->getName(), p);
        people.insert(pair);
        index++;
    }
}

void World::createTime()
{
    time = new Calendar();
}

void World::freezeInfoFields()
{
    for (std::pair<std::string, Agent *> element : people)
    {
        Agent *p = element.second;

        if (!p->checkAllInfoFieldsPresent())
        {
            throw std::runtime_error("Agent " + p->getName() + " is missing at least one field that other agents have.");
        }
    }

    Agent::lockInfoFields();
}

void World::createPlaces()
{
    try
    {

        worldModel = new WorldModel(this);
    }
    catch (std::exception &e)
    {
        throw std::runtime_error("Can't instantiate the world model");
    }
    places = createPlacesFromImages();
    worldModel->createPlaces(places);
}

std::vector<Place *> World::createPlacesFromImages()
{
    Place::initialize(this);
    std::vector<Place *> placesFromImg;
    std::vector<std::string> fileList = simData->getPlaceFiles();
    int index = 0;
    while (index != fileList.size())
    {
        std::string filename = fileList[index];
        std::vector<Position *> placePoints = readPlacePoints(filename);
        int indexVec = 0;
        Controller::getProgress()->reportPlacesFound(filename, placePoints.size());

        while (indexVec != placePoints.size())
        {
            Position *pos = placePoints[indexVec];
            Place *place;
            try
            {
                place = new Place(filename, pos, this);
            }
            catch (const PositionOnAWallException &e)
            {
                throw std::runtime_error("One of your " + filename + " places, at " + pos->toString() + " is on a wall");
            }
            Controller::getProgress()->reportPlaceCreated(filename);
            placesFromImg.push_back(place);
            indexVec++;
        }
        index++;
    }

    return placesFromImg;
}

World::World(Simulation *simulation, SimulationData *simData)
{
    this->simulation = simulation;
    this->simData = simData;
    this->worldName = "Siafu Offices, Heidelberg, Germany";

    Agent::resetAgents();

    Controller::getProgress()->reportWorldCreation(worldName);

    buildWalls();

    initializeCoordinates();

    createTime();

    createPlaces();

    createPeople();

    freezeInfoFields();
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

bool World::isAWall(Position *pos)
{
    return walls[pos->getRow() * width + pos->getCol()];
}

std::vector<Agent *> World::getPeople()
{
    std::vector<Agent *> agents;
    // for (std::pair<std::string, Agent *> element : people)
    // {
    //     agents.push_back(element.second);
    // }

    // Same order as in the Java version in order to check the results on a fixed scenario
    agents.push_back(people["RestHomeResident - 10"]);
    agents.push_back(people["RestHomeResident - 13"]);
    agents.push_back(people["RestHomeResident - 14"]);
    agents.push_back(people["RestHomeResident - 11"]);
    agents.push_back(people["RestHomeResident - 12"]);
    agents.push_back(people["RestHomeResident - 8"]);
    agents.push_back(people["RestHomeResident - 17"]);
    agents.push_back(people["RestHomeResident - 9"]);
    agents.push_back(people["RestHomeResident - 18"]);
    agents.push_back(people["RestHomeResident - 15"]);
    agents.push_back(people["RestHomeResident - 16"]);
    agents.push_back(people["RestHomeResident - 4"]);
    agents.push_back(people["RestHomeResident - 5"]);
    agents.push_back(people["RestHomeResident - 6"]);
    agents.push_back(people["RestHomeResident - 7"]);
    agents.push_back(people["RestHomeResident - 1"]);
    agents.push_back(people["RestHomeResident - 2"]);
    agents.push_back(people["RestHomeResident - 3"]);
    return agents;
}

std::vector<Place *> World::getPlaces()
{
    return places;
}

Calendar *World::getTime()
{
    return time;
}

std::vector<Place *> World::getPlacesOfType(std::string type)
{
    if (placeTypes.find(type) == placeTypes.end())
    {
        throw PlaceTypeUndefinedException(type);
    }

    std::vector<Place *> selection;
    int index = 0;

    while (index != places.size())
    {
        Place *p = places[index];

        if (p->getPlaceType().compare(type) == 0)
        {
            selection.push_back(p);
        }
        index++;
    }

    return selection;
}

Place *World::getNearestPlaceOfType(const std::string type, Position *pos)
{
    Place *nearest = nullptr;
    double minDistance = -1;
    std::vector<Place *> placesSelected = getPlacesOfType(type);
    int index = 0;
    while (index != placesSelected.size())
    {
        Place *p = placesSelected[index];
        double distance = p->distanceFrom(pos);

        if ((distance < minDistance) || (nearest == nullptr))
        {
            nearest = p;
            minDistance = distance;
        }
        index++;
    }

    return nearest;
}

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

BaseWorldModel *World::getWorldModel()
{
    return worldModel;
}

// BaseContextModel *World::getContextModel()
// {
//     return contextModel;
// }