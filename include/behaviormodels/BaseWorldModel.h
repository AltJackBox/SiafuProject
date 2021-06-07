#ifndef BASEWORLDMODEL_H
#define BASEWORLDMODEL_H


class World;

class BaseWorldModel {
	
	protected:
    World world;

	public:
	BaseWorldModel();
    BaseWorldModel(const World world) {
		this->world = world;
	}

	//virtual void createPlaces(ArrayList<Place> places);

	//virtual void doIteration(final Collection<Place> places);

};

#endif
