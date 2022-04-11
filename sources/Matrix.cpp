#include "Matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <regex>

namespace zich {
    /**
     * The constructor
     * @param vec
     * @param row
     * @param col
     */
    Matrix::Matrix(const std::vector<double> &vec, int row, int col)
            : mat(vec), row(row), col(col) {
        checkInput(vec.size(), row, col);
    }

    /**
     * Checks if the input is valid
     * Throws otherwise
     * @param matSize
     * @param row
     * @param col
     */
    void Matrix::checkInput(unsigned int matSize, int row, int col) {
        if (row * col != matSize || row < 1 || col < 1) {
            throw std::invalid_argument("row and col must be positive and row*col must be equal to size of vector");
        }
    }

    /**
     * Checks if 2 matrices can be multiplied with each other.
     * Throws otherwise
     * @param other
     */
    void Matrix::isMultiDefined(const Matrix &other) const {
        if (this->col != other.row) {
            throw std::invalid_argument("The two matrices are not multi defined");
        }
    }

    /**
     * Checks if 2 matrices has the same dimension
     * Throws otherwise
     * @param other
     */
    void Matrix::checkSameDimension(const Matrix &other) const {
        if (this->row != other.row || this->col != other.col) {
            throw std::invalid_argument("both matrices must be in the same dimension");
        }
    }

    /**
     * Calculates the sum of all the numbers in the matrix
     * @param m
     * @return Total sum
     */
    double Matrix::calculateSumOfMat(const Matrix &m) {
        double sum = 0;
        for (unsigned int i = 0; i < m.mat.size(); ++i) {
            sum += m.mat[i];
        }
        return sum;
    }

    /**
     * Checks if all the numbers in the matrix are identical
     * @param m1
     * @param m2
     * @return
     */
    bool Matrix::isEqual(const Matrix &m1, const Matrix &m2) {
        for (unsigned int i = 0; i < m1.mat.size(); ++i) {
            if (m1.mat[i] != m2.mat[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * Overloads operator (-): Changes the matrix sign
     * @return
     */
    Matrix Matrix::operator-() const {
        Matrix minusMat{this->mat, this->row, this->col};
        for (unsigned int i = 0; i < minusMat.mat.size(); ++i) {
            if (minusMat.mat[i] != 0) {
                minusMat.mat[i] *= -1;
            }
        }
        return minusMat;
    }

    /**
     * Overloads operator (+):Returns a copy of the matrix
     * @return
     */
    Matrix Matrix::operator+() const {
        Matrix plusMat{this->mat, this->row, this->col};
        return plusMat;
    }

    /**
     * Overloads operator (+): Add 2 matrices together and returns a copy of the new matrix.
     * @param other
     * @return
     */
    Matrix Matrix::operator+(const Matrix &other) const {
        this->checkSameDimension(other);
        Matrix newMat{this->mat, this->row, this->col};
        for (unsigned int i = 0; i < newMat.mat.size(); ++i) {
            newMat.mat[i] += other.mat[i];
        }
        return newMat;
    }

    /**
     * Overloads operator (+=): Add other matrix to the current matrix and returns the current mat with the new values.
     * @param other
     * @return
     */
    Matrix &Matrix::operator+=(const Matrix &other) {
        this->checkSameDimension(other);
        *this = *this + other;
        return *this;
    }

    /**
     * Overloads operator (-): Subtract 2 matrices together and returns a copy of the new matrix.
     * @param other
     * @return
     */

    Matrix Matrix::operator-(const Matrix &other) const {
        this->checkSameDimension(other);
        Matrix newMat{this->mat, this->row, this->col};
        for (unsigned int i = 0; i < newMat.mat.size(); ++i) {
            newMat.mat[i] -= other.mat[i];
        }
        return newMat;
    }

    /**
     * Overloads operator (-=): Subtract other matrix from the current matrix and returns the current mat with the new values.
     * @param other
     * @return
     */
    Matrix &Matrix::operator-=(const Matrix &other) {
        this->checkSameDimension(other);
        *this = *this - other;
        return *this;
    }

    /**
     * Overloads operator (*): Multiple 2 matrices and returns a copy of the new matrix.
     * @param other
     * @return
     */
    Matrix Matrix::operator*(const Matrix &other) const {
        this->isMultiDefined(other);
        unsigned int currRunner = 0; // The index which always moves accordingly between the 2 matrices
        unsigned int matIndex = 0; // the index for inserting the result to the newMat
        double currSum = 0; // The current sum which is calculated every iteration
        unsigned int colRunner = 0; // index runner for the cols in other.mat
        unsigned int jump = static_cast<unsigned int>(other.col); // the step we need to skip to get to the next row.
        unsigned int newSize = static_cast <unsigned int>(this->row * other.col); // the new size of the mat
        std::vector<double> newVec(newSize, 0);
        Matrix newMat{newVec, this->row, other.col};
        for (unsigned int i = 0; i < this->mat.size(); i += static_cast<unsigned int>(this->col)) {
            colRunner = 0;
            for (unsigned int currCol = 0; currCol < other.mat.size(); ++currCol) {
                currSum += this->mat[currRunner + i] * other.mat[colRunner + currRunner * jump];
                currRunner++;
                if (currRunner == this->col) {
                    colRunner++;
                    newMat.mat[matIndex++] = currSum;
                    currRunner = 0;
                    currSum = 0;
                }
            }
        }
        return newMat;
    }

    /**
     * Overloads operator (*=): Multiple other matrix with the current matrix and returns the current mat with the new values.
     * @param other
     * @return
     */
    Matrix &Matrix::operator*=(const Matrix &other) {
        this->isMultiDefined(other);
        *this = *this * other;
        return *this;
    }

    /**
     * Overloads operator (*=) with scalar: Multiple the current matrix with scalar and returns the current mat with the new values.
     * @param scalar
     * @return
     */
    Matrix &Matrix::operator*=(const double scalar) {
        for (unsigned int i = 0; i < this->mat.size(); ++i) {
            this->mat[i] *= scalar;
        }
        return *this;
    }

    /**
     * Overloads operator (++) prefix increment
     * @return
     */
    Matrix &Matrix::operator++() {
        for (unsigned int i = 0; i < this->mat.size(); ++i) {
            this->mat[i]++;
        }
        return *this;
    }

    /**
     * Overloads operator (--) prefix increment
     * @return
     */
    Matrix &Matrix::operator--() {
        for (unsigned int i = 0; i < this->mat.size(); ++i) {
            this->mat[i]--;
        }
        return *this;
    }

    /**
     * Overloads operator (++) with dummy int - postfix increment
     * @return
     */
    Matrix Matrix::operator++(int) {
        Matrix matCopy{this->mat, this->row, this->col};
        ++*this;
        return matCopy;
    }

    /**
     * Overloads operator (--) with dummy int - postfix increment
     * @return
     */
    Matrix Matrix::operator--(int) {
        Matrix matCopy{this->mat, this->row, this->col};
        --*this;
        return matCopy;
    }

    /**
     * Overloads operator (!=): Compare between 2 matrices.
     * Returns true if the 2 matrices have at least one different value.
     * @param other
     * @return
     */
    bool Matrix::operator!=(const Matrix &other) const {
        this->checkSameDimension(other);
        return !this->isEqual(*this, other);
    }

    /**
     * Overloads operator (==): Compare between 2 matrices.
     * Returns true if the 2 matrices are identical.
     * @param other
     * @return
     */
    bool Matrix::operator==(const Matrix &other) const {
        this->checkSameDimension(other);
        return this->isEqual(*this, other);
    }

    /**
     * Overloads operator (>): Compare between 2 matrices.
     * Return true if the sum of all the values in the current matrix are greater than the sum of all the values in the other mat.
     * @param other
     * @return
     */
    bool Matrix::operator>(const Matrix &other) const {
        this->checkSameDimension(other);
        return this->calculateSumOfMat(*this) > this->calculateSumOfMat(other);
    }

    /**
     * Overloads operator (>=): Compare between 2 matrices.
     * Return true if the sum of all the values in the current matrix are greater than the sum of all the values in the other mat.
     * OR
     * Return true if the 2 matrices are identical
     * @param other
     * @return
     */
    bool Matrix::operator>=(const Matrix &other) const {
        this->checkSameDimension(other);
        return this->calculateSumOfMat(*this) > this->calculateSumOfMat(other) || *this == other;
    }

    /**
     * Overloads operator (<): Compare between 2 matrices.
     * Return true if the sum of all the values in the current matrix are less than the sum of all the values in the other mat.
     * @param other
     * @return
     */
    bool Matrix::operator<(const Matrix &other) const {
        this->checkSameDimension(other);
        return this->calculateSumOfMat(*this) < this->calculateSumOfMat(other);
    }

    /**
     * Overloads operator (<=): Compare between 2 matrices.
     * Return true if the sum of all the values in the current matrix are less than the sum of all the values in the other mat.
     * OR
     * Return true if the 2 matrices are identical
     * @param other
     * @return
     */
    bool Matrix::operator<=(const Matrix &other) const {
        this->checkSameDimension(other);
        return this->calculateSumOfMat(*this) < this->calculateSumOfMat(other) || *this == other;
    }

    /**
     * Overloads operator (*) with scalar: Multiple the matrix with scalar and returns a copy of the new mat.
     * @param scalar
     * @param m
     * @return
     */
    Matrix operator*(const double scalar, const Matrix &m) {
        Matrix newMat{m.mat, m.row, m.col};
        for (unsigned int i = 0; i < newMat.mat.size(); ++i) {
            newMat.mat[i] *= scalar;
        }
        return newMat;
    }

    /**
     * Overloads operator (ostream): Basically a ToString function for the matrix.
     * @param output
     * @param m
     * @return
     */
    std::ostream &operator<<(std::ostream &output, const Matrix &m) {
        int currCol = 1;
        unsigned int index = 0;
        double toPrint = 0;
        while (index < m.mat.size()) {
            toPrint = m.mat[index] == 0 ? 0 : m.mat[index];
            output << "[" << toPrint;
            index++;
            while (currCol < m.col) {
                toPrint = m.mat[index] == 0 ? 0 : m.mat[index];
                output << " " << toPrint;
                index++;
                currCol++;
            }
            output << "]\n";
            currCol = 1;
        }
        return output;
    }

    /**
     * Adding the row from the userInput into the vector.
     * @param inputVec
     * @param currRow
     */
    void Matrix::addRow(std::vector<double> &inputVec, const std::string &currRow) {
        unsigned int i = 1;
        std::string toInsert;
        while (i < currRow.size() - 1) {
            while (currRow.at(i) != ' ' && currRow.at(i) != ']') {
                toInsert += currRow.at(i++);
            }
            i++;
            inputVec.push_back(std::stod(toInsert));
            toInsert = "";
        }
    }

    /**
     * Returns the num of cols from the userInput
     * @param currRow
     * @return
     */
    unsigned int Matrix::getCols(const std::string &currRow) {
        unsigned int numOfCols = 0;
        for (std::string::size_type i = 1; i < currRow.size() - 1; ++i) {
            while (currRow.at(i) == ' ') {
                numOfCols++;
                i++;
            }
        }
        return ++numOfCols;
    }

    /**
     * Checks if a row from the userInput is valid.
     * @param currRow
     */
    void Matrix::checkValidRow(const std::string &currRow) {
        if (currRow.at(0) != '[' || currRow.at(currRow.size() - 1) != ']') {
            throw std::invalid_argument("Wrong format");
        }
    }

    /**
     * Checks if a col from the userInput is valid.
     * @param expectedCol
     * @param currRow
     */
    void Matrix::checkValidCol(const unsigned int expectedCol, const std::string &currRow) {
        if (expectedCol != Matrix::getCols(currRow)) {
            throw std::invalid_argument("columns must be same the size!");
        }
    }

    /**
     * Overload operator (istream): Takes an input (matrix) from the user.
     * @param input
     * @param m
     * @return
     */
    std::istream &operator>>(std::istream &input, Matrix &m) {
        std::vector<double> inputVec;
        std::string userInput;
        std::getline(input, userInput);

        unsigned int expectedCol = 1;
        unsigned int numOfRows = 1;

        std::string delimiter = ", ";
        size_t pos = 0;
        std::string currRow;
        bool oneRow = false;

        if ((pos = userInput.find(delimiter)) == std::string::npos) {
            oneRow = true;
        }

        // reading the first row:
        currRow = userInput.substr(0, pos);
        userInput.erase(0, pos + delimiter.length());
        Matrix::checkValidRow(currRow);
        expectedCol = Matrix::getCols(currRow);
        Matrix::addRow(inputVec, currRow);

        while ((pos = userInput.find(delimiter)) != std::string::npos) {
            currRow = userInput.substr(0, pos);
            userInput.erase(0, pos + delimiter.length());
            Matrix::checkValidRow(currRow);
            Matrix::checkValidCol(expectedCol, currRow);
            Matrix::addRow(inputVec, currRow);
            numOfRows++;
        }
        if (!oneRow) {
            Matrix::checkValidRow(userInput);
            Matrix::checkValidCol(expectedCol, userInput);
            Matrix::addRow(inputVec, userInput); // adding the last row
            numOfRows++;
        }

        // add changes to matrix
        m.mat.swap(inputVec);
        m.col = (int) expectedCol;
        m.row = (int) numOfRows;
        return input;
    }

}