
#include <iostream>

int main() {
    int *tab = nullptr;

    if (tab == NULL) {
        std::cout << "Equivalent to null\n";
    }
    if (tab == nullptr) {
        std::cout << "Equivalent to nullptr\n";
    }

    if (!tab) {
        std::cout << "Equivalent to false ptr\n";
    }
}