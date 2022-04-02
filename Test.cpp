#include "doctest.h"
#include "Matrix.hpp"
#include <vector>

using namespace zich;

double fRand(double fMin, double fMax) {
    double f = (double) rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void generateRandomVector(std::vector<double> &randomVec) {
    srand(time(NULL));
    for (std::string::size_type i = 0; i < randomVec.size(); ++i) {
        randomVec[i] = fRand(-300, 300);
    }
}


TEST_CASE ("..") {
    srand(time(NULL));
    std::vector<double> vec(std::rand() % 100);
    generateRandomVector(vec);
}

TEST_CASE ("bad input - row*col NOT equal to size of vector") {
    std::vector<double> vec(30);
    generateRandomVector(vec);
    srand(time(NULL));
    int row, col;
    for (int i = 0; i < 100; ++i) {
        row = std::rand() % 30;
        col = std::rand() % 30;
        if (row * col != vec.size()) {
                    CHECK_THROWS(Matrix(vec, row, col));
        }
    }
}

TEST_CASE ("bad input - can't added or subtract two matrices with different dimensions") {
    srand(time(NULL));
    std::vector<double> vec(50);
    generateRandomVector(vec);
    for (int i = 0; i < 25; ++i) {
        Matrix firstMat(vec, i, 50 - i);
        Matrix secondMat(vec, 50 - i, i);
                CHECK_THROWS(firstMat + secondMat);
                CHECK_THROWS(firstMat - secondMat);
                CHECK_THROWS(secondMat - firstMat);
    }

}

TEST_CASE ("bad input - can't compare two matrices with different dimensions") {
    srand(time(NULL));
    std::vector<double> vec(100);
    generateRandomVector(vec);
    for (int i = 0; i < 50; ++i) {
        Matrix firstMat(vec, i, 100 - i);
        Matrix secondMat(vec, 100 - i, i);
                CHECK_THROWS(if (firstMat == secondMat));
                CHECK_THROWS(if (firstMat != secondMat));
                CHECK_THROWS(if (firstMat > secondMat));
                CHECK_THROWS(if (firstMat < secondMat));
                CHECK_THROWS(if (firstMat <= secondMat));
                CHECK_THROWS(if (firstMat >= secondMat));
    }

}

TEST_CASE ("") {

}