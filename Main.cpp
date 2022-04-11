////#include "sources/Matrix.hpp"
//#include <string>
//
//double fRand(double fMin, double fMax) {
//    double f = (double) rand() / RAND_MAX;
//    return fMin + f * (fMax - fMin);
//}
//
//void generateRandomVector(std::vector<double> &randomVec) {
//    srand(time(nullptr));
//    for (double &i: randomVec) {
//        i = fRand(-300, 300);
//    }
//}
//
//using namespace zich;
//
//int main() {
//    /**
//     * generates and prints a random matrix
//     */
//    std::cout << ">>>>Random matrices<<<<\n\n";
//    std::vector<double> vec(30);
//    srand(time(NULL));
//    int row, col;
//    int modulo = 5;
//    for (int i = 0; i < 3; ++i) {
//        generateRandomVector(vec);
//        row = modulo;
//        col = 30 / modulo;
//        modulo += 5;
//        std::cout << Matrix({vec, row, col}) << "\n\n";
//    }
//
//    /**
//     * common matrices
//     */
//    std::cout << ">>>>>>>>>>   Common matrices   <<<<<<<<<<\n\n\n";
//    std::vector<double> vecOfZeros{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//    std::vector<double> identityVec{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
//    std::vector<double> diagonalVec{1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4};
//    std::vector<double> symmetricVec{1, 7, 3, 4, 7, 4, 5, 9, 3, 5, 0, -2, 4, 9, -2, 14};
//    std::vector<double> basicVec{1, 2, 3, 4};
//
//    Matrix matOfZeros{vecOfZeros, 4, 4};
//    Matrix identityMat{identityVec, 4, 4};
//    Matrix diagonalMat{diagonalVec, 4, 4};
//    Matrix symmetricMat{symmetricVec, 4, 4};
//    Matrix basicMat{basicVec, 2, 2};
//    std::cout << ">>>Zero matrix<<<\n\n";
//    std::cout << matOfZeros << "\n\n";
//    std::cout << ">>>Identity matrix<<<\n\n";
//    std::cout << identityMat << "\n\n";
//    std::cout << ">>>Diagonal matrix<<<\n\n";
//    std::cout << diagonalMat << "\n\n";
//    std::cout << ">>>Symmetric matrix<<<\n\n";
//    std::cout << symmetricMat << "\n\n";
//
//    /**
//     * Operator on matrices
//     */
//
//    std::cout << ">>>>>>>>>>   Basic operators   <<<<<<<<<<\n\n\n";
//    std::cout << "Identity matrix" << " * " << "Diagonal matrix:\n";
//    std::cout << identityMat * diagonalMat << "\n\n";
//    std::cout << "Symmetric matrix" << " - " << "Identity matrix:\n";
//    std::cout << symmetricMat - identityMat << "\n\n";
//    std::cout << "Symmetric matrix" << " + " << "Zero matrix:\n";
//    std::cout << symmetricMat + matOfZeros << "\n\n";
//    std::cout << "++Symmetric matrix\n";
//    std::cout << ++symmetricMat << "\n\n";
//
//    std::cout << "Please enter a matrix as following: [x1 y1 z1], [x2 y2 z2], [x3 y3 z3] .. etc\n";
//    std::cin >> basicMat;
//    std::cout << "\nHere is your matrix sir:\n";
//    std::cout << basicMat;
//
//    return 0;
//}