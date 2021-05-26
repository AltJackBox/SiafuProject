#ifndef BASEAGENTMODEL_H
#define BASEAGENTMODEL_H

#include <model/World.h>
#include <vector>

class BaseAgentModel {

	protected:
     World world;

	public:
     BaseAgentModel(const World world) {
		this->world = world;
	}

	//virtual std::vector<Agent> createAgents();

	//virtual void doIteration(final Collection<Agent> agents);
};

#endif
