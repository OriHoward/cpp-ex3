#include "doctest.h"
#include "Matrix.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>


const int VEC_SIZE = 300;

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

TEST_CASE ("bad input - can't add or subtract or compare two matrices with different dimensions") {
    std::vector<double> vec(VEC_SIZE);
    generateRandomVector(vec);
    for (int i = 1; i < 21; ++i) {
        // checking if the division is an integer
        if (VEC_SIZE / i == VEC_SIZE / double(i)) {
            Matrix firstMat(vec, i, VEC_SIZE / i);
            Matrix secondMat(vec, VEC_SIZE / i, i);
                    CHECK_THROWS(firstMat + secondMat);
                    CHECK_THROWS(firstMat += secondMat);
                    CHECK_THROWS(firstMat - secondMat);
                    CHECK_THROWS(firstMat -= secondMat);
                    CHECK_THROWS(secondMat - firstMat);
                    CHECK_THROWS(secondMat -= firstMat);
                    CHECK_THROWS(bool check(firstMat == secondMat)); // to check which one is good
                    CHECK_THROWS(if (firstMat != secondMat));
                    CHECK_THROWS(if (firstMat > secondMat));
                    CHECK_THROWS(if (firstMat < secondMat));
                    CHECK_THROWS(if (firstMat <= secondMat));
                    CHECK_THROWS(if (firstMat >= secondMat));
        }
    }
}


TEST_CASE ("bad input - Undefined multiplication between 2 matrices") {
    std::vector<double> vec(VEC_SIZE);
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
    std::vector<double> vec(VEC_SIZE);
    generateRandomVector(vec);
    for (int i = 1; i < 20; ++i) {
        // checking if the division is an integer
        if (VEC_SIZE / i == VEC_SIZE / double(i)) {
            Matrix firstMat(vec, i, VEC_SIZE / i);
            Matrix secondMat(vec, VEC_SIZE / i, i);
                    CHECK_NOTHROW(firstMat * secondMat);
                    CHECK_NOTHROW(secondMat * firstMat);
        }
    }
}

TEST_CASE ("bad input - row and col must be positive") {
    std::vector<double> vec(VEC_SIZE);
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
    std::vector<double> negativeVec{-1, -2, -3, -4, -5, -6, -7, -8, -9};
    std::vector<double> positiveVec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<double> vecOfZeros{0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<double> doubleNegativeVec{2, 4, 6, 8, 10, 12, 14, 16, 18};
    Matrix positiveMat(positiveVec, 3, 3);
    Matrix negativeMat(negativeVec, 3, 3);
    Matrix matOfZeros(vecOfZeros, 3, 3);
    Matrix regularMat(vec, 5, 3);
    Matrix doubleNegativeMat(doubleNegativeVec, 3, 3);

    /**
     * testing the operators : +, += , - ,-= in sub cases.
     */
            SUBCASE("+operator") {
                CHECK_EQ(positiveMat + negativeMat, matOfZeros);
                CHECK_EQ(negativeMat + positiveMat, matOfZeros);
    }

            SUBCASE ("+=operator") {
        positiveMat += negativeMat;
                CHECK_EQ(positiveMat, matOfZeros);
        negativeMat += matOfZeros;
                CHECK_EQ(negativeMat, negativeMat);
    }

            SUBCASE("-operator") {
                CHECK_EQ((negativeMat) - positiveMat, doubleNegativeMat);
                CHECK_EQ(positiveMat - positiveMat, matOfZeros);
    }
            SUBCASE("-=operator") {
        negativeMat -= negativeMat;
                CHECK_EQ(negativeMat, matOfZeros);

    }

//
//    newMat -= Matrix(negativeMat, 3, 3);
//            CHECK_EQ(newMat, Matrix(positiveMat, 3, 3));
//            CHECK_EQ(newMat + newMat, Matrix(std::vector<double>{2, 4, 6, 8, 10, 12, 14, 16, 18}, 3, 3));
//            CHECK_EQ(newMat - Matrix(vecOfZeros, 3, 3), newMat);
//            CHECK_EQ(Matrix(negativeMat, 3, 3), -Matrix(positiveMat, 3, 3));
    /**
     * testing the string output
     */
//    std::stringstream ss;
//    ss << Matrix(vec, 5, 3);
//            CHECK_EQ(ss.str(), "[2 4.3 5]\n[2 3 1.7]\n[4.1 2.5 0]\n[19 4 4]\n[4 4 4]");
//    ss.str("");
//    ss << Matrix(negativeMat, 3, 3);
//            CHECK(ss.str() == "[-1 -2 -3]\n[-4 -5 -6]\n[-7 -8 -9]");
//    ss.str("");
//    ss << Matrix(vecOfZeros, 3, 3);
//            CHECK(ss.str() == "[0 0 0]\n[0 0 0]\n[0 0 0]");
//    ss.str("");
//    ss << -Matrix(vecOfZeros, 3, 3);
//            CHECK_EQ(ss.str(), "[0 0 0]\n[0 0 0]\n[0 0 0]");
}

//TEST_CASE ("bad output") {
//
//}

