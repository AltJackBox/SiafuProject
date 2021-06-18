#ifndef BASEAGENTMODEL_H
#define BASEAGENTMODEL_H

#include <vector>

class World;

class BaseAgentModel {

	protected:
     World world;

	public:
	BaseAgentModel();
    BaseAgentModel(const World world) {
		this->world = world;
	}

	virtual std::vector<Agent*> createAgents();

	virtual void doIteration(std::vector<Agent*> agents);
};

#endif
