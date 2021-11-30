#pragma once
#include <memory>
#include <random>
#include <cctype>


class Matrix{
    public:

    Matrix(const int n_rows, const int n_columns, bool init = true):n_rows(n_rows),n_columns(n_columns)
    {
        M = std::make_unique<double[]>(n_rows*n_columns);
        if (init)
        {
            std::random_device rd;
            std::mt19937 g(rd());
            std::uniform_real_distribution<> d(-3,3);

            for (int i = 0; i < n_rows * n_columns; i++){
                M[i] = d(g);
            }
            
        }
        
    }

    

    Matrix operator+(const Matrix &m);
    Matrix operator*(const Matrix &m);
    Matrix operator-(const Matrix &m);
    const Matrix &operator-=(const Matrix &m);
    
    double operator()(size_t i, size_t j) const
    {
        return M[i*n_columns + j];
    }

  
    void VectorAdd(const Matrix &vector);

    void f(const std::function<double(double)> &fn);
    Matrix row(size_t i);

    Matrix copy();
    void Multiply(const Matrix &m);
 

    inline void set(double value, size_t i, size_t j)
    {
       M[i*n_columns + j] = value;
    }
    
    Matrix Transpose();
    void FillRow(const  u_char* data, size_t row);



    size_t n_rows,n_columns;

   

  

    
    std::unique_ptr<double[]> M;

};

