#include <model/Place.h>
#include <model/World.h>
#include <model/Position.h>
#include <model/Gradient.h>

#include <string>
#include <iostream>
#include <utility>

void Place::basicChecks(World *thisPlacesWorld)
{
    // if (gradients == null) {
    // 	throw new InitializationRequiredException(
    // 			"You need to initialize the Place class");
    // }
    if (world != thisPlacesWorld)
    {
        std::cerr << "All your places must belong to the same World.";
    }
}

Place::Place(std::string type, Position *pos, World *world)
{
    Place(type, pos, world, type + "-" + pos->toString(), NULL);
}

// Can throw position unreachable
Place::Place(std::string type, Position *pos, World *world, std::string name, Position *relevantPosition)
{
    basicChecks(world);
    if (world->isAWall(pos))
    {
        std::cerr << "PositionOnAWallException";
    }
    this->type = type;
    this->pos = pos;
    this->name = name;

    world->addPlaceType(type);

    if (relevantPosition != NULL) {
    	temporaryGradient = new Gradient(pos, world, relevantPosition);
    } /* else if (!gradients.containsKey(pos.tostd::string())) { */
    // 	gradients.put(pos, new Gradient(pos, world));
    // }
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

std::string Place::getType()
{
    return type;
}

Position *Place::getPos()
{
    return pos;
}

void Place::set(std::string key, Publishable value)
{
    std::pair<std::string, Publishable> pair;
    pair = std::make_pair(key, value);
    info.insert(pair);
}

Publishable Place::get(std::string key)
{
    if (info.find(key) == info.end())
    {
        std::cerr << "InfoUndefinedException " + key;
    }

    return info.at(key);
}

Gradient* Place::getGradient()
{
    if (temporaryGradient != NULL)
    {
        return temporaryGradient;
    }
    // else
    // {
        // return (Gradient)gradients.get(pos.tostd::string());
    // }
}

int Place::pointFrom(Position* targetPos, int preferedDir)
{
    return getGradient()->pointFrom(targetPos, preferedDir);
}

int Place::distanceFrom(Position* targetPos)
{
    return getGradient()->distanceFrom(targetPos);
}

bool Place::equals(Place* p){
    return (this->getPos()->equals(p->getPos())) && (this->getName().compare(p->getName()));
}