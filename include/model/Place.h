#ifndef PLACE_H
#define PLACE_H

#include <siafu/Controller.h>
#include <model/World.h>
#include <types/Publishable.h>
#include <utils/PersistentCachedMap.h>
#include <string>
#include <map>

class Position;
class World;
class Gradient;

class Place : public Publishable
{

private:
	static PersistentCachedMap *gradients;

	static World *world;

	std::string type;

	Position *pos;

	Gradient *temporaryGradient = nullptr;

	bool visible = true;

	std::map<std::string, Publishable *> info;

	void basicChecks(World *thisPlacesWorld);

public:
	std::string name;

	static void initialize(World *newWorld)
	{
		world = newWorld;
		gradients = nullptr;
		gradients = new PersistentCachedMap(DEFAULT_GRADIENT_PATH, "Simulation-Office", World::getCacheSize());
	}

	Place();

	~Place();

	static void removePlacePointers()
	{
		delete gradients;
	}

	Place(std::string type, Position *pos, World *world);

	Place(std::string type, Position *pos, World *world, std::string name, Position *relevantPosition);

	std::string toString() override;

	std::string getName();

	void setName(std::string name);

	std::string getPlaceType();

	Position *getPos();

	void set(std::string key, Publishable *value);

	Publishable *get(std::string key);

	Gradient *getGradient();

	int pointFrom(Position *targetPos, int preferedDir);

	int distanceFrom(Position *targetPos);

	bool equals(Place *p);

	std::string getType() override;
};

#endif
