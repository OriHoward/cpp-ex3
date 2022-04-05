#include "Matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>

//todo change size type to unsign int
//todo add deep copy to cpp and test
//todo add subcases
//todo test postfix and prefix and * and *=

namespace zich {
    // change constructor later
    Matrix::Matrix(const std::vector<double> &vec, int row, int col)
            : mat(vec), row(row), col(col) { checkInput(vec.size(), row, col); }


    void Matrix::checkInput(unsigned int matSize, int row, int col) {
        if (row * col != matSize || row < 1 || col < 1) {
            throw std::invalid_argument("row and col must be positive and row*col must be equal to size of vector");
        }
    }

    void Matrix::isMultiDefined(const Matrix &other) const {
        if (this->col != other.row) {
            throw std::invalid_argument("The two matrices are not multi defined");
        }
    }

    void Matrix::checkSameDimension(const Matrix &other) const {
        if (this->row != other.row || this->col != other.col) {
            throw std::invalid_argument("both matrices must be in the same dimension");
        }
    }


    Matrix Matrix::operator-() const {
        Matrix minusMat(this->mat, this->row, this->col);
        for (std::string::size_type i = 0; i < minusMat.mat.size(); ++i) {
            if (minusMat.mat[i] != 0) {
                minusMat.mat[i] *= -1;
            }
        }
        return minusMat;
    }

    Matrix Matrix::operator+() const {
        Matrix plusMat(this->mat, this->row, this->col);
        for (std::string::size_type i = 0; i < plusMat.mat.size(); ++i) {
            plusMat.mat[i] *= -1;
        }
        return plusMat;
    }


    Matrix Matrix::operator+(const Matrix &other) const {
        this->checkSameDimension(other);
        Matrix newMat(this->mat, this->row, this->col);
        for (std::string::size_type i = 0; i < newMat.mat.size(); ++i) {
            newMat.mat[i] += other.mat[i];
        }
        return newMat;
    }

    Matrix &Matrix::operator+=(const Matrix &other) {
        this->checkSameDimension(other);
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            this->mat[i] += other.mat[i];
        }
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &other) const {
        this->checkSameDimension(other);
        Matrix newMat(this->mat, this->row, this->col);
        for (std::string::size_type i = 0; i < newMat.mat.size(); ++i) {
            newMat.mat[i] -= other.mat[i];
        }
        return newMat;
    }

    Matrix &Matrix::operator-=(const Matrix &other) {
        this->checkSameDimension(other);
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            this->mat[i] -= other.mat[i];
        }
        return *this;
    }

    Matrix Matrix::operator*(const Matrix &other) const {
        this->isMultiDefined(other);
//        std::vector<double> newVec;
//        int newMatSize = this->row * other.col;
////        newVec.reserve(newMatSize);
//        Matrix newMat(newVec, this->row, other.col);
//
//        return newMat;
        return *this;

    }

    Matrix &Matrix::operator*=(const Matrix &other) {
        this->isMultiDefined(other);
        return *this;
    }

    Matrix &Matrix::operator*=(const double scalar) { return *this; }

//prefix increment takes no arguments:
    Matrix &Matrix::operator++() {
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            this->mat[i]++;
        }
        return *this;
    }

    Matrix &Matrix::operator--() {
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            this->mat[i]--;
        }
        return *this;
    }

//postfix increment:
    Matrix Matrix::operator++(int dummy_flag_for_postfix_increment) {
        Matrix matCopy(this->mat, this->row, this->col);
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            this->mat[i]++;
        }
        return matCopy;
    }

    Matrix Matrix::operator--(int dummy_flag_for_postfix_increment) {
        Matrix matCopy(this->mat, this->row, this->col);
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            this->mat[i]--;
        }
        return matCopy;
    }

    bool Matrix::operator!=(const Matrix &other) const {
        this->checkSameDimension(other);
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            if (this->mat[i] != other.mat[i]) {
                return true;
            }
        }
        return false;
    }

    bool Matrix::operator==(const Matrix &other) const {
        this->checkSameDimension(other);
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            if (this->mat[i] != other.mat[i]) {
                return false;
            }
        }
        return true;
    }

    bool Matrix::operator>(const Matrix &other) const {
        this->checkSameDimension(other);
        double sumOfA = 0;
        double sumOfB = 0;
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            sumOfA += this->mat[i];
            sumOfB += other.mat[i];
        }
        return sumOfA > sumOfB;
    }

    bool Matrix::operator>=(const Matrix &other) const {
        this->checkSameDimension(other);
        double sumOfA = 0;
        double sumOfB = 0;
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            sumOfA += this->mat[i];
            sumOfB += other.mat[i];
        }
        return sumOfA >= sumOfB;
    }

    bool Matrix::operator<(const Matrix &other) const {
        this->checkSameDimension(other);
        double sumOfA = 0;
        double sumOfB = 0;
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            sumOfA += this->mat[i];
            sumOfB += other.mat[i];
        }
        return sumOfA < sumOfB;
    }

    bool Matrix::operator<=(const Matrix &other) const {
        this->checkSameDimension(other);
        double sumOfA = 0;
        double sumOfB = 0;
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            sumOfA += this->mat[i];
            sumOfB += other.mat[i];
        }
        return sumOfA <= sumOfB;
    }

    Matrix operator*(const double scalar, const Matrix &m) {
        Matrix newMat(m.mat, m.row, m.col);
        for (std::string::size_type i = 0; i < newMat.mat.size(); ++i) {
            newMat.mat[i] *= scalar;
        }
        return newMat;
    }


    std::ostream &operator<<(std::ostream &output, const Matrix &m) {
        int currCol = 1;
        std::string::size_type index = 0;
        while (index < m.mat.size()) {
            output << "[" << m.mat[index++];
            while (currCol < m.col) {
                output << " " << m.mat[index++];
                currCol++;
            }
            output << "]";
            if (index < m.mat.size()) {
                output << "\n";
            }
            currCol = 1;
        }
        return output;
    }

    std::istream &operator>>(std::istream &input, Matrix &m) { return input; }

}