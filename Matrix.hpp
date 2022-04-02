#include <vector>
#include <iostream>
#include <stdexcept>

#ifndef CPP___EX3_MATRIX_HPP
#define CPP___EX3_MATRIX_HPP

namespace zich {
    class Matrix {
    private:

    public:
        //Unary minus
        Matrix operator-() const;

        Matrix operator+() const;


        Matrix(std::vector<double>&, int, int);

        ~Matrix();

        Matrix operator+(const Matrix &other);

        Matrix &operator+=(const Matrix &other);

        Matrix operator-(const Matrix &other);

        Matrix &operator-=(const Matrix &other);

//        Matrix operator*(const Matrix &other);
//
//        Matrix operator*(int, const Matrix &m);
//
//        Matrix operator*(int scalar);
//
//        Matrix operator*(const Matrix &m, int scalar);

        Matrix &operator*=(const Matrix &other);

        Matrix &operator*=(double scalar);

        //prefix increment takes no arguments:
        Matrix &operator++();

        Matrix &operator--();

        //postfix increment:
        Matrix operator++(int dummy_flag_for_postfix_increment);

        Matrix operator--(int dummy_flag_for_postfix_increment);

        friend bool operator!=(const Matrix &m1, const Matrix &m2);

        friend bool operator==(const Matrix &m1, const Matrix &m2);

        friend bool operator>(const Matrix &m1, const Matrix &m2);

        friend bool operator>=(const Matrix &m1, const Matrix &m2);

        friend bool operator<(const Matrix &m1, const Matrix &m2);

        friend bool operator<=(const Matrix &m1, const Matrix &m2);

        friend std::ostream &operator<<(std::ostream &output, const Matrix &m);

        friend std::istream &operator>>(std::istream &input, Matrix &m);

        friend bool operator*(int, const Matrix &m);

    };


}
#endif
