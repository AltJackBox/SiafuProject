#include <model/Place.h>
#include <model/World.h>
#include <model/Position.h>
#include <model/Gradient.h>
#include <model/SimulationData.h>
#include <exceptions/PositionOnAWallException.h>
#include <exceptions/InitializationRequiredException.h>
#include <exceptions/InfoUndefinedException.h>
#include <utils/PersistentCachedMap.h>

#include <string>
#include <iostream>
#include <utility>

World *Place::world;
PersistentCachedMap *Place::gradients;

std::string PLACES = DEFAULT_PATH + PLACES_PATH;
std::string PNG = ".png";

void Place::basicChecks(World *thisPlacesWorld)
{
    if (gradients == nullptr)
    {
        throw InitializationRequiredException("You need to initialize the Place class.");
    }
    if (world != thisPlacesWorld)
    {
        std::cerr << "All your places must belong to the same World.\n";
        exit(EXIT_FAILURE);
    }
}

Place::Place(std::string type, Position *pos, World *world) : Place(type, pos, world, type + "-" + pos->toString(), nullptr)
{
}

Place::Place(std::string typeP, Position *pos, World *world, std::string nameP, Position *relevantPosition)
{
    basicChecks(world);
    if (world->isAWall(pos))
    {
        throw PositionOnAWallException();
    }
    this->pos = pos;

    // Erasing ressources & extension from type and name variables

    size_t pos1 = typeP.find(PLACES);
    if (pos1 != std::string::npos)
    {
        typeP.erase(pos1, PLACES.length());
    }
    size_t pos2 = typeP.find(PNG);
    if (pos2 != std::string::npos)
    {
        typeP.erase(pos2, PNG.length());
    }

    pos1 = nameP.find(PLACES);
    if (pos1 != std::string::npos)
    {
        nameP.erase(pos1, PLACES.length());
    }
    pos2 = nameP.find(PNG);
    if (pos2 != std::string::npos)
    {
        nameP.erase(pos2, PNG.length());
    }

    this->type = typeP;

    this->name = nameP;

    world->addPlaceType(typeP);

    if (relevantPosition != nullptr)
    {
        temporaryGradient = new Gradient(pos, world, relevantPosition);
    }
    else if (!(gradients->containsKey(pos->toString())))
    {
        gradients->put(pos, new Gradient(pos, world));
    }
}

std::string Place::toString()
{
    return getName();
}

std::string Place::getName()
{
    return name;
}

void Place::setName(std::string name)
{
    this->name = name;
}

std::string Place::getPlaceType()
{
    return type;
}

Position *Place::getPos()
{
    return pos;
}

void Place::set(std::string key, Publishable *value)
{
    std::pair<std::string, Publishable *> pair;
    pair = std::make_pair(key, value);
    info[pair.first] = pair.second;
}

Publishable *Place::get(std::string key)
{
    if (info.find(key) == info.end())
    {
        throw InfoUndefinedException(key);
    }

    return info.at(key);
}

Gradient *Place::getGradient()
{
    if (temporaryGradient != nullptr)
    {
        return temporaryGradient;
    }
    else
    {
        return (Gradient *)gradients->get(pos->toString());
    }
    return nullptr;
}

int Place::pointFrom(Position *targetPos, int preferedDir)
{
    return getGradient()->pointFrom(targetPos, preferedDir);
}

int Place::distanceFrom(Position *targetPos)
{
    return getGradient()->distanceFrom(targetPos);
}

bool Place::equals(Place *p)
{
    return (this->getPos()->equals(p->getPos())) && (this->getName().compare(p->getName()));
}

std::string Place::getType()
{
    return "Place";
}