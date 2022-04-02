#include "Matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

namespace zich {

    Matrix::Matrix(std::vector<double> &vec, int row, int col) {
        checkInput(vec, row, col);
        this->vec = vec;
        this->row = row;
        this->col = col;
    }

    Matrix::~Matrix() {}

    void Matrix::checkInput(std::vector<double> &vec, int row, int col) {
        if (row * col != vec.size() || row < 1 || col < 1) {
            throw std::invalid_argument("row and col must be positive and row*col must be equal to size of vector");
        }
    }

    void Matrix::checkMatSize(int matSize, int row, int col) {
    }

    void Matrix::checkSameDimension(const Matrix &other) const {
        if (this->row != other.row || this->col != other.col) {
            throw std::invalid_argument("both matrices must be in the same dimension");
        }
    }

    void Matrix::checkSameDimension(const Matrix &m1, const Matrix &m2) {
        if (m1.row != m2.row || m1.col != m2.col) {
            throw std::invalid_argument("both matrices must be in the same dimension");
        }
    }


    Matrix Matrix::operator-() const { return *this; }

    Matrix Matrix::operator+() const { return *this; }


    Matrix Matrix::operator+(const Matrix &other) {
        this->checkSameDimension(other);
        return *this;
    }

    Matrix &Matrix::operator+=(const Matrix &other) {
        this->checkSameDimension(other);
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &other) {
        this->checkSameDimension(other);
        return *this;
    }

    Matrix &Matrix::operator-=(const Matrix &other) {
        this->checkSameDimension(other);
        return *this;
    }

    Matrix Matrix::operator*(const Matrix &other) { return *this; }

    Matrix &Matrix::operator*=(const Matrix &other) { return *this; }

    Matrix &Matrix::operator*=(double scalar) { return *this; }

//prefix increment takes no arguments:
    Matrix &Matrix::operator++() { return *this; }

    Matrix &Matrix::operator--() { return *this; }

//postfix increment:
    Matrix Matrix::operator++(int dummy_flag_for_postfix_increment) { return *this; }

    Matrix Matrix::operator--(int dummy_flag_for_postfix_increment) { return *this; }

    bool operator!=(const Matrix &m1, const Matrix &m2) {
        Matrix::checkSameDimension(m1, m2);
        return false;
    }

    bool operator==(const Matrix &m1, const Matrix &m2) {
        Matrix::checkSameDimension(m1, m2);
        return false;
    }

    bool operator>(const Matrix &m1, const Matrix &m2) {
        Matrix::checkSameDimension(m1, m2);
        return false;
    }

    bool operator>=(const Matrix &m1, const Matrix &m2) {
        Matrix::checkSameDimension(m1, m2);
        return false;
    }

    bool operator<(const Matrix &m1, const Matrix &m2) {
        Matrix::checkSameDimension(m1, m2);
        return false;
    }

    bool operator<=(const Matrix &m1, const Matrix &m2) {
        Matrix::checkSameDimension(m1, m2);
        return false;
    }

    // not sure :
    bool operator*(int scalar, const Matrix &m) { return true; }


    std::ostream &operator<<(std::ostream &output, const Matrix &m) { return output << ""; }

    std::istream &operator>>(std::istream &input, Matrix &m) { return input; }


}