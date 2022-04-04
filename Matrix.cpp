#include "Matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <iomanip>

namespace zich {

    Matrix::Matrix(std::vector<double> &vec, int row, int col) {
        checkInput(vec.size(), row, col);
        this->mat = vec;
        this->row = row;
        this->col = col;
    }


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

    std::string Matrix::toString() const {
        std::string strMat;
        int currCol = 1;
        std::string::size_type index = 0;
        while (index < this->mat.size()) {
            strMat += "[";
            strMat += std::to_string(this->mat[index++]).substr(0, 4);
            while (currCol < this->col) {
                strMat += " " + std::to_string(this->mat[index++]).substr(0, 4);
                currCol++;
            }
            strMat += "]";
            if (index < this->mat.size()) {
                strMat += "\n";
            }
            currCol = 1;
        }
        return strMat;
    }


    Matrix Matrix::operator-() { // check about the const
        for (std::string::size_type i = 0; i < this->mat.size(); ++i) {
            this->mat[i] *= -1;
        }
        return *this;
    }

    Matrix Matrix::operator+() { return *this; }


    Matrix Matrix::operator+(const Matrix &other) const {
        this->checkSameDimension(other);
        std::vector<double> newVec;
        newVec.reserve(other.mat.size());
        Matrix newMat(newVec, this->row, this->col);
        for (std::string::size_type i = 0; i < row * col; ++i) {
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
        return *this;
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
        return *this;
    }

    Matrix &Matrix::operator*=(const Matrix &other) {
        this->isMultiDefined(other);
        return *this;
    }

    Matrix &Matrix::operator*=(double scalar) { return *this; }

//prefix increment takes no arguments:
    Matrix &Matrix::operator++() { return *this; }

    Matrix &Matrix::operator--() { return *this; }

//postfix increment:
    Matrix Matrix::operator++(int dummy_flag_for_postfix_increment) { return *this; }

    Matrix Matrix::operator--(int dummy_flag_for_postfix_increment) { return *this; }

    bool Matrix::operator!=(const Matrix &other) const {
        this->checkSameDimension(other);
        return false;
    }

    bool Matrix::operator==(const Matrix &other) const {
        this->checkSameDimension(other);
        return false;
    }

    bool Matrix::operator>(const Matrix &other) const {
        this->checkSameDimension(other);
        return false;
    }

    bool Matrix::operator>=(const Matrix &other) const {
        this->checkSameDimension(other);
        return false;
    }

    bool Matrix::operator<(const Matrix &other) const {
        this->checkSameDimension(other);
        return false;
    }

    bool Matrix::operator<=(const Matrix &other) const {
        this->checkSameDimension(other);
        return false;
    }

    // not sure :
    bool operator*(int scalar, const Matrix &m) {
        return true;
    }


    std::ostream &operator<<(std::ostream &output, const Matrix &m) {
        output << m.toString();
        return output;
    }

    std::istream &operator>>(std::istream &input, Matrix &m) { return input; }


}