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

    void Matrix::isMultiDefined(const Matrix &other) {
        if (this->col != other.row) {
            throw std::invalid_argument("The two matrices are not multi defined");
        }
    }

    void Matrix::checkSameDimension(const Matrix &other) const {
        if (this->row != other.row || this->col != other.col) {
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

    Matrix Matrix::operator*(const Matrix &other) {
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
        Matrix::checkSameDimension(other);
        return false;
    }

    bool Matrix::operator==(const Matrix &other) const {
        Matrix::checkSameDimension(other);
        return false;
    }

    bool Matrix::operator>(const Matrix &other) const {
        Matrix::checkSameDimension(other);
        return false;
    }

    bool Matrix::operator>=(const Matrix &other) const {
        Matrix::checkSameDimension(other);
        return false;
    }

    bool Matrix::operator<(const Matrix &other) const {
        Matrix::checkSameDimension(other);
        return false;
    }

    bool Matrix::operator<=(const Matrix &other) const {
        Matrix::checkSameDimension(other);
        return false;
    }

    // not sure :
    bool operator*(int scalar, const Matrix &m) {
        return true;
    }


    std::ostream &operator<<(std::ostream &output, const Matrix &m) { return output << ""; }

    std::istream &operator>>(std::istream &input, Matrix &m) { return input; }


}