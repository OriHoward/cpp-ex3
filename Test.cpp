#include "doctest.h"
#include "sources/Matrix.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>


const int VEC_SIZE = 300;
const int NUM_OF_LOOPS = 75;

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
    for (int i = 0; i <= NUM_OF_LOOPS; ++i) {
        row = 1 + std::rand() % 30;
        col = 1 + std::rand() % 30;
        if (row * col != vec.size()) {
                    CHECK_THROWS(Matrix({vec, row, col}));
        }
    }
}

TEST_CASE ("bad input - can't add or subtract or compare two matrices with different dimensions") {
    std::vector<double> vec(VEC_SIZE);
    generateRandomVector(vec);
    for (int i = 1; i <= NUM_OF_LOOPS; ++i) {
        // checking if the division is an integer
        if (VEC_SIZE / i == VEC_SIZE / double(i)) {
            Matrix firstMat{vec, i, VEC_SIZE / i};
            Matrix secondMat{vec, VEC_SIZE / i, i};
                    CHECK_THROWS(firstMat + secondMat);
                    CHECK_THROWS(firstMat += secondMat);
                    CHECK_THROWS(firstMat - secondMat);
                    CHECK_THROWS(firstMat -= secondMat);
                    CHECK_THROWS(secondMat - firstMat);
                    CHECK_THROWS(secondMat -= firstMat);
                    CHECK_THROWS(bool check(firstMat == secondMat));
                    CHECK_THROWS(bool check(firstMat != secondMat));
                    CHECK_THROWS(bool check(firstMat > secondMat));
                    CHECK_THROWS(bool check(firstMat < secondMat));
                    CHECK_THROWS(bool check(firstMat <= secondMat));
                    CHECK_THROWS(bool check(firstMat >= secondMat));

        }
    }
}


TEST_CASE ("bad input - Undefined multiplication between 2 matrices") {
    std::vector<double> vec(VEC_SIZE);
    generateRandomVector(vec);
            CHECK_THROWS(Matrix({vec, 10, 30}) * Matrix({vec, 20, 15}));
            CHECK_THROWS(Matrix({vec, 10, 30}) *= Matrix({vec, 20, 15}));

            CHECK_THROWS(Matrix({vec, 2, 150}) * Matrix({vec, 30, 10}));
            CHECK_THROWS(Matrix({vec, 150, 2}) *= Matrix({vec, 20, 15}));

            CHECK_THROWS(Matrix({vec, 10, 30}) * Matrix({vec, 4, 75}));
            CHECK_THROWS(Matrix({vec, 2, 150}) *= Matrix({vec, 75, 4}));

            CHECK_THROWS(Matrix({vec, 20, 15}) * Matrix({vec, 20, 15}));
            CHECK_THROWS(Matrix({vec, 10, 30}) *= Matrix({vec, 10, 30}));
}

TEST_CASE ("good input - well defined multiplication between 2 matrices") {
    std::vector<double> vec(VEC_SIZE);
    generateRandomVector(vec);
    for (int i = 1; i <= NUM_OF_LOOPS; ++i) {
        // checking if the division is an integer
        if (VEC_SIZE / i == VEC_SIZE / double(i)) {
            Matrix firstMat{vec, i, VEC_SIZE / i};
            Matrix secondMat{vec, VEC_SIZE / i, i};
                    CHECK_NOTHROW(firstMat * secondMat);
        }
    }
}

TEST_CASE ("bad input - row and col must be positive") {
    std::vector<double> vec(VEC_SIZE);
    generateRandomVector(vec);
            CHECK_THROWS(Matrix({vec, -10, -30}));
            CHECK_THROWS(Matrix({vec, -30, -10}));

            CHECK_THROWS(Matrix({vec, -150, -2}));
            CHECK_THROWS(Matrix({vec, -2, -150}));

            CHECK_THROWS(Matrix({vec, -4, -75}));
            CHECK_THROWS(Matrix({vec, -75, -4}));

            CHECK_THROWS(Matrix({vec, -6, -50}));
            CHECK_THROWS(Matrix({vec, -50, -6}));

}

TEST_CASE ("bad input - row and cols can't be zero") {
    std::vector<double> vec(10);
    generateRandomVector(vec);
            CHECK_THROWS(Matrix({vec, 10, 0}));
            CHECK_THROWS(Matrix({vec, 0, 10}));
            CHECK_THROWS(Matrix({vec, 0, 0}));
}

TEST_CASE ("good output") {

    /**
     * init all vectors
     */
    std::vector<double> vec{2, 4.3, 5.0, 2, 3, 1.7, 4.1, 2.5, 0, 19, 4, 4, 4, 4, 4};
    std::vector<double> negativeVec{-1, -2, -3, -4, -5, -6, -7, -8, -9};
    std::vector<double> positiveVec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<double> vecOfZeros{0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<double> doubleNegativeVec{-2, -4, -6, -8, -10, -12, -14, -16, -18};
    std::vector<double> doublePositiveVec{2, 4, 6, 8, 10, 12, 14, 16, 18};
    std::vector<double> sumAVecTest{20, 20, 5, 5, 1, 1}; // 52
    std::vector<double> sumBVecTest{20, 20, 0, 2, 0, 0}; // 42

    /**
     * vectors for multiplication
     */
    std::vector<double> multiATest{12, 14, 2, -7, 15, 1, 0, 4, 6, 2, 4, 5, 5, 2, 90}; // 3X5
    std::vector<double> multiBTest{44, -2, 3, 4, 6, 8, 9, 0, 25, 3}; //5X2
    std::vector<double> expectedVec{894, 93, 172, 36, 2489, 322}; // 3X2


    std::vector<double> multiCTest{2, -14, -12, 1, 6, 4}; //2X3
    std::vector<double> multiDTest{-19, -2, 9, 4, 6, 76}; //3X2
    std::vector<double> expectedVec2{-236, -972, 59, 326}; //2X2



    std::vector<double> multiETest{2, 4, -5, 12, 4, 14, 0}; //1X7
    std::vector<double> multiFTest{0, 9, 6, 4, 7, 0, 9, 5, 8, 9, -4, -3, -2, -4}; //7X2
    std::vector<double> expectedVec3{73, 88}; //2X2





    /**
     * init all matrices
     */
    Matrix positiveMat{positiveVec, 3, 3};
    Matrix negativeMat{negativeVec, 3, 3};
    Matrix matOfZeros{vecOfZeros, 3, 3};
    Matrix regularMat{vec, 5, 3};
    Matrix doubleNegativeMat{doubleNegativeVec, 3, 3};
    Matrix doublePositiveMat{doublePositiveVec, 3, 3};
    Matrix sumAMat{sumAVecTest, 2, 3};
    Matrix sumBMat{sumBVecTest, 2, 3};

    /**
     * matrices for multiplication
     */
    Matrix multiAMat{multiATest, 3, 5};
    Matrix multiBMat{multiBTest, 5, 2};
    Matrix expectedMat{expectedVec, 3, 2};

    Matrix multiCMat{multiCTest, 2, 3};
    Matrix multiDMat{multiDTest, 3, 2};
    Matrix expectedMat2{expectedVec2, 2, 2};

    Matrix multiEMat{multiETest, 1, 7};
    Matrix multiFMat{multiFTest, 7, 2};
    Matrix expectedMat3{expectedVec3, 1, 2};


    std::stringstream ss;

    /**
     * Test the operators : + , += , - , -=
     */
            SUBCASE("operator -> +") {
                CHECK_EQ(positiveMat + negativeMat, matOfZeros);
                CHECK_EQ(negativeMat + positiveMat, matOfZeros);
    }

            SUBCASE ("operator -> +=") {
        positiveMat += negativeMat;
                CHECK_EQ(positiveMat, matOfZeros);
        negativeMat += matOfZeros;
                CHECK_EQ(negativeMat, negativeMat);
    }

            SUBCASE("operator -> -") {
                CHECK_EQ(negativeMat - positiveMat, doubleNegativeMat);
                CHECK_EQ(positiveMat - positiveMat, matOfZeros);
    }
            SUBCASE("operator -> -=") {
        negativeMat -= negativeMat;
                CHECK_EQ(negativeMat, matOfZeros);
        positiveMat -= -(positiveMat);
                CHECK_EQ(positiveMat, doublePositiveMat);
    }

    /**
     * Test the compare operators : ==, != , < , <= , > , >=
     */

            SUBCASE("operator -> ==") {
                CHECK(bool (positiveMat +negativeMat == matOfZeros));

    }
            SUBCASE("operator -> !=") {
                CHECK(bool (sumAMat != sumBMat));
    }
            SUBCASE("operator -> <=") {
                CHECK(bool (sumBMat <= sumAMat));
    }
            SUBCASE("operator -> <") {
                CHECK(bool (sumBMat<sumAMat));
    }
            SUBCASE("operator -> >") {
                CHECK(bool (sumAMat >sumBMat));
    }
            SUBCASE("operator -> >=") {
                CHECK(bool (sumAMat >=sumBMat));
    }


    /**
     * Test the string output
     */

            SUBCASE("Test Cout") {
        ss << regularMat;
                CHECK_EQ(ss.str(), "[2 4.3 5]\n[2 3 1.7]\n[4.1 2.5 0]\n[19 4 4]\n[4 4 4]\n");
        ss.str("");
        ss << negativeMat;
                CHECK(ss.str() == "[-1 -2 -3]\n[-4 -5 -6]\n[-7 -8 -9]\n");
        ss.str("");
        ss << matOfZeros;
                CHECK(ss.str() == "[0 0 0]\n[0 0 0]\n[0 0 0]\n");
        ss.str("");
        ss << -matOfZeros;
                CHECK(ss.str() == "[0 0 0]\n[0 0 0]\n[0 0 0]\n");

    }

    /**
     * Test prefix increment and postfix increment
     */

            SUBCASE("prefix test") {
        Matrix expected(std::vector<double>{1, 1, 1, 1, 1, 1, 1, 1, 1}, 3, 3);
                CHECK_EQ(++matOfZeros, expected);
        Matrix expectedRegular(std::vector<double>{3, 5.3, 6.0, 3, 4, 2.7, 5.1, 3.5, 1, 20, 5, 5, 5, 5, 5}, 5, 3);
                CHECK_EQ(++regularMat, expectedRegular);
    }
            SUBCASE("postfix test") {
                CHECK(matOfZeros-- != matOfZeros);
    }

    /**
   * Test the compare operators : *, *= (matrices and scalar as well)
   */
            SUBCASE("operator -> scalar * Matrix") {
                CHECK_EQ(-2 * negativeMat, doublePositiveMat);
                CHECK_EQ(2 * negativeMat, doubleNegativeMat);
                CHECK_EQ(5 * matOfZeros, matOfZeros);
                CHECK_EQ(0 * negativeMat, matOfZeros);
    }
            SUBCASE("operator -> Matrix *= scalar") {
                CHECK_EQ(-2 * negativeMat, doublePositiveMat);
                CHECK_EQ(2 * negativeMat, doubleNegativeMat);
                CHECK_EQ(5 * matOfZeros, matOfZeros);
                CHECK_EQ(0 * negativeMat, matOfZeros);
    }
            SUBCASE("operator -> Matrix * Matrix") {
                CHECK_EQ(multiAMat * multiBMat, expectedMat);
                CHECK_EQ(multiCMat * multiDMat, expectedMat2);
                CHECK_EQ(multiEMat * multiFMat, expectedMat3);
    }

            SUBCASE("operator -> Matrix *= Matrix") {
        multiAMat *= multiBMat;
        multiCMat *= multiDMat;
        multiEMat *= multiFMat;
                CHECK_EQ(multiAMat, expectedMat);
                CHECK_EQ(multiCMat, expectedMat2);
                CHECK_EQ(multiEMat, expectedMat3);
    }

}



