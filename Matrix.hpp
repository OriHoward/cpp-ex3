#include <vector>
#include <iostream>
#include <stdexcept>

#ifndef CPP___EX3_MATRIX_HPP
#define CPP___EX3_MATRIX_HPP

namespace zich {
    class Matrix {
    private:
        int row, col;
        std::vector<double> vec;

    public:

        static void checkInput(std::vector<double> &vec, int row, int col);


        void checkSameDimension(const Matrix &other) const;


        void isMultiDefined(const Matrix &other) const;

        //Unary minus
        Matrix operator-() const;

        Matrix operator+() const;


        Matrix(std::vector<double> &vec, int row, int col);

        ~Matrix();

        Matrix operator+(const Matrix &other);

        Matrix &operator+=(const Matrix &other);

        Matrix operator-(const Matrix &other);

        Matrix &operator-=(const Matrix &other);

        Matrix operator*(const Matrix &other);

        Matrix &operator*=(const Matrix &other);

        Matrix &operator*=(double scalar);

        //prefix increment takes no arguments:
        Matrix &operator++();

        Matrix &operator--();

        //postfix increment:
        Matrix operator++(int dummy_flag_for_postfix_increment);

        Matrix operator--(int dummy_flag_for_postfix_increment);

        bool operator!=(const Matrix &other) const;

        bool operator==(const Matrix &other) const;

        bool operator>(const Matrix &other) const;

        bool operator>=(const Matrix &other) const;

        bool operator<(const Matrix &other) const;

        bool operator<=(const Matrix &other) const;

        friend std::ostream &operator<<(std::ostream &output, const Matrix &m);

        friend std::istream &operator>>(std::istream &input, Matrix &m);

        friend bool operator*(int, const Matrix &m);

    };

}
#endif
