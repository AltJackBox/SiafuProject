#include <siafu/Controller.h>
#include <assert.h>

void test1(){
    Controller* controller = new Controller("","1");
    ConsoleProgress* progress = controller->getProgress();
    assert(progress != NULL);
    World* world = controller->getWorld();
    assert(world != NULL);
    SimulationData* simData = controller->getSimulationData();
    assert(simData != NULL);
    std::cout << "Test 1 passed\n";
}

int main(){
    test1();
}