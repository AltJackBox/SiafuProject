#include <model/SimulationData.h>

void test1(){

    SimulationData* sm = SimulationData::getInstance("./ressources/Simulation-Office/");
    
    std::vector<std::string> places = sm->getPlaceFiles();
    std::cout << "Place files found : \n";
    int index = 0;
    while (index != places.size()){
        std::cout << places[index] + "\n";
        index++;
    }

    std::string walls = sm->getWallsFile();
    std::cout << "Wall file found : " + walls + "\n";

    std::cout << "Test 1 passed\n";
}

int main(){
    test1();
}