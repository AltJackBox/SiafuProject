#ifndef BASEWORLDMODEL_H
#define BASEWORLDMODEL_H

#include <vector>


class World;
class Place;

class BaseWorldModel {
	
	protected:
    World* world;

	public:
	BaseWorldModel();
    BaseWorldModel(World* world) {
		this->world = world;
	}

	virtual void createPlaces(std::vector<Place*> places);

	virtual void doIteration(std::vector<Place*> places);

};

#endif
