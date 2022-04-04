#include "doctest.h"
#include "Matrix.hpp"
#include <vector>
#include <assert.h>
#include <string>
#include <iostream>
#include <sstream>

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

void generateZeroMat(std::vector<double> &randomVec) {
    for (std::string::size_type i = 0; i < randomVec.size(); ++i) {
        randomVec[i] = 0;
    }
}


TEST_CASE ("bad input - row*col NOT equal to size of vector") {
    std::vector<double> vec(30);
    generateRandomVector(vec);
    srand(time(NULL));
    int row, col;
    for (int i = 0; i < 100; ++i) {
        row = 1 + std::rand() % 30;
        col = 1 + std::rand() % 30;
        if (row * col != vec.size()) {
                    CHECK_THROWS(Matrix(vec, row, col));
        }
    }
}

TEST_CASE ("bad input - can't add or subtract two matrices with different dimensions") {
    std::vector<double> vec(300);
    generateRandomVector(vec);
    for (int i = 1; i < 21; ++i) {
        // checking if the division is an integer
        if (300 / i == 300 / double(i)) {
            Matrix firstMat(vec, i, 300 / i);
            Matrix secondMat(vec, 300 / i, i);
                    CHECK_THROWS(firstMat + secondMat);
                    CHECK_THROWS(firstMat += secondMat);
                    CHECK_THROWS(firstMat - secondMat);
                    CHECK_THROWS(firstMat -= secondMat);
                    CHECK_THROWS(secondMat - firstMat);
                    CHECK_THROWS(secondMat -= firstMat);
        }
    }
}

TEST_CASE ("bad input - can't compare two matrices with different dimensions") {
    std::vector<double> vec(300);
    generateRandomVector(vec);
    for (int i = 1; i < 21; ++i) {
        // checking if the division is an integer
        if (300 / i == 300 / double(i)) {
            Matrix firstMat(vec, i, 300 / i);
            Matrix secondMat(vec, 300 / i, i);
                    CHECK_THROWS(if (firstMat == secondMat));
                    CHECK_THROWS(if (firstMat != secondMat));
                    CHECK_THROWS(if (firstMat > secondMat));
                    CHECK_THROWS(if (firstMat < secondMat));
                    CHECK_THROWS(if (firstMat <= secondMat));
                    CHECK_THROWS(if (firstMat >= secondMat));
        }
    }
}

TEST_CASE ("bad input - Undefined multiplication between 2 matrices") {
    std::vector<double> vec(300);
    generateRandomVector(vec);
            CHECK_THROWS(Matrix(vec, 10, 30) * Matrix(vec, 20, 15));
            CHECK_THROWS(Matrix(vec, 10, 30) *= Matrix(vec, 20, 15));

            CHECK_THROWS(Matrix(vec, 2, 150) * Matrix(vec, 30, 10));
            CHECK_THROWS(Matrix(vec, 150, 2) *= Matrix(vec, 20, 15));

            CHECK_THROWS(Matrix(vec, 10, 30) * Matrix(vec, 4, 75));
            CHECK_THROWS(Matrix(vec, 2, 150) *= Matrix(vec, 75, 4));

            CHECK_THROWS(Matrix(vec, 20, 15) * Matrix(vec, 20, 15));
            CHECK_THROWS(Matrix(vec, 10, 30) *= Matrix(vec, 10, 30));
}

TEST_CASE ("good input - well defined multiplication between 2 matrices") {
    std::vector<double> vec(300);
    generateRandomVector(vec);
    for (int i = 1; i < 20; ++i) {
        // checking if the division is an integer
        if (300 / i == 300 / double(i)) {
            Matrix firstMat(vec, i, 300 / i);
            Matrix secondMat(vec, 300 / i, i);
                    CHECK_NOTHROW(firstMat * secondMat);
                    CHECK_NOTHROW(secondMat * firstMat);
        }
    }
}

TEST_CASE ("bad input - row and col must be positive") {
    std::vector<double> vec(300);
    generateRandomVector(vec);
            CHECK_THROWS(Matrix(vec, -10, -30));
            CHECK_THROWS(Matrix(vec, -30, -10));

            CHECK_THROWS(Matrix(vec, -150, -2));
            CHECK_THROWS(Matrix(vec, -2, -150));

            CHECK_THROWS(Matrix(vec, -4, -75));
            CHECK_THROWS(Matrix(vec, -75, -4));

            CHECK_THROWS(Matrix(vec, -6, -50));
            CHECK_THROWS(Matrix(vec, -50, -6));

}

TEST_CASE ("bad input - row and cols can't be zero") {
    std::vector<double> vec(10);
    generateRandomVector(vec);
            CHECK_THROWS(Matrix(vec, 10, 0));
            CHECK_THROWS(Matrix(vec, 0, 10));
            CHECK_THROWS(Matrix(vec, 0, 0));
}

TEST_CASE ("good output") {
    std::vector<double> vec{2, 4.3, 5.0, 2, 3, 1.7, 4.1, 2.5, 0, 19, 4, 4, 4, 4, 4};
    std::vector<double> unaryMinus{-1, -2, -3, -4, -5, -6, -7, -8, -9};
    std::vector<double> unaryPlus{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<double> vecOfZeros(9);
    generateZeroMat(vecOfZeros);

    Matrix newMat{unaryPlus, 3, 3};
    newMat += Matrix(unaryMinus, 3, 3);
            CHECK_EQ(newMat, Matrix(vecOfZeros, 3, 3));

    newMat -= Matrix(unaryMinus, 3, 3);
            CHECK_EQ(newMat, Matrix(unaryPlus, 3, 3));
            CHECK_EQ(newMat + newMat, Matrix(std::vector<double>{2, 4, 6, 8, 10, 12, 14, 16, 18}, 3, 3));
            CHECK_EQ(newMat - Matrix(vecOfZeros, 3, 3), newMat);
            CHECK_EQ(Matrix(unaryMinus, 3, 3), -Matrix(unaryPlus, 3, 3));

    std::stringstream ss;
    ss << Matrix(vec, 5, 3);
            CHECK(ss.str() == "[2 4.3 5]\n[2 3 1.7]\n[4.1 2.5 0]\n[19 4 4]\n[4 4 4]");
}

//TEST_CASE ("bad output") {
//
//}

