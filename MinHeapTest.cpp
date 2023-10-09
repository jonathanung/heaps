#include "MinHeap.hpp"
#include <iostream>

int main() {
    std::vector<int> test = {1,5,3,7,10,3,15,64,167,3,256,124,57,994,61,262};
    MinHeap mH = MinHeap(test);
    std::cout << mH;
    for (int i = 0; i < test.size(); i++) {
        std::cout << mH.extract() << std::endl;
    }
    return 0;
}