#include "MaxNodeHeap.hpp"
#include "HeapNode.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    srand(time(0));
    std::vector<int> test = {1, 5, 3, 7, 10, 3, 15, 64, 167, 3, 256, 124, 57, 994, 61, 262};
        MaxNodeHeap<std::string> mH = MaxNodeHeap<std::string>();
    for (int i = 0; i < test.size(); i++) {
        std::string str = "";
        for (int i = 0; i < 4; i++) {
            str += rand() % 26 + 97;
        }
        mH.insert(str, test[i]);
    }
    std::cout << mH;
    for (int i = 0; i < test.size(); i++) {
        std::cout << mH.extractNode() << std::endl;
    }
    return 0;
}