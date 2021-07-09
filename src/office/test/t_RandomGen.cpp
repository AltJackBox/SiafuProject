#include <random>
#include <iostream>

int main() {
    //std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(1); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, 10);
    int aux = dis(gen);

    for (int i = 0; i < 10 ; i++) {
        std::cout << aux << " ";
        aux = dis(gen);
    }
    std::cout << "\n";
}