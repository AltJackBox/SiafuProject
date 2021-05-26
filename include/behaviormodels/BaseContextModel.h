#ifndef BASECONTEXTMODEL_H
#define BASECONTEXTMODEL_H

#include <model/World.h>

class BaseContextModel {
	
	protected:
     World world;

	public:
    BaseContextModel(const World world) {
		this->world = world;
	}

	//virtual void createOverlays(final ArrayList<Overlay> olList);

	//virtual void doIteration(final Map<String, Overlay> overlays);
};

#endif