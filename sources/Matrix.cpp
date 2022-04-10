#include "Matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

//todo documentation - all functions
//todo - check about the main problem
//todo - cin

namespace zich {

    Matrix::Matrix(const std::vector<double> &vec, int row, int col)
            : mat(vec), row(row), col(col) {
        checkInput(vec.size(), row, col);
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

    double Matrix::calculateSumOfMat(const Matrix &m) {
        double sum = 0;
        for (unsigned int i = 0; i < m.mat.size(); ++i) {
            sum += m.mat[i];
        }
        return sum;
    }

    bool Matrix::isEqual(const Matrix &m1, const Matrix &m2) const {
        for (unsigned int i = 0; i < this->mat.size(); ++i) {
            if (m1.mat[i] != m2.mat[i]) {
                return false;
            }
        }
        return true;
    }


    Matrix Matrix::operator-() const {
        Matrix minusMat{this->mat, this->row, this->col};
        for (unsigned int i = 0; i < minusMat.mat.size(); ++i) {
            if (minusMat.mat[i] != 0) {
                minusMat.mat[i] *= -1;
            }
        }
        return minusMat;
    }

    Matrix Matrix::operator+() const {
        Matrix plusMat{this->mat, this->row, this->col};
        return plusMat;
    }


    Matrix Matrix::operator+(const Matrix &other) const {
        this->checkSameDimension(other);
        Matrix newMat{this->mat, this->row, this->col};
        for (unsigned int i = 0; i < newMat.mat.size(); ++i) {
            newMat.mat[i] += other.mat[i];
        }
        return newMat;
    }

    Matrix &Matrix::operator+=(const Matrix &other) {
        this->checkSameDimension(other);
        *this = *this + other;
        return *this;
    }

    Matrix Matrix::operator-(const Matrix &other) const {
        this->checkSameDimension(other);
        Matrix newMat{this->mat, this->row, this->col};
        for (unsigned int i = 0; i < newMat.mat.size(); ++i) {
            newMat.mat[i] -= other.mat[i];
        }
        return newMat;
    }

    Matrix &Matrix::operator-=(const Matrix &other) {
        this->checkSameDimension(other);
        *this = *this - other;
        return *this;
    }

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

    Matrix &Matrix::operator*=(const Matrix &other) {
        this->isMultiDefined(other);
        *this = *this * other;
        return *this;
    }

    Matrix &Matrix::operator*=(const double scalar) {
        for (unsigned int i = 0; i < this->mat.size(); ++i) {
            this->mat[i] *= scalar;
        }
        return *this;
    }

//prefix increment takes no arguments:
    Matrix &Matrix::operator++() {
        for (unsigned int i = 0; i < this->mat.size(); ++i) {
            this->mat[i]++;
        }
        return *this;
    }

    Matrix &Matrix::operator--() {
        for (unsigned int i = 0; i < this->mat.size(); ++i) {
            this->mat[i]--;
        }
        return *this;
    }

//postfix increment:
    Matrix Matrix::operator++(int) {
        Matrix matCopy{this->mat, this->row, this->col};
        ++*this;
        return matCopy;
    }

    Matrix Matrix::operator--(int) {
        Matrix matCopy{this->mat, this->row, this->col};
        --*this;
        return matCopy;
    }

    bool Matrix::operator!=(const Matrix &other) const {
        this->checkSameDimension(other);
        return !this->isEqual(*this, other);
    }

    bool Matrix::operator==(const Matrix &other) const {
        this->checkSameDimension(other);
        return this->isEqual(*this, other);
    }

    bool Matrix::operator>(const Matrix &other) const {
        this->checkSameDimension(other);
        return this->calculateSumOfMat(*this) > this->calculateSumOfMat(other);
    }

    bool Matrix::operator>=(const Matrix &other) const {
        this->checkSameDimension(other);
        return this->calculateSumOfMat(*this) > this->calculateSumOfMat(other) || *this == other;
    }

    bool Matrix::operator<(const Matrix &other) const {
        this->checkSameDimension(other);
        return this->calculateSumOfMat(*this) < this->calculateSumOfMat(other);
    }

    bool Matrix::operator<=(const Matrix &other) const {
        this->checkSameDimension(other);
        return this->calculateSumOfMat(*this) < this->calculateSumOfMat(other) || *this == other;
    }

    Matrix operator*(const double scalar, const Matrix &m) {
        Matrix newMat{m.mat, m.row, m.col};
        for (unsigned int i = 0; i < newMat.mat.size(); ++i) {
            newMat.mat[i] *= scalar;
        }
        return newMat;
    }

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
            output << "]";
            if (index < m.mat.size()) {
                output << "\n";
            }
            currCol = 1;
        }
        return output;
    }


    void Matrix::addRow(std::vector<double> &inputVec, const std::string &currRow) {
        unsigned int i = 1;
        std::string toInsert;
        while (i < currRow.size() - 1) {
            while (currRow.at(i) != ' ' && currRow.at(i) != ']') {
                toInsert += currRow.at(i++);
            }
            i++;
            if (!toInsert.empty()) {
                inputVec.push_back(std::stod(toInsert));
                toInsert = "";
            }
        }
    }

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

    void Matrix::checkValidRow(const std::string &currRow) {
        if (currRow.at(0) != '[' || currRow.at(currRow.size() - 1) != ']') {
            throw std::invalid_argument("Wrong format");
        }
        for (std::string::size_type i = 1; i < currRow.size() - 1; ++i) {
            if (currRow.at(i) != ' ' && std::isdigit(currRow.at(i)) == 0) {
                throw std::invalid_argument("Wrong format");
            }
        }
    }

    void Matrix::checkValidCol(const unsigned int expectedCol, const std::string &currRow) {
        if (expectedCol != Matrix::getCols(currRow)) {
            throw std::invalid_argument("columns must be same the size!");
        }
    }

    std::istream &operator>>(std::istream &input, Matrix &m) {
        std::vector<double> inputVec;
        std::string userInput;
        std::getline(input, userInput);

        unsigned int expectedCol = 1;
        unsigned int numOfRows = 1;

        std::string delimiter = ", ";
        size_t pos = 0;
        std::string currRow;

        // reading the first row:
        pos = userInput.find(delimiter);
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
        Matrix::checkValidRow(userInput);
        Matrix::checkValidCol(expectedCol, userInput);
        Matrix::addRow(inputVec, userInput); // adding the last row
        numOfRows++;

        // add changes to matrix
        m.mat = inputVec;
        m.col = (int) expectedCol;
        m.row = (int) numOfRows;

        return input;
    }

}