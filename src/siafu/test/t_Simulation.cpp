#include <siafu/Controller.h>
#include <iostream>

void test1(){
    Controller* controller = new Controller("./ressources/Simulation-Office/", -1, false);
    std::cout << "Test 1 passed\n";
}   

int main(){
    test1();
}