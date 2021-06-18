#ifndef PLACE_H
#define PLACE_H

#include <types/Publishable.h>
#include <string>
#include <map>

class Position;
class World;
class Gradient;

class Place : public Publishable
{

private:
	//static PersistentCachedMap gradients;

	static World *world;

	std::string type;

	Position *pos;

	Gradient *temporaryGradient;

	bool visible = true;

	std::map<std::string, Publishable> info;

	void basicChecks(World *thisPlacesWorld);

public:
	std::string name;

	static void Place::initialize(World *newWorld)
	{
		world = newWorld;
		// Allow the old value to be garbage
		// collected before the next is created
		// gradients = null;

		// gradients =
		//     new SiafuGradientCache(Controller.DEFAULT_GRADIENT_PATH,
		//                            world.getWorldName(), World.getCacheSize(),
		//                            World.shouldPrefillCache());
	}

	Place();

	Place(std::string type, Position *pos, World *world);

	Place(std::string type, Position *pos, World *world, std::string name, Position *relevantPosition);

	std::string toString();

	std::string getName();

	void setName(std::string name);

	std::string getType();

	Position *getPos();

	void set(std::string key, Publishable value);

	Publishable get(std::string key);

	Gradient *getGradient();

	int pointFrom(Position *targetPos, int preferedDir);

	int distanceFrom(Position *targetPos);

	bool equals(Place *p);
};

#endif
