
#include <iostream>

int main() {
    int *tab;
    if (tab == nullptr) {
        std::cout << "Equivalent to nullptr\n";
    }

    if (!tab) {
        std::cout << "Equivalent to false ptr\n";
    }
}