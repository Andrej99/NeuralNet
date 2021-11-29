#include "matrix.h"
#include <iostream>
#include "util.h"

void print(const  Matrix &m)
{
       for (size_t i = 0; i < m.n_rows; i++)
    {
        for (size_t j= 0; j < m.n_columns; j++)
        {

            printf("%lf ",m(i,j));
         
        }
        puts("");
        
    }
    puts("-----------------");

}

double sigmoid(double x) { return 1/(1 + exp(-x));}
double d_sigmoid(double x) { return sigmoid(x)*( 1-sigmoid(x)); }

double relu(double x) {return x <=0 ? 0:x;}
double d_relu(double x) {return x <= 0 ? 0 : 1;}

double compute_error(const Matrix &out, const Matrix &labels)
{
    double error = 0;
    int n = 0;

    for (size_t i = 0; i < out.n_rows; i++){
        n++;
        error += (out(i,0) - labels(i,0))*(out(i,0) - labels(i,0));

    }

    return error/n;

}


int main()
{

 


    Matrix X(4,2);

    X.set(0,0,0);
    X.set(0,0,1);

    X.set(0,1,0);
    X.set(1,1,1);

    X.set(1,2,0);
    X.set(0,2,1);
    
    X.set(1,3,0);
    X.set(1,3,1);


    Matrix y(4,1);
    y.set(0,0,0);
    y.set(1,1,0);
    y.set(1,2,0);
    y.set(0,3,0);
    
  

    Matrix W1(2,2);
    Matrix W2(1,2);

    Matrix b1 = Matrix(2,1);
    
    Matrix b2 = Matrix(2,1);


    
    return 0;
}
