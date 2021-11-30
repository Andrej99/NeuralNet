#include "matrix.h"
#include <cassert>




Matrix Matrix::operator*(const Matrix &B)
{

    assert(n_columns == B.n_rows);

    Matrix result(n_rows,B.n_columns);
    for (size_t i = 0; i < n_rows; i++){

        for (size_t j= 0; j < B.n_columns; j++){
            double sum = 0;

            for(size_t k = 0; k < n_columns; k++){

                sum += this->operator()(i,k) * B(k,j);
            }
            result.set(sum,i,j);

            
        }
        
    }

    return result;
}

void Matrix::f(const std::function<double(double)> &fn)
{
    for (size_t i = 0; i < n_rows * n_columns; i++){
        M[i] = fn(M[i]);
    }
}


 void Matrix::VectorAdd(const Matrix &vector)
 {
     assert(vector.n_rows == n_columns);
     assert(vector.n_columns == 1);
     for (size_t i = 0; i < n_rows; i++){

         for (size_t j = 0; j < n_columns; j++){
            
             M[i*n_columns + j] += vector.M[j];

         }
          
     }

 }

 Matrix Matrix::copy()
 {
     Matrix result(n_rows,n_columns);
     for (size_t i = 0; i < n_rows*n_columns; i++){
         result.M[i] = M[i];
     }

     return result;

 }
//For inplace:
//https://en.wikipedia.org/wiki/In-place_matrix_transposition#Non-square_matrices%3a_Following_the_cycles
Matrix Matrix::Transpose()
 {
    Matrix result(n_columns,n_rows);
    
    //#pragma omp parallel for
    for(size_t n = 0; n<n_rows * n_columns; n++) {
        size_t i = n/n_rows;
        size_t j = n%n_rows;
        result.M[n] = M[n_columns*j + i];
    }
    return result;
 }

 Matrix Matrix::operator+(const Matrix &m)
 {
     assert(m.n_columns == n_columns);
     assert(m.n_rows == n_rows);

     Matrix result(n_rows,n_columns);


    
     for(size_t i = 0; i < n_columns*n_rows; i++){
         result.M[i] = M[i] + m.M[i];
     }

     return result;
 }

 Matrix Matrix::operator-(const Matrix &m)
 {
     assert(m.n_columns == n_columns);
     assert(m.n_rows == n_rows);

     Matrix result(n_rows,n_columns);


    
     for(size_t i = 0; i < n_columns*n_rows; i++){
         result.M[i] = M[i] - m.M[i];
     }

     return result;

 }

 Matrix Matrix::row(size_t i)
 {
     assert(i < n_rows);
     Matrix result(1,n_columns);

     size_t row_i = i*n_columns;

     for (size_t i = 0; i < n_columns; i++){
         result.M[i] = M[row_i + i];
     }

     return result;
          
 }

void Matrix::Multiply(const Matrix &m)
{
     assert(m.n_columns == n_columns);
     assert(m.n_rows == n_rows);

     
     for(size_t i = 0; i < n_columns*n_rows; i++){
         M[i] = M[i] * m.M[i];
     }

}

const Matrix &Matrix::operator-=(const Matrix &m)
{
    assert(m.n_columns == n_columns);
    assert(m.n_rows == n_rows);
    
     for(size_t i = 0; i < n_columns*n_rows; i++){
         M[i] = M[i] - m.M[i];
     }

     return *this;

}

void Matrix::FillRow(const  u_char* data, size_t row)
{
    assert(row < n_rows);
     

     size_t row_i = row*n_columns;

     for (size_t i = 0; i < n_columns; i++){
         M[row_i + i] = (double)data[i];
     }

}