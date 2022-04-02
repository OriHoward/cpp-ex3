#include "Matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

namespace zich {

    Matrix::Matrix(std::vector<double>, int, int) {}

    Matrix::~Matrix() {}


    Matrix Matrix::operator-() const { return *this; }

    Matrix Matrix::operator+() const { return *this; }


    Matrix Matrix::operator+(const Matrix &other) { return *this; }

    Matrix &Matrix::operator+=(const Matrix &other) { return *this; }

    Matrix Matrix::operator-(const Matrix &other) { return *this; }

    Matrix &Matrix::operator-=(const Matrix &other) { return *this; }


    Matrix &Matrix::operator*=(const Matrix &other) { return *this; }

    Matrix &Matrix::operator*=(double scalar) { return *this; }

//prefix increment takes no arguments:
    Matrix &Matrix::operator++() { return *this; }

    Matrix &Matrix::operator--() { return *this; }

//postfix increment:
    Matrix Matrix::operator++(int dummy_flag_for_postfix_increment) { return *this; }

    Matrix Matrix::operator--(int dummy_flag_for_postfix_increment) { return *this; }

    bool operator!=(const Matrix &m1, const Matrix &m2) { return false; }

    bool operator==(const Matrix &m1, const Matrix &m2) { return false; }

    bool operator>(const Matrix &m1, const Matrix &m2) { return false; }

    bool operator>=(const Matrix &m1, const Matrix &m2) { return false; }

    bool operator<(const Matrix &m1, const Matrix &m2) { return false; }

    bool operator<=(const Matrix &m1, const Matrix &m2) { return false; }

    bool operator*(int scalar, const Matrix &m) { return true; }


    std::ostream &operator<<(std::ostream &output, const Matrix &m) { return output << ""; }

    std::istream &operator>>(std::istream &input, Matrix &m) { return input; }


}