#include <utils/PersistentCachedMap.h>
#include <model/Position.h>
#include <model/Gradient.h>
#include <model/World.h>

int main() {
    World* world = new World();
    Position* pos = new Position(0,3);
    Gradient* grad = new Gradient(pos, world); // center

    PersistentCachedMap* pcm = new PersistentCachedMap("./ressources/CalculatedGradients/", "Simulation-Office", 100);

    pcm->persistObject(pos, grad);

    grad = pcm->recoverObject(pos->toString());

    std::cout << "Recovered gradient contains : " + grad->toString() + " as center position\n";

}