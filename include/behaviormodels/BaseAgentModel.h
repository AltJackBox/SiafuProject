#ifndef BASEAGENTMODEL_H
#define BASEAGENTMODEL_H

#include <vector>

class Agent;
class World;

class BaseAgentModel
{

protected:
	World *world;

public:
	BaseAgentModel();

	virtual ~BaseAgentModel()
	{
	}

	BaseAgentModel(World *world)
	{
		this->world = world;
	}

	virtual std::vector<Agent *> createAgents()
	{
		return std::vector<Agent *>();
	}

	virtual void doIteration(std::vector<Agent *> agents) {}
};

#endif
