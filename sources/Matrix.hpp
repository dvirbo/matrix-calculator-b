
// @AUTHOR: dvir borochov
// Header file for class Matrix
#include <iostream>
#include <vector>
namespace zich
{
    class Matrix
    {
        int _row;
        int _column;
        // double mult_helper(const Matrix &other, const int row, const int col);

    public:
        std::vector<double> _vec;
        Matrix(std::vector<double> vec, int row, int column);

        //#####################
        // Arithmetic Operators
        //#####################
        Matrix operator-() const;
        Matrix operator-(const Matrix &other);
        Matrix operator+() const;
        Matrix operator+(const Matrix &other);
        Matrix operator+=(const Matrix &other);
        Matrix operator-=(const Matrix &other);

        //##############################
        // Inc Dec Operators
        //##############################

        Matrix operator--(int num);

        Matrix operator++(int num);

        Matrix &operator--();

        Matrix &operator++();

        //#####################
        // Comparison Operators
        //#####################

        bool operator!=(const Matrix &other) const;

        bool operator==(const Matrix &other) const;

        bool operator<=(const Matrix &other) const;
        bool operator>=(const Matrix &other) const;

        bool operator<(const Matrix &other) const;
        bool operator>(const Matrix &other) const;

        //##############################
        // mult Operator
        //##############################
        friend Matrix operator*(double d, Matrix &mat);
        Matrix operator*(const Matrix &other);
        Matrix operator*=(double d);
        Matrix &operator*=(const Matrix &other);              
        Matrix operator*(double d) const;
         double mult_helper(const Matrix &other, const int row, const int col);


        //##############################
        // I/O Operators
        //##############################
        friend std::ostream &operator<<(std::ostream &out, Matrix mat);
        friend std::istream &operator>>(std::istream &in, Matrix &mat);
    };

}