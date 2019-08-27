#include <random>
#include <iostream>

int main() {
    for (int i = 0; i < 20; i++) {
        std::cout << std::rand() % 6 + 1 << std::endl;
    }
    return 0;
}