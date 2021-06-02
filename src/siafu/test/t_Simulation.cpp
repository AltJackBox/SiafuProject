#include <siafu/Simulation.h>
#include <assert.h>

void test1(){
    Controller* controller = new Controller("","1");
    Simulation* simulation = new Simulation("",controller);
    std::cout << "Test 1 passed\n";
}   

int main(){
    test1();
}