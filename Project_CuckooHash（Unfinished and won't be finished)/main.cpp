#include "CuckooHash.h"
int main() {
    // Number of elements to test with
    int numElements = 1000000;

    // Test with different load factors (e.g., 0.2, 0.4, 0.6, 0.8)
    std::vector<double> loadFactors = {0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5};
    
    // Run the test for each load factor
    for (double loadFactor : loadFactors) {
        testCuckooHashTable(numElements, loadFactor);
    }

    return 0;
}