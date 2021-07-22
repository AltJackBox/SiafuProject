#ifndef BASECONTEXTMODEL_H
#define BASECONTEXTMODEL_H

class World;

class BaseContextModel
{

protected:
	World* world;

public:
	BaseContextModel();

	// ~BaseContextModel(){
	// 	delete world;
	// }
	
	BaseContextModel(World* world)
	{
		this->world = world;
	}

	//virtual void createOverlays(final ArrayList<Overlay> olList);

	//virtual void doIteration(final Map<String, Overlay> overlays);
};

#endif