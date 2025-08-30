#include "ql/math/randomnumbers/primitivepolynomials.hpp"
#include "utilities.hpp"
#include <ql/math/randomnumbers/sobolrsg.hpp>
#include <boost/test/tools/old/interface.hpp>
#include <vector>
#include <boost/test/included/unit_test.hpp>
#include <chrono>

using namespace QuantLib;
using namespace boost::unit_test_framework;

std::vector<int> dimensionality_vector{1,2,3,4,5,10,15,15,50,100,250,500,1000,1500,2500,5000,7500,10000,12500,15000,17500,20000,PPMT_MAX_DIM};
void benchmark1() {
    for(int j = 0; j < dimensionality_vector.size(); j++) {
        std::cout << dimensionality_vector[j] << std::endl;
        SobolRsg rsg(dimensionality_vector[j], 0);

        auto start = std::chrono::high_resolution_clock::now();
        int points = 100'000;
        for (int i=0; i<points; i++) {
            rsg.nextSequence().value;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    }
}

void benchmark2() {
    int total_points = PPMT_MAX_DIM * 50000;
    for(int j = 0; j < dimensionality_vector.size(); j++) {
        std::cout << dimensionality_vector[j] << std::endl;
        SobolRsg rsg(dimensionality_vector[j], 0);

        auto start = std::chrono::high_resolution_clock::now();
        int points = 0;
        for (int i=0; points<total_points; i++) {
            points += dimensionality_vector[j];
            rsg.nextSequence().value;
        }
        std::cout << points << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    }
}

int main() {
    benchmark2();
}
