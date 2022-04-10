#ifndef CPP___EX3_MATRIX_HPP
#define CPP___EX3_MATRIX_HPP

#include <vector>
#include <iostream>
#include <stdexcept>

namespace zich {
    class Matrix {
    private:
        std::vector<double> mat;
        int row, col;

    public:

        static void checkInput(unsigned int matSize, int row, int col);

        void checkSameDimension(const Matrix &other) const;

        void isMultiDefined(const Matrix &other) const;

        static double calculateSumOfMat(const Matrix &m);

        bool isEqual(const Matrix &m1, const Matrix &m2) const;

        static void addRow(std::vector<double> &, const std::string &currRow);

        static unsigned int getCols(const std::string &currRow);

        static void checkValidRow(const std::string &currRow);

        static void checkValidCol(const unsigned int expectedCol, const std::string &currRow);

        //Unary minus
        Matrix operator-() const;

        Matrix operator+() const;


        Matrix(const std::vector<double> &vec, int row, int col);


        Matrix operator+(const Matrix &other) const;

        Matrix &operator+=(const Matrix &other);

        Matrix operator-(const Matrix &other) const;

        Matrix &operator-=(const Matrix &other);

        Matrix operator*(const Matrix &other) const;

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


        friend Matrix operator*(const double scalar, const Matrix &m);

    };
}
#endif
