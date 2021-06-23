#include <model/World.h>
#include <model/SimulationData.h>

void test1(){
    SimulationData* sm = SimulationData::getInstance("./ressources/Simulation-Office/");

    World* world = new World(nullptr, sm);
    std::cout << "Test 1 passed\n";
}

int main(){
    test1();
}