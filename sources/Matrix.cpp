// @AUTHOR: dvir borochov

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <numeric>
#include <tgmath.h>
#include <algorithm>
#include "Matrix.hpp"

using namespace std;
using namespace zich;

// initializer lists of vec, row and column
Matrix::Matrix(vector<double> vec, int row, int column)
    : _vec(std::move(vec)), _row(row), _column(column)

{
    if (this->_vec.empty())
    {
        throw invalid_argument("empty vactor");
    }
    if (this->_row <= 0 || this->_column <= 0)
    {
        throw invalid_argument("size of row/ colunm is negetive");
    }
    if (this->_row * this->_column != this->_row * this->_column)
    {
        //  cout << this->_row * this->_column << endl << this->_row * this->_column << endl;
        throw invalid_argument("unvalid sizes");
    }
    if(this->_vec.size() != (unsigned int)(this->_row) * (unsigned int)(this->_column)){
                throw invalid_argument("unvalid sizes");
    }
}

//-----------------------------
// Arithmetic Operators:
//-----------------------------

// make the change on other matrix
Matrix Matrix::operator-() const
{
    Matrix temp{this->_vec, this->_row, this->_column};
    int t = 0;
    for (unsigned i = 0; i < temp._vec.size(); i++)
    {
        t = temp._vec.at(i);
        t = -t;
        temp._vec.at(i) = t;
    }
    return temp;
}

Matrix Matrix::operator-(const Matrix &other)
{
    if (this->_row != other._row || this->_column != other._column)
    {
        throw "can't make Arithmetic Operators between Different matrices";
    }
    Matrix temp{this->_vec, this->_row, this->_column};
    for (unsigned i = 0; i < temp._vec.size(); i++)
    {
        temp._vec.at(i) = this->_vec.at(i) - other._vec.at(i);
    }

    return temp;
}

Matrix Matrix::operator+() const
{

    return *this;
}
Matrix Matrix::operator+(const Matrix &other)
{
    if (this->_row != other._row || this->_column != other._column)
    {
        throw "can't make Arithmetic Operators between Different matrices";
    }
    Matrix temp{this->_vec, this->_row, this->_column};
    for (unsigned i = 0; i < temp._vec.size(); i++)
    {
        temp._vec.at(i) = this->_vec.at(i) + other._vec.at(i);
    }

    return temp;
}
Matrix Matrix::operator+=(const Matrix &other)
{
    if (this->_row != other._row || this->_column != other._column)
    {
        throw "can't make Arithmetic Operators between Different matrices";
    }
    return (*this = *this + other);
}
Matrix Matrix::operator-=(const Matrix &other)
{
    if (this->_row != other._row || this->_column != other._column)
    {
        throw "can't make Arithmetic Operators between Different matrices";
    }
    return (*this = *this - other);
}

// ----------------------
// inc and dec operators
// ----------------------

Matrix &Matrix::operator++() // pre (++x)
{
    for (unsigned i = 0; i < this->_vec.size(); i++)
    {
        this->_vec.at(i) += 1;
    }

    return *this;
}

Matrix &Matrix::operator--() // pre (--x)
{
    for (unsigned i = 0; i < this->_vec.size(); i++)
    {
        this->_vec.at(i) -= 1;
    }
    return *this;
}

Matrix Matrix::operator--(int num) // post (x--)
{

    Matrix res = *this;
    --(*this);
    return res;
}

Matrix Matrix::operator++(int num) // post (x++)
{
    Matrix res = *this;
    ++(*this);
    return res;
}

//---------------------
// Comparison Operators
//---------------------

bool Matrix::operator!=(const Matrix &other) const
{

    return !(*this == other);
}

bool Matrix::operator==(const Matrix &other) const
{
    if (this->_row != other._row || this->_column != other._column)
    {
        throw invalid_argument("are not the same.. ");
    }

    for (unsigned int i = 0; i < this->_row; ++i)
    {
        for (unsigned int j = 0; j < this->_column; j++)
        {
            if (this->_vec.at(i) != other._vec.at(i))
            {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator<=(const Matrix &other) const
{
    if (this->_row != other._row || this->_column != other._column)
    {
        throw "can't compare betwen them";
    }
    bool flag = false;
    size_t sum1 = std::accumulate(this->_vec.begin(), this->_vec.end(), 0.0);
    size_t sum2 = std::accumulate(other._vec.begin(), other._vec.end(), 0.0);
    if (sum1 <= sum2)
    {
        flag = true;
    }
    return flag;
}
bool Matrix::operator>=(const Matrix &other) const
{
    if (this->_row != other._row || this->_column != other._column)
    {
        throw "can't compare betwen them";
    }
    bool flag = false;
    size_t sum1 = std::accumulate(this->_vec.begin(), this->_vec.end(), 0.0);
    size_t sum2 = std::accumulate(other._vec.begin(), other._vec.end(), 0.0);
    if (sum1 >= sum2)
    {
        flag = true;
    }
    return flag;
}

bool Matrix::operator<(const Matrix &other) const
{
    if (this->_row != other._row || this->_column != other._column)
    {
        throw "can't compare betwen them";
    }
    bool flag = false;
    size_t sum1 = std::accumulate(this->_vec.begin(), this->_vec.end(), 0.0);
    size_t sum2 = std::accumulate(other._vec.begin(), other._vec.end(), 0.0);
    if (sum1 < sum2)
    {
        flag = true;
    }
    return flag;
}
bool Matrix::operator>(const Matrix &other) const
{
    if (this->_row != other._row || this->_column != other._column)
    {
        throw "can't compare betwen them";
    }
    bool flag = false;
    size_t sum1 = std::accumulate(this->_vec.begin(), this->_vec.end(), 0.0);
    size_t sum2 = std::accumulate(other._vec.begin(), other._vec.end(), 0.0);
    if (sum1 > sum2)
    {
        flag = true;
    }
    return flag;
}

//---------------
// mult Operators
//---------------

// mult mat with some num.. not change the orginal mat
zich::Matrix zich::operator*(double d, Matrix &mat)
{
    Matrix temp{mat._vec, mat._row, mat._column};
    double t = 0;
    for (unsigned i = 0; i < temp._vec.size(); i++)
    {
        t = temp._vec.at(i);
        t *= d;
        temp._vec.at(i) = t;
    }
    return temp;
}
/*

*/
double Matrix::mult_helper(const Matrix &other, const int row, const int col)
{
    double ans = 0;
    for (int i = 0; i < this->_column; i++)
    {
        unsigned int left_mat = (unsigned int)(this->_column * row + i);
        unsigned int right_mat = (unsigned int)(other._column * i + col);
        ans += this->_vec.at(left_mat) * other._vec.at(right_mat);
    }
    return ans;
}

// mult 2 mat..return the new mat the mult of them
Matrix Matrix::operator*(const Matrix &other)
{
    if (this->_column != other._row)
    {
        throw "column num of left matrix not eqals to right rows num";
    }

    std::vector<double> tVec;
    tVec.resize((unsigned int)(this->_row * other._column));
    Matrix temp(tVec, this->_row, other._column);
    for (int i = 0; i < temp._row; i++)
    {
        for (int j = 0; j < temp._column; j++)
        {
            temp._vec.at((unsigned int)(i * temp._column + j)) = mult_helper(other, i, j);
        }
    }
    return temp;
}

// mult mat with some num, change and return the orginal mat
Matrix Matrix::operator*=(double d)
{
    double t = 0;
    for (unsigned int i = 0; i < this->_vec.size(); i++)
    {
        t = this->_vec.at(i);
        t *= d;
        this->_vec.at(i) = t;
    }
    return *this;
}

Matrix Matrix::operator*(double d) const
{
    Matrix temp{this->_vec, this->_row, this->_column};
    double t = 0;
    for (unsigned i = 0; i < temp._vec.size(); i++)
    {
        t = temp._vec.at(i);
        t *= d;
        temp._vec.at(i) = t;
    }
    return temp;
}

Matrix &Matrix::operator*=(const Matrix &other)
{
    *this = (*this * other);
    return *this;
}

//--------------
// I/O Operators
//--------------

ostream &zich::operator<<(std::ostream &out, Matrix mat)
{
    unsigned int ii = 0;
    for (unsigned int i = 0; i < mat._row; i++)
    {
        out << "[";
        for (unsigned int j = 0; j < mat._column; j++)
        {
            if (j < mat._column - 1)
            {
                ii = (unsigned int)(mat._column);
                out << mat._vec.at(i * ii + j) << " ";
            }
            else
            {
                ii = (unsigned int)(mat._column);
                out << mat._vec.at(i * ii + j);
            }
        }
        if (i < mat._row - 1)
        {
            out << "]" << endl;
        }
        else
        {
            out << "]";
        }
    }
    return out;
}

istream &zich::operator>>(std::istream &in, Matrix &mat)
{
    string s;
    string token;
    string delimiter = ", ";
    string ans;
    size_t rowLen = SIZE_MAX; // the length of the row
    size_t pos = 0;
    double data = 0;
    std::vector<double> finvec;

    getline(in, s); // scan the str from the user:

    while ((pos = s.find(delimiter)) != string::npos)
    {
        token = s.substr(0, pos);
        if (rowLen == SIZE_MAX) // init the line at the first time..
        {
            rowLen = token.length();
        }
        else
        {
            if (token.length() != rowLen)
            {
                throw invalid_argument("the rows must be the same length\n");
            }
        }
        ans += token;
        std::cout << token << endl;
        s.erase(0, pos + delimiter.length());
    }
    //** final iterate:
    token = s.substr(0, pos);
    if (token.length() != rowLen)
    {
        throw invalid_argument("the rows must be the same length\n");
    }
    ans += token;
    std::cout << token << endl;

    //** endl

    if (s.length() != rowLen) // check if the final part is valid
    {
        throw invalid_argument("the rows must be the same length\n");
    }
    ans += s;
    ans.erase(std::remove(ans.begin(), ans.end(), '['), ans.end()); // erase '[' from the str
    std::replace(ans.begin(), ans.end(), ']', ' ');                 // replace all ']' to ' '
    std::stringstream iss(ans);                                     // parse str to vector of double:

    while (iss >> data)
    {
        finvec.push_back(data);
    }
    // allocate the final data to the matrix:
    mat._row = rowLen;
    mat._column = (int)(finvec.size() / rowLen);
    mat._vec = finvec;
    return in;
}
