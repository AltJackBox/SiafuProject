#ifndef BASEWORLDMODEL_H
#define BASEWORLDMODEL_H

#include <vector>

class Place;
class World;

class BaseWorldModel
{

protected:
	World *world;

public:
	BaseWorldModel();

	virtual ~BaseWorldModel()
	{
	}

	BaseWorldModel(World *world)
	{
		this->world = world;
	}

	virtual void createPlaces(std::vector<Place *> places) {}

	virtual void doIteration(std::vector<Place *> places) {}
};

#endif
