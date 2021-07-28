#include <siafu/Controller.h>
#include <assert.h>
#include <iostream>

void test1(){
    Controller* controller = new Controller("./ressources/Simulation-Office/", -1, false);
    //Simulation* simulation = new Simulation("1",controller);
    std::cout << "Test 1 passed\n";
}   

int main(){
    test1();
}